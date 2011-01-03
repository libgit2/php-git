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

static void php_git_free_storage(php_git_t *obj TSRMLS_DC)
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
	php_git_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();

	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_init, 0, 0, 2)
    ZEND_ARG_INFO(0, path)
    ZEND_ARG_INFO(0, is_bare)
ZEND_END_ARG_INFO()
PHP_METHOD(git, init)
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

    int suc = git_repository_init(&repository,"/tmp/uhi",is_bare);

    if(suc != 0){
        php_printf("can't create repository\n");
        return;
    }
    
    MAKE_STD_ZVAL(obj);
    object_init_ex(obj, git_class_entry);
    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(obj TSRMLS_CC);
    myobj->repository = repository;

    add_property_string_ex(obj, "path",5,path, 1 TSRMLS_CC);
    RETURN_ZVAL(obj, 1, 0);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_string_to_type, 0, 0, 1)
    ZEND_ARG_INFO(0, string_type)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_string_to_type)
{
    const char *string_type = NULL;
    int string_len = 0;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &string_type, &string_len) == FAILURE){
        return;
    }

    RETVAL_LONG(git_object_string2type(string_type))
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_type_to_string, 0, 0, 1)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_type_to_string)
{
    git_otype t;
    int type;
    const char *str;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "l", &type) == FAILURE){
        return;
    }
    t = (git_otype)type;
    str = git_object_type2string(t);

    RETVAL_STRING(str,1);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_hex_to_raw, 0, 0, 1)
    ZEND_ARG_INFO(0, hex)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_hex_to_raw)
{
    git_oid oid;

    const char *hex = NULL;
    int hex_len = 0;
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hex, &hex_len) == FAILURE){
        return;
    }
    
    git_oid_mkstr(&oid, hex);
    RETVAL_STRINGL((&oid)->id,GIT_OID_RAWSZ,1);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_raw_to_hex, 0, 0, 1)
    ZEND_ARG_INFO(0, raw)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_raw_to_hex)
{
    git_oid oid;
    const char *raw = NULL;
    char out[GIT_OID_HEXSZ];
    int raw_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",
        &raw, &raw_len) == FAILURE){
        return;
    }
    
    git_oid_mkraw(&oid, raw);
    git_oid_fmt(out, &oid);

    RETVAL_STRINGL(out,GIT_OID_HEXSZ,1);
}


PHP_METHOD(git, getIndex)
{
    zval *object = getThis();
    git_repository *repository;
    git_index *index;
    //FIXME: GitIndexを呼びたいけどコレでいいの？
    zval *index_object = emalloc(sizeof(zval));
    int ret = 0;

    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);


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

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_object, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getObject)
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
    
    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;
    
    odb = git_repository_database(repository);
    
    if(git_odb_exists(odb,hash)){
        RETURN_FALSE;
    }else{
        ret = git_blob_lookup(&blob, repository,&oid);
        
        if(ret == GIT_SUCCESS){
            MAKE_STD_ZVAL(git_raw_object);
            object_init_ex(git_raw_object, git_blob_class_entry);
            php_git_blob_t *blobobj = (php_git_blob_t *) zend_object_store_get_object(git_raw_object TSRMLS_CC);
            blobobj->repository = repository;
            blobobj->blob = blob;

            add_property_string_ex(git_raw_object,"data", 5, git_blob_rawcontent(blob), 1 TSRMLS_CC);
            RETURN_ZVAL(git_raw_object,0,0);
        }else{
            RETURN_FALSE;
        }
    }
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_commit, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getCommit)
{
    zval *object = getThis();
    zval *git_raw_object;
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
    
    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;
    odb = git_repository_database(repository);
    
    if(git_odb_exists(odb,hash)){
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
                git_oid_fmt(buf,moid);

                MAKE_STD_ZVAL(array_ptr);
                object_init_ex(array_ptr, git_tree_entry_class_entry);

                add_property_string(array_ptr, "name", git_tree_entry_name(entry), 1);
                add_property_string(array_ptr, "oid", buf, 1);
                add_property_long(array_ptr, "attr", git_tree_entry_attributes(entry));

                add_next_index_zval(entries,  array_ptr);
            }

            php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
            tobj->repository = repository;
            tobj->tree = tree;

            add_property_zval(git_tree,"entries", entries);
            add_property_zval(git_raw_object,"tree", git_tree);
            
            RETURN_ZVAL(git_raw_object,1,0);
        }else{
            RETURN_FALSE;
        }
    }
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

