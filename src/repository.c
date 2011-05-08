/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2011 Shuhei Tanuma
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "php_git.h"
#include <spl/spl_array.h>
#include <zend_interfaces.h>
#include <string.h>
#include <time.h>

PHPAPI zend_class_entry *git_repository_class_entry;

extern void create_signature_from_commit(zval **signature, const git_signature *sig);
extern int php_git_odb_add_backend(git_odb **odb, zval *backend, int priority);
extern int php_git_odb_add_alternate(git_odb **odb, zval *backend, int priority);

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_init, 0, 0, 2)
    ZEND_ARG_INFO(0, path)
    ZEND_ARG_INFO(0, is_bare)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_object, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_commit, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_construct, 0, 0, 0)
    ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_lookup_ref, 0, 0, 1)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_open3, 0, 0, 1)
    ZEND_ARG_INFO(0, git_dir)
    ZEND_ARG_INFO(0, odb)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_add_backend, 0, 0, 2)
    ZEND_ARG_INFO(0, backend)
    ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_add_alternate, 0, 0, 2)
    ZEND_ARG_INFO(0, backend)
    ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_references, 0, 0, 1)
    ZEND_ARG_INFO(0, flag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_open2, 0, 0, 4)
    ZEND_ARG_INFO(0, git_dir)
    ZEND_ARG_INFO(0, git_object_directory)
    ZEND_ARG_INFO(0, git_index_file)
    ZEND_ARG_INFO(0, git_work_tree)
ZEND_END_ARG_INFO()

static void php_git_repository_free_storage(php_git_repository_t *obj TSRMLS_DC)
{
    // if added some backend. free backend before free zend_object.
    if(obj->repository){
        git_repository_free(obj->repository);
        obj->repository = NULL;
    }
    zend_object_std_dtor(&obj->zo TSRMLS_CC);

    efree(obj);
}

zend_object_value php_git_repository_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_repository_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_repository_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();

    return retval;
}

PHP_METHOD(git_repository, init)
{
    git_repository *repository;
    char *path = NULL;
    int path_len = 0;
    int is_bare = 0;
    int ret;
    zval *obj;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"sl",
        &path, &path_len, &is_bare) == FAILURE){
        return;
    }

    int suc = git_repository_init(&repository,path,is_bare);

    if(suc != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "can't create repository\n");
        return;
    }
    
    MAKE_STD_ZVAL(obj);
    object_init_ex(obj, git_repository_class_entry);
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(obj TSRMLS_CC);
    myobj->repository = repository;

    add_property_string_ex(obj, "path",sizeof("path"),path, 1 TSRMLS_CC);
    RETURN_ZVAL(obj, 1, 1);
}

PHP_METHOD(git_repository, getIndex)
{
    zval *object = getThis();
    git_repository *repository;
    git_index *index;

    zval *index_object;
    int ret = 0;

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);

    ret = git_repository_index(&index,myobj->repository);

    if (ret == GIT_EBAREINDEX) {
        php_error_docref(NULL TSRMLS_CC, E_NOTICE, "The index file is not backed up by an existing repository.");
        RETURN_FALSE;
    } else if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "specified index cannot be opend");
        RETURN_FALSE;
    }

    MAKE_STD_ZVAL(index_object);
    object_init_ex(index_object, git_index_class_entry);
    php_git_index_t *iobj = (php_git_index_t *) zend_object_store_get_object(index_object TSRMLS_CC);

    iobj->index = index;

    git_index_read(index);

    //Todo: Read from Git object.
    //add_property_string_ex(index_object, "path",5,index->index_file_path, 1 TSRMLS_CC);
    //add_property_long(index_object, "entry_count",git_index_entrycount(index));
    //zval_ptr_dtor(&index_object);

    RETURN_ZVAL(index_object,0,1);
}


PHP_METHOD(git_repository, getObject)
{
    zval *object = getThis();
    zval *git_object;
    int git_rawsz = 0;
    git_repository *repository;
    git_odb *odb;
    git_blob *blob;
    git_oid oid;
    
    char *hash;
    int hash_len = 0;
    int ret = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }
    
    git_oid_mkstr(&oid, hash);
    
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;
    
    odb = git_repository_database(repository);
    
    if(!git_odb_exists(odb,&oid)){
        RETURN_FALSE;
    }else{
        ret = git_blob_lookup(&blob, repository,&oid);

        if(ret == GIT_SUCCESS){
            MAKE_STD_ZVAL(git_object);
            object_init_ex(git_object, git_blob_class_entry);
            php_git_blob_t *blobobj = (php_git_blob_t *) zend_object_store_get_object(git_object TSRMLS_CC);
            blobobj->object = blob;

            git_rawsz = git_blob_rawsize(blob);
            add_property_stringl_ex(git_object,"data", sizeof("data"), (char *)git_blob_rawcontent(blob),git_rawsz, 1 TSRMLS_CC);
            RETURN_ZVAL(git_object,1,1);
        }else{
            RETURN_FALSE;
        }
    }
}


