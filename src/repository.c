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

extern int php_git_odb_add_backend(git_odb **odb, zval *backend);

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_branch, 0, 0, 1)
    ZEND_ARG_INFO(0, branch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_update, 0, 0, 2)
    ZEND_ARG_INFO(0, branch)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_open3, 0, 0, 1)
    ZEND_ARG_INFO(0, git_dir)
    ZEND_ARG_INFO(0, odb)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()


static void php_git_repository_free_storage(php_git_repository_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    if(obj->repository){
        git_repository_free(obj->repository);
    }
    obj->repository = NULL;
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

    if(suc != 0){
        php_printf("can't create repository\n");
        return;
    }
    
    MAKE_STD_ZVAL(obj);
    object_init_ex(obj, git_repository_class_entry);
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(obj TSRMLS_CC);
    myobj->repository = repository;

    add_property_string_ex(obj, "path",5,path, 1 TSRMLS_CC);
    RETURN_ZVAL(obj, 1, 1);
}

PHP_METHOD(git_repository, getIndex)
{
    zval *object = getThis();
    git_repository *repository;
    git_index *index;
    //FIXME: GitIndexを呼びたいけどコレでいいの？
    zval *index_object = emalloc(sizeof(zval));
    int ret = 0;

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);


    index = git_repository_index(myobj->repository);
    if(!index){
        php_printf("Git Repository not found");
        RETURN_FALSE;
    }

    object_init_ex(index_object, git_index_class_entry);
    php_git_index_t *iobj = (php_git_index_t *) zend_object_store_get_object(index_object TSRMLS_CC);

    iobj->index = index;
    iobj->repository = repository;

    git_index_read(index);

    //Todo: Read from Git object.
    //add_property_string_ex(index_object, "path",5,index->index_file_path, 1 TSRMLS_CC);
    add_property_long(index_object, "offset", 0);
    add_property_long(index_object, "entry_count",git_index_entrycount(index));
    zend_list_addref(ret);

    RETURN_ZVAL(index_object,1,0);
}


PHP_METHOD(git_repository, getObject)
{
    zval *object = getThis();
    zval *git_raw_object;
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
            MAKE_STD_ZVAL(git_raw_object);
            object_init_ex(git_raw_object, git_blob_class_entry);
            php_git_blob_t *blobobj = (php_git_blob_t *) zend_object_store_get_object(git_raw_object TSRMLS_CC);
            blobobj->object = blob;

            add_property_string_ex(git_raw_object,"data", 5, git_blob_rawcontent(blob), 1 TSRMLS_CC);
            RETURN_ZVAL(git_raw_object,1,0);
            zend_object_std_dtor(git_raw_object TSRMLS_CC);
        }else{
            RETURN_FALSE;
        }
    }
}