PHP_METHOD(git, __construct)
{
    const char *repository_path = NULL;
    int ret = 0;
    int arg_len = 0;
    git_repository *repository;
    zval *object = getThis();

    object_init_ex(object, git_class_entry);

    if(!object){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,
            "Constructor called statically!");
        RETURN_FALSE;
    }

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                            "s", &repository_path, &arg_len) == FAILURE){
        return;
    }

    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);

    ret = git_repository_open(&repository,repository_path);
    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git repository not found.");
        RETURN_FALSE;
    }
    myobj->repository = repository;

    add_property_string_ex(object, "path",5,repository_path, 1 TSRMLS_CC);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getTree)
{
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
    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);
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
    tobj->tree = tree;

    add_property_zval(git_tree,"entries", entries);

    RETURN_ZVAL(git_tree,1,0);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getWalker)
{
    zval *object = getThis();
    git_repository *repository;
    git_index *index;
    //FIXME: GitWalkerを呼びたいけどコレでいいの？
    zval *walker_object = emalloc(sizeof(zval));
    git_revwalk *walk;
    int ret = 0;

    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    object_init_ex(walker_object, git_walker_class_entry);
    ret = git_revwalk_new(&walk,repository);
    php_git_walker_t *wobj = (php_git_walker_t *) zend_object_store_get_object(walker_object TSRMLS_CC);
    wobj->walker = walk;
    wobj->repository = repository;

    RETURN_ZVAL(walker_object,1,0);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_branch, 0, 0, 1)
    ZEND_ARG_INFO(0, branch)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getBranch)
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

    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    prop = zend_read_property(git_class_entry,object,"path",4,0 TSRMLS_DC);
    char *uhi = Z_STRVAL_P(prop);
    
    //FIXME: 適当すぎる
    FILE *fp;
    sprintf(&buf,"%s/refs/heads/%s",uhi,branch);
    fp = fopen(&buf,"r");
    memset(buf,0,sizeof(buf));
    fread(buf,1,40,fp);
    fclose(fp);
    
    RETVAL_STRINGL(buf,40,1 TSRMLS_DC);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_write_object, 0, 0, 1)
    ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

PHP_METHOD(git, writeObject)
{
    zval *object = getThis();
    git_repository *repository;
    git_odb *odb;
    git_blob *blob;
    git_oid *oid;
    zval *data;
    zval *z_git_blob;
    char *content;
    int content_len = 0;
    int ret = 0;
    char out[40];

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_git_blob) == FAILURE){
        return;
    }
    
    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    data = zend_read_property(git_blob_class_entry,z_git_blob,"data",4,0 TSRMLS_CC);
    printf("%s\n",Z_STRVAL_P(data));

    git_blob_new(&blob, repository);
    git_blob_set_rawcontent(blob, Z_STRVAL_P(data), strlen(Z_STRVAL_P(data)));
    
    ret = git_object_write((git_object *)blob);
    if(ret != GIT_SUCCESS){
        php_printf("can't write object");
    }
    
    oid = git_object_id((git_object *)blob);
    git_oid_to_string(&out,41,oid);
    
    RETVAL_STRING(&out, 1);
}