void create_tree_entry_from_entry(zval **object, git_tree_entry *entry, git_repository *repository)
{
    TSRMLS_FETCH();
    char buf[41] = {0};
    const git_oid *oid;
    MAKE_STD_ZVAL(*object);
    object_init_ex(*object, git_tree_entry_class_entry);
    php_git_tree_entry_t *entry_obj = (php_git_tree_entry_t *) zend_object_store_get_object(*object TSRMLS_CC);

    entry_obj->entry = entry;
    entry_obj->repository = repository;
    oid = git_tree_entry_id(entry);
    git_oid_to_string(buf,41,oid);
    
    add_property_string(*object, "name", (char *)git_tree_entry_name(entry), 1);
    add_property_string(*object, "oid", buf, 1);
    add_property_long(*object, "mode", git_tree_entry_attributes(entry));
}



PHP_METHOD(git_repository, getCommit)
{
    zval *object = getThis();
    zval *git_commit_object;
    php_git_tree_entry_t *entry_obj;
    git_repository *repository;
    git_odb *odb;
    git_object *blob;
    git_oid oid;
    char out[GIT_OID_HEXSZ+1] = {0};
    char *hash;
    int hash_len = 0;
    int ret = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }
    
    git_oid_mkstr(&oid, hash);
    
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;
    odb = git_repository_database(repository);
    
    if(!git_odb_exists(odb,&oid)){
        RETURN_FALSE;
    }else{
        ret = git_object_lookup((git_object **)&blob, repository,&oid , GIT_OBJ_COMMIT);
        
        if(ret == GIT_SUCCESS){
            zval *author;
            zval *committer;
            git_commit *commit = (git_commit *)blob;

            create_signature_from_commit(&author, git_commit_author(commit));
            create_signature_from_commit(&committer, git_commit_committer(commit));
            
            MAKE_STD_ZVAL(git_commit_object);
            object_init_ex(git_commit_object,git_commit_class_entry);

            php_git_commit_t *cobj = (php_git_commit_t *) zend_object_store_get_object(git_commit_object TSRMLS_CC);
            cobj->object = commit;
            cobj->repository = repository;

            add_property_zval(git_commit_object,"author", author);
            add_property_zval(git_commit_object,"committer", committer);

            add_property_string_ex(git_commit_object,"tree",sizeof("tree"),git_oid_allocfmt(git_commit_tree_oid(commit)), 1 TSRMLS_CC);

            int parent_count = git_commit_parentcount(commit);
            int i;
            zval *parents;

            MAKE_STD_ZVAL(parents);
            array_init(parents);
            for (i = 0; i < parent_count; i++) {
                add_next_index_string(parents,git_oid_allocfmt(git_commit_parent_oid(commit,i)),1);
            }
            
            add_property_string_ex(git_commit_object,"message",sizeof("message"),git_commit_message(commit), 1 TSRMLS_CC);
            add_property_zval_ex(git_commit_object,"parents",sizeof("parents"),parents TSRMLS_CC);

            RETVAL_ZVAL(git_commit_object,0,1);
            zval_ptr_dtor(&parents);
            zval_ptr_dtor(&author);
            zval_ptr_dtor(&committer);
        }else{
            RETURN_FALSE;
        }
    }
}


PHP_METHOD(git_repository, __construct)
{
    const char *repository_path = NULL;
    int ret = 0;
    int arg_len = 0;
    git_repository *repository;
    zval *object = getThis();

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "|s", &repository_path, &arg_len) == FAILURE){
        return;
    }

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);

    if(arg_len > 0){
        ret = git_repository_open(&repository,repository_path);
        if(ret != GIT_SUCCESS){
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                "specified repository does not exist.");
            RETURN_FALSE;
        }
        myobj->repository = repository;
        add_property_string_ex(object, "path",sizeof("path"),(char *)repository_path, 1 TSRMLS_CC);
    }else{
        myobj->repository = NULL;
    }
}