PHP_METHOD(git_repository, getCommit)
{
    zval *object = getThis();
    zval *git_raw_object;
    php_git_tree_entry_t *entry_obj;
    git_repository *repository;
    git_odb *odb;
    git_object *blob;
    git_oid oid;
    char out[40];
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
    
    if(git_odb_exists(odb,&oid)){
        RETURN_FALSE;
    }else{
        ret = git_repository_lookup(&blob, repository,&oid , GIT_OBJ_COMMIT);
        
        if(ret == GIT_SUCCESS){
            git_signature *sig;
            zval *committer;
            zval *author;
            MAKE_STD_ZVAL(author);
            char *name;
            object_init_ex(author,git_signature_class_entry);
            sig = git_commit_author(blob);
            add_property_string(author,"name",sig->name,1 TSRMLS_CC);
            add_property_string(author,"email",sig->email,1 TSRMLS_CC);
            add_property_long(author,"time",sig->when.time);

            MAKE_STD_ZVAL(committer);
            object_init_ex(committer,git_signature_class_entry);

            sig = git_commit_committer(blob);
            add_property_string(committer,"name",sig->name,1 TSRMLS_CC);
            add_property_string(committer,"email",sig->email,1 TSRMLS_CC);
            add_property_long(committer,"time",sig->when.time);



            MAKE_STD_ZVAL(git_raw_object);
            object_init_ex(git_raw_object,git_commit_class_entry);
            php_git_commit_t *c_obj = (php_git_commit_t *) zend_object_store_get_object(git_raw_object TSRMLS_CC);
            c_obj->object = blob;
            
            sig = git_commit_author(blob);
            git_tree *tree = git_commit_tree(blob);
            git_oid *tree_oid;
            tree_oid = git_tree_id(tree);
            git_oid_to_string(&out,41,tree_oid);
            //add_property_string(git_raw_object,"tree", out,1);

            add_property_zval(git_raw_object,"author", author);
            add_property_zval(git_raw_object,"committer", committer);


            //コピペ
            zval *git_tree;
            zval *entries;
            git_oid *moid;
            git_tree_entry *entry;

            MAKE_STD_ZVAL(git_tree);
            MAKE_STD_ZVAL(entries);
            array_init(entries);
            object_init_ex(git_tree, git_tree_class_entry);

            int r = git_tree_entrycount(tree);
            int i = 0;
            char buf[40];
            char *offset;
            zval *array_ptr;

            for(i; i < r; i++){
                entry = git_tree_entry_byindex(tree,i);
                moid = git_tree_entry_id(entry);
                git_oid_to_string(&buf,41,moid);

                MAKE_STD_ZVAL(array_ptr);
                object_init_ex(array_ptr, git_tree_entry_class_entry);
                entry_obj = (php_git_tree_entry_t *) zend_object_store_get_object(array_ptr TSRMLS_CC);
                entry_obj->entry = entry;

                add_property_string(array_ptr, "name", git_tree_entry_name(entry), 1);
                add_property_string(array_ptr, "oid", buf, 1);
                add_property_long(array_ptr, "attr", git_tree_entry_attributes(entry));

                add_next_index_zval(entries,  array_ptr);
            }

            php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
            tobj->repository = repository;
            tobj->object = tree;

            add_property_zval(git_tree,"entries", entries);
            add_property_zval(git_raw_object,"tree", git_tree);
            
            RETURN_ZVAL(git_raw_object,1,0);
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

    object_init_ex(object, git_repository_class_entry);

    if(!object){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,
            "Constructor called statically!");
        RETURN_FALSE;
    }

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "|s", &repository_path, &arg_len) == FAILURE){
        return;
    }

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);

    if(arg_len > 0){
        ret = git_repository_open(&repository,repository_path);
        if(ret != GIT_SUCCESS){
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git repository not found.");
            RETURN_FALSE;
        }
        myobj->repository = repository;
       add_property_string_ex(object, "path",5,repository_path, 1 TSRMLS_CC);
    }else{
        myobj->repository = NULL;
    }
}


PHP_METHOD(git_repository, getTree)
{
    //FIXME
    zval *object = getThis();
    git_repository *repository;
    git_tree *tree;
    zval *git_tree;
    zval *entries;

    git_oid oid;
    char *hash;
    int hash_len = 0;
    int ret = 0;
    git_tree_entry *entry;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }

    git_oid_mkstr(&oid, hash);
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;
    ret = git_tree_lookup(&tree, repository, &oid);
    if(ret != GIT_SUCCESS){
        //FIXME
        printf("target not found");
        RETURN_FALSE;
    }
    
    MAKE_STD_ZVAL(git_tree);
    MAKE_STD_ZVAL(entries);
    array_init(entries);
    object_init_ex(git_tree, git_tree_class_entry);

    int r = git_tree_entrycount(tree);
    int i = 0;
    char buf[40];
    char *offset;
    git_oid *moid;
    zval *array_ptr;

    for(i; i < r; i++){
        entry = git_tree_entry_byindex(tree,i);
        moid = git_tree_entry_id(entry);
        git_oid_to_string(buf,41,moid);

        MAKE_STD_ZVAL(array_ptr);
        object_init_ex(array_ptr, git_tree_entry_class_entry);

        add_property_string(array_ptr, "name", git_tree_entry_name(entry), 1);
        add_property_string(array_ptr, "oid", buf, 1);
        add_property_long(array_ptr, "attr", git_tree_entry_attributes(entry));

        add_next_index_zval(entries,  array_ptr);
    }

    php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
    tobj->repository = repository;
    tobj->object = tree;

    add_property_zval(git_tree,"entries", entries);

    RETURN_ZVAL(git_tree,1,0);
}