// Git
PHPAPI function_entry php_git_methods[] = {
    PHP_ME(git, __construct, arginfo_git_construct, ZEND_ACC_PUBLIC)
    PHP_ME(git, getCommit, arginfo_git_get_commit, ZEND_ACC_PUBLIC)
    PHP_ME(git, getObject, arginfo_git_get_object, ZEND_ACC_PUBLIC)
    PHP_ME(git, writeObject, arginfo_git_write_object, ZEND_ACC_PUBLIC)
    PHP_ME(git, getIndex, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git, getBranch, arginfo_git_get_branch, ZEND_ACC_PUBLIC)
    PHP_ME(git, getWalker, arginfo_git_walker, ZEND_ACC_PUBLIC) // FIXME
    PHP_ME(git, getTree, arginfo_git_get_tree, ZEND_ACC_PUBLIC)
    PHP_ME(git, init, arginfo_git_init, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

// Git Global Functions
PHPAPI function_entry php_git_functions[] = {
    PHP_FE(git_hex_to_raw, arginfo_git_hex_to_raw)
    PHP_FE(git_raw_to_hex, arginfo_git_raw_to_hex)
    PHP_FE(git_type_to_string, arginfo_git_type_to_string)
    PHP_FE(git_string_to_type, arginfo_git_string_to_type)
    {NULL, NULL, NULL}
};

void git_init(TSRMLS_D)
{
    zend_class_entry git_ce;
    INIT_CLASS_ENTRY(git_ce, "Git", php_git_methods);
    git_class_entry = zend_register_internal_class(&git_ce TSRMLS_CC);
	git_class_entry->create_object = php_git_repository_new;


    REGISTER_GIT_CONST_LONG("SORT_NONE", 0)
    REGISTER_GIT_CONST_LONG("SORT_TOPO", 1)
    REGISTER_GIT_CONST_LONG("SORT_DATE", 2)
    REGISTER_GIT_CONST_LONG("SORT_REVERSE", 4)

    REGISTER_GIT_CONST_LONG("OBJ_ANY", GIT_OBJ_ANY)
    REGISTER_GIT_CONST_LONG("OBJ_BAD", GIT_OBJ_BAD)
    REGISTER_GIT_CONST_LONG("OBJ_COMMIT", GIT_OBJ_COMMIT)
    REGISTER_GIT_CONST_LONG("OBJ_TREE", GIT_OBJ_TREE)
    REGISTER_GIT_CONST_LONG("OBJ_BLOB", GIT_OBJ_BLOB)
    REGISTER_GIT_CONST_LONG("OBJ_TAG", GIT_OBJ_TAG)
}

PHP_MINIT_FUNCTION(git) {
    git_init(TSRMLS_C);
    git_index_init(TSRMLS_C);
    git_init_signature(TSRMLS_C);
    git_init_walker(TSRMLS_C);
    git_init_tree(TSRMLS_C);
    git_init_commit(TSRMLS_C);
    git_init_tree_entry(TSRMLS_C);
    git_init_rawobject(TSRMLS_C);
    git_init_tag(TSRMLS_C);
    git_init_object(TSRMLS_C);
    git_init_blob(TSRMLS_C);

    return SUCCESS;
}


PHP_MINFO_FUNCTION(git)
{
    php_printf("PHP Git Extension\n");
    php_info_print_table_start();
    php_info_print_table_row(2,"Version", PHP_GIT_EXTVER " (development)");
    php_info_print_table_row(2, "Authors", "Shuhei Tanuma 'stanuma@zynga.co.jp' (lead)\n");
    php_info_print_table_end();
}

zend_module_entry git_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_GIT_EXTNAME,
    php_git_functions,	/* Functions */
    PHP_MINIT(git),	/* MINIT */
    NULL, 	/* MSHUTDOWN */
    NULL, 	/* RINIT */
    NULL,	/* RSHUTDOWN */
    PHP_MINFO(git),	/* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_GIT_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GIT
ZEND_GET_MODULE(git)
#endif
