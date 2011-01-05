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

extern zend_object_value php_git_repository_new(zend_class_entry *ce TSRMLS_DC);


static void php_git_commit_free_storage(php_git_commit_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    //RepositoryでFreeされるよ
    obj->commit = NULL;
    obj->repository = NULL;
    efree(obj);
}

zend_object_value php_git_commit_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_commit_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_commit_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

//GitCommit
ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, __construct)
{
    zval *z_repository;
    git_commit *commit;
    git_repository *repository;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }
    object_init_ex(object, git_commit_class_entry);
    php_git_commit_t *cobj = (php_git_commit_t *) zend_object_store_get_object(object TSRMLS_CC);
    php_git_t *myobj = (php_git_t *) zend_object_store_get_object(z_repository TSRMLS_CC);

    
    ret = git_commit_new(&commit,myobj->repository);
    if(ret != GIT_SUCCESS){
        //FIXME
        RETURN_FALSE;
    }
    cobj->repository = myobj->repository;
    cobj->commit = commit;
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_committer, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setCommitter)
{
    zval *this = getThis();
    zval *z_signature;
    git_signature *signature;
    php_git_commit_t *c_obj;
    php_git_signature_t *s_obj;
    git_commit *commit;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_signature) == FAILURE){
        return;
    }

    c_obj = (php_git_commit_t *) zend_object_store_get_object(this TSRMLS_CC);
    s_obj = (php_git_signature_t *) zend_object_store_get_object(z_signature TSRMLS_CC);
    git_commit_set_author(c_obj->commit, s_obj->signature);
    add_property_zval_ex(object,"committer",10,z_signature);
}

PHP_METHOD(git_commit, getCommitter)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"committer",9, 0 TSRMLS_CC);
    RETURN_ZVAL(signature,0, 0);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_author, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setAuthor)
{
    zval *this = getThis();
    zval *z_signature;
    git_signature *signature;
    php_git_commit_t *c_obj;
    php_git_signature_t *s_obj;
    git_commit *commit;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_signature) == FAILURE){
        return;
    }

    c_obj = (php_git_commit_t *) zend_object_store_get_object(this TSRMLS_CC);
    s_obj = (php_git_signature_t *) zend_object_store_get_object(z_signature TSRMLS_CC);
    git_commit_set_committer(c_obj->commit, s_obj->signature);
    add_property_zval_ex(object,"author",7,z_signature);
}

PHP_METHOD(git_commit, write)
{
    zval *this = getThis();
    git_repository *repository;
    git_commit *commit;

    php_git_commit_t *myobj = (php_git_commit_t *) zend_object_store_get_object(this TSRMLS_CC);
    repository = myobj->repository;

    git_commit_new(&commit,repository);
    zval *author = zend_read_property(git_commit_class_entry,this,"author",sizeof("author")-1,0 TSRMLS_CC);
    
    
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setTree)
{
    zval *object = getThis();
    char *hash;
    int hash_len;
    char *filename;
    git_oid oid;
    git_tree *tree;
    git_repository *repository;
    git_object *git_obj;
    int attr;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }

    php_git_commit_t *myobj = (php_git_commit_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    git_oid_mkstr(&oid, hash);
    git_repository_lookup (&tree, repository, &oid, GIT_OBJ_TREE);
    if(tree){
        //コピペ
        zval *git_tree;
        zval *entries;
        git_tree_entry *entry;
        MAKE_STD_ZVAL(git_tree);
        MAKE_STD_ZVAL(entries);
        array_init(entries);
        object_init_ex(git_tree, git_tree_class_entry);

        int r = git_tree_entrycount(tree);
        int i = 0;
        char mbuf[40];
        char *offset;
        git_oid *moid;
        zval *array_ptr;

        for(i; i < r; i++){
            entry = git_tree_entry_byindex(tree,i);
            moid = git_tree_entry_id(entry);
            git_oid_to_string(mbuf,41,moid);

            MAKE_STD_ZVAL(array_ptr);
            object_init_ex(array_ptr, git_tree_entry_class_entry);

            add_property_string(array_ptr, "name", git_tree_entry_name(entry), 1);
            add_property_string(array_ptr, "oid", mbuf, 1);
            add_property_long(array_ptr, "attr", git_tree_entry_attributes(entry));

            add_next_index_zval(entries,  array_ptr);
        }

        //add_property_long(git_tree, "entry", git_tree_entrycount(tree));
        add_property_zval(git_tree,"entries", entries);
        add_property_zval(object,"tree",git_tree);
        //

        RETURN_TRUE;
    }
    //
}


PHP_METHOD(git_commit, getAuthor)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"author",6, 0 TSRMLS_CC);
    RETURN_ZVAL(signature,0, 0);
}

PHPAPI function_entry php_git_commit_methods[] = {
    PHP_ME(git_commit, __construct,  arginfo_git_commit__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setTree,  arginfo_git_commit_set_tree, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setAuthor,  arginfo_git_commit_set_author, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getAuthor, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setCommitter,  arginfo_git_commit_set_committer, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getCommitter,  NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, write, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_commit(TSRMLS_C)
{
    zend_class_entry git_commit_ce;
    INIT_CLASS_ENTRY(git_commit_ce, "GitCommit", php_git_commit_methods);
    git_commit_class_entry = zend_register_internal_class(&git_commit_ce TSRMLS_CC);
	git_commit_class_entry->create_object = php_git_commit_new;
    zend_declare_property_null(git_commit_class_entry, "author",sizeof("author")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "committer",sizeof("committer")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
}