PHP_METHOD(git_repository, getTree)
{
    zval *object = getThis();
    git_tree *tree;
    zval *git_tree;

    git_oid oid;
    char *hash;
    int hash_len = 0;
    int ret = 0;
    git_tree_entry *entry;
    php_git_tree_entry_t *te;
    char buf[GIT_OID_HEXSZ+1] = {0};
    int i = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }

    git_oid_mkstr(&oid, hash);
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);

    ret = git_tree_lookup(&tree, myobj->repository, &oid);
    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
            "target tree does not exist.");
        RETURN_FALSE;
    }
    
    MAKE_STD_ZVAL(git_tree);
    object_init_ex(git_tree, git_tree_class_entry);

    php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
    tobj->object = tree;
    tobj->repository = myobj->repository;

    RETURN_ZVAL(git_tree,0,0);
}


PHP_METHOD(git_repository, getWalker)
{
    zval *walker_object;
    git_revwalk *walk;
    int ret = 0;

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    ret = git_revwalk_new(&walk,myobj->repository);

    MAKE_STD_ZVAL(walker_object);
    object_init_ex(walker_object, git_walker_class_entry);
    php_git_walker_t *wobj = (php_git_walker_t *) zend_object_store_get_object(walker_object TSRMLS_CC);
    wobj->walker = walk;

    RETURN_ZVAL(walker_object,0,1);
}


PHP_METHOD(git_repository, addAlternate)
{
    php_git_repository_t *this = (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *backend;
    git_odb *odb;
    git_odb_backend *odb_backend;
    int priority = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &backend, &priority) == FAILURE){
        return;
    }

    if(!instanceof_function(Z_OBJCE_P(backend), git_backend_class_entry TSRMLS_CC)){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "parameter does not extends Git\\Backend");
        return;
    }

    odb = git_repository_database(this->repository);
    int ret = php_git_odb_add_alternate(&odb, backend, priority);
}


PHP_METHOD(git_repository, addBackend)
{
    php_git_repository_t *this = (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *backend;
    git_odb *odb;
    git_odb_backend *odb_backend;
    int priority = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &backend, &priority) == FAILURE){
        return;
    }
    if(!instanceof_function(Z_OBJCE_P(backend), git_backend_class_entry TSRMLS_CC)){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "parameter does not extends Git\\Backend");
        return;
    }
    
    odb = git_repository_database(this->repository);
    int ret = php_git_odb_add_backend(&odb, backend, priority);
}


PHP_METHOD(git_repository, lookupRef)
{
    php_git_repository_t *this = (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *name;
    int  name_len = 0;
    int  result;
    zval *ref;
    char out[GIT_OID_HEXSZ+1] = {0};
    git_oid *oid;
    git_rtype type;
    git_reference *reference;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &name, &name_len) == FAILURE){
        return;
    }

    result = git_reference_lookup(&reference, this->repository, name);
    if(result != GIT_SUCCESS) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "Can't find specified reference.");
        RETURN_FALSE;
    }

    MAKE_STD_ZVAL(ref);
    object_init_ex(ref, git_reference_class_entry);
    php_git_reference_t *refobj  = (php_git_reference_t *) zend_object_store_get_object(ref TSRMLS_CC);
    refobj->object = reference;

    add_property_string_ex(ref,"name",  sizeof("name"),  (char *)git_reference_name(reference), 1 TSRMLS_CC);

    type = git_reference_type(reference);
    if(type == GIT_REF_SYMBOLIC) {
        const char *target = git_reference_target(reference);
        if(target != NULL) {
            add_property_string_ex(ref,"target",sizeof("target"),(char *)target, 1 TSRMLS_CC);
        }
        int rr = git_reference_resolve(&refobj->object,reference);
        if(rr != GIT_SUCCESS){
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                "something wrong");
            RETURN_FALSE;
        }
    }

    git_oid_to_string(out,GIT_OID_HEXSZ+1,git_reference_oid(refobj->object));
    add_property_string_ex(ref,"oid",sizeof("oid"),out, 1 TSRMLS_CC);

    RETURN_ZVAL(ref,0,0);
}