PHP_METHOD(git_repository, getWalker)
{
    zval *object = getThis();
    git_repository *repository;
    git_index *index;
    //FIXME: GitWalkerを呼びたいけどコレでいいの？
    zval *walker_object = emalloc(sizeof(zval));
    git_revwalk *walk;
    int ret = 0;

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    object_init_ex(walker_object, git_walker_class_entry);
    ret = git_revwalk_new(&walk,repository);
    php_git_walker_t *wobj = (php_git_walker_t *) zend_object_store_get_object(walker_object TSRMLS_CC);
    wobj->walker = walk;
    wobj->repository = repository;

    RETURN_ZVAL(walker_object,1,0);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_add_backend, 0, 0, 1)
    ZEND_ARG_INFO(0, backend)
ZEND_END_ARG_INFO()

PHP_METHOD(git_repository, addBackend)
{
    php_git_repository_t *this = (php_git_repository_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *backend;
    git_odb *odb;
    git_odb_backend *odb_backend;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &backend) == FAILURE){
        return;
    }
    
    odb = git_repository_database(this->repository);
    int ret = php_git_odb_add_backend(&odb, backend);
}



PHP_METHOD(git_repository, getBranch)
{
    zval *object = getThis();
    zval *prop;
    git_repository *repository;
    char *branch;
    char buf[255];
    int branch_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
            "s", &branch, &branch_len) == FAILURE){
        return;
    }

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    prop = zend_read_property(git_class_entry,object,"path",4,0 TSRMLS_DC);
    char *uhi = Z_STRVAL_P(prop);
    
    //FIXME
    FILE *fp;
    sprintf(&buf,"%s/refs/heads/%s",uhi,branch);
    if((fp = fopen(&buf,"r")) == NULL){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,"specified branch name not found");
        return;
    }
    memset(buf,0,sizeof(buf));
    fread(buf,1,40,fp);
    fclose(fp);
    
    RETVAL_STRINGL(buf,40,1 TSRMLS_DC);
}



PHP_METHOD(git_repository, update)
{
    zval *object = getThis();
    zval *prop;
    git_repository *repository;
    char *branch;
    char *hash;
    int hash_len = 0;
    int branch_len = 0;
    char buf[255];

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "ss", &branch, &branch_len, &hash, &hash_len) == FAILURE){
        return;
    }

    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    prop = zend_read_property(git_class_entry,object,"path",4,0 TSRMLS_DC);
    char *uhi = Z_STRVAL_P(prop);
    
    FILE *fp;
    sprintf(&buf,"%s/refs/heads/%s",uhi,branch);
    if((fp = fopen(&buf,"w")) == NULL){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,"specified branch name not found");
        return;
    }
    fputs(hash,fp);
    fclose(fp);
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
        php_error_docref(NULL TSRMLS_CC, E_ERROR,"repository busy.");
        return;
    }
    if(z_odb){
        if(instanceof_function(Z_OBJCE_P(z_odb), git_odb_class_entry TSRMLS_CC)){
            odbt = (php_git_odb_t *) zend_object_store_get_object(z_odb TSRMLS_CC);
        }else{
            php_error_docref(NULL TSRMLS_CC, E_ERROR,"specified parameter isn't Git\\Odb");
        }
    }

    ret = git_repository_open3(&this->repository,git_dir,odbt->odb,index,tree);

    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,"can't open specified repository & odb");
    }
}

PHPAPI function_entry php_git_repository_methods[] = {
    PHP_ME(git_repository, __construct, arginfo_git_construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getCommit, arginfo_git_get_commit, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getObject, arginfo_git_get_object, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getIndex, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getBranch, arginfo_git_get_branch, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, getWalker, arginfo_git_walker, ZEND_ACC_PUBLIC) // FIXME
    PHP_ME(git_repository, getTree, arginfo_git_get_tree, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, init, arginfo_git_init, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(git_repository, update, arginfo_git_update, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, addBackend, arginfo_git_add_backend, ZEND_ACC_PUBLIC)
    PHP_ME(git_repository, open3, arginfo_git_open3, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void php_git_repository_init(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Repository", php_git_repository_methods);

    git_repository_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git_repository_class_entry->create_object = php_git_repository_new;
}