PHP_METHOD(git_repository, getReferences)
{
    php_git_repository_t *this= (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_strarray *list = malloc(sizeof(git_strarray));
    int  result;
    int i = 0;
    git_reference *reference;
    zval *references;
    git_rtype type;
    char out[GIT_OID_HEXSZ+1] = {0};

    git_reference_listall(list,this->repository,GIT_REF_LISTALL);

    MAKE_STD_ZVAL(references);
    array_init(references);
    for(i = 0; i < list->count; i++){
        zval *ref;

        // FIXME
        result = git_reference_lookup(&reference, this->repository, list->strings[i]);
        if(result != GIT_SUCCESS) {
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                "Can't find specified reference.");
            RETURN_FALSE;
        }

        MAKE_STD_ZVAL(ref);
        object_init_ex(ref, git_reference_class_entry);
        php_git_reference_t *refobj  = (php_git_reference_t *) zend_object_store_get_object(ref TSRMLS_CC);
        refobj->object = reference;

        add_property_string_ex(ref,"name",  sizeof("name"),  (char *)git_reference_name(reference), 1 TSRMLS_CC);

        type = git_reference_type(reference);
        if(type == GIT_REF_SYMBOLIC) {
            const char *target = git_reference_target(reference);
            if(target != NULL) {
                add_property_string_ex(ref,"target",sizeof("target"),(char *)target, 1 TSRMLS_CC);
            }
            int rr = git_reference_resolve(&refobj->object,reference);
            if(rr != GIT_SUCCESS){
                zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                    "something wrong");
                RETURN_FALSE;
            }
        }

        git_oid_to_string(out,GIT_OID_HEXSZ+1,git_reference_oid(refobj->object));
        add_property_string_ex(ref,"oid",sizeof("oid"),out, 1 TSRMLS_CC);
        memset(out,'\0',GIT_OID_HEXSZ+1);
        //

        add_next_index_zval(references, ref);
    }

    git_strarray_free(list);
    RETURN_ZVAL(references,0,0);
}

PHP_METHOD(git_repository, open3)
{
    php_git_repository_t *this= (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);

    char *git_dir;
    int git_dir_len = 0;
    zval *z_odb;
    char *index = NULL;
    int index_len = 0;
    char *tree = NULL;
    int tree_len = 0;
    int ret = 0;
    php_git_odb_t *odbt = NULL;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s|zss", &git_dir, &git_dir_len, &z_odb, &index, &index_len, &tree, &tree_len) == FAILURE){
        return;
    }
 
    if(this->repository != NULL){
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"repository busy.");
        return;
    }
    if(z_odb){
        if(instanceof_function(Z_OBJCE_P(z_odb), git_odb_class_entry TSRMLS_CC)){
            odbt = (php_git_odb_t *) zend_object_store_get_object(z_odb TSRMLS_CC);
        }else{
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"specified parameter doesn't Git\\Odb");
        }
    }

    ret = git_repository_open3(&this->repository,git_dir,odbt->odb,index,tree);

    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,"can't open specified repository & odb");
    }
}

PHP_METHOD(git_repository, open2)
{
    php_git_repository_t *this= (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *git_dir;
    char *git_object_directory;
    char *git_index_file;
    char *git_work_tree;
    int git_dir_len = 0;
    int git_object_directory_len = 0;
    int git_index_file_len = 0;
    int git_work_tree_len = 0;
    git_repository *repository;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "ssss", &git_dir, &git_dir_len, &git_object_directory, &git_object_directory_len, &git_index_file, &git_index_file_len, &git_work_tree, &git_work_tree_len) == FAILURE){
        return;
    }
    
    if(this->repository != NULL){
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "repository busy");
        return;
    }
    
    int ret = git_repository_open2(&repository,git_dir, git_object_directory, git_index_file, git_work_tree);
    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"can't open specified directories");
        RETURN_FALSE;
    }

    add_property_string_ex(getThis(), "path",sizeof("path"),(char *)git_dir, 1 TSRMLS_CC);
    this->repository = repository;
    RETURN_TRUE;
}

PHP_METHOD(git_repository, getWorkdir)
{
    php_git_repository_t *this= (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    
    if(this->repository != NULL) {
        char *git_workdir;
        git_workdir = git_repository_workdir(this->repository);
        RETVAL_STRING(git_workdir,1);
    }
}

PHP_METHOD(git_repository, empty)
{
    php_git_repository_t *this= (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    if (this->repository != NULL) {
        if (git_repository_is_empty(this->repository)) {
            RETURN_TRUE;
        } else {
            RETURN_FALSE;
        }
    } else {
        RETURN_TRUE;
    }
}


PHPAPI function_entry php_git_repository_methods[] = {
    PHP_ME(git_repository, __construct,   arginfo_git_construct,      ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getCommit,     arginfo_git_get_commit,     ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getObject,     arginfo_git_get_object,     ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getIndex,      NULL,                       ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, lookupRef,     arginfo_git_lookup_ref,     ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getWalker,     arginfo_git_walker,         ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getTree,       arginfo_git_get_tree,       ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, init,          arginfo_git_init,           ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(git_repository, addBackend,    arginfo_git_add_backend,    ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, addAlternate,  arginfo_git_add_alternate,  ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, open3,         arginfo_git_open3,          ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, open2,         arginfo_git_open2,          ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getReferences, arginfo_git_get_references, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getWorkdir,    NULL,                       ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, empty,         NULL,                       ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_git_repository_init(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Repository", php_git_repository_methods);
    git_repository_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    git_repository_class_entry->create_object = php_git_repository_new;
}
