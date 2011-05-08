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

PHPAPI zend_class_entry *git_walker_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker_hide, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker_push, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker_sort, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

static void php_git_walker_free_storage(php_git_walker_t *obj TSRMLS_DC)
{
    if(obj->walker != NULL){
        git_revwalk_free(obj->walker);
        obj->walker = NULL;
    }
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    efree(obj);
}

zend_object_value php_git_walker_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_walker_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_walker_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

PHP_METHOD(git_walker, __construct)
{
}

PHP_METHOD(git_walker, hide)
{
    char *hash;
    int hash_len = 0;
    git_revwalk *walker;
    git_commit *commit;
    git_repository *repository;
    git_oid oid;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }

    php_git_walker_t *myobj = (php_git_walker_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    walker = myobj->walker;

    repository = git_revwalk_repository(walker);
    
    git_oid_mkstr(&oid,hash);

    git_revwalk_hide(walker,&oid);
}

PHP_METHOD(git_walker, push)
{
    char *hash;
    int hash_len = 0;
    git_oid oid;
    git_commit *head;
    git_revwalk *walker;
    git_repository *repository;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }

    php_git_walker_t *myobj = (php_git_walker_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    walker = myobj->walker;
    repository = git_revwalk_repository(walker);
    
    git_oid_mkstr(&oid,hash);
    
    git_revwalk_push(walker,&oid);
}


PHP_METHOD(git_walker, next)
{
    zval *git_commit_object;
    char *hash;
    int hash_len = 0;
    git_oid oid;
    git_commit *commit;
    git_revwalk *walker;
    git_signature *signature;
    zval *parents;

    php_git_walker_t *myobj = (php_git_walker_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    walker = myobj->walker;

    int ret = git_revwalk_next(&oid,walker);
    if(ret != GIT_SUCCESS){
        RETURN_FALSE;
    }
    git_object_lookup((git_object **)&commit, git_revwalk_repository(walker), &oid, GIT_OBJ_COMMIT);

    MAKE_STD_ZVAL(git_commit_object);
    object_init_ex(git_commit_object,git_commit_class_entry);

    zval *author;
    zval *committer;

    create_signature_from_commit(&author, git_commit_author(commit));
    create_signature_from_commit(&committer, git_commit_committer(commit));
    
    MAKE_STD_ZVAL(git_commit_object);
    object_init_ex(git_commit_object,git_commit_class_entry);

    php_git_commit_t *cobj = (php_git_commit_t *) zend_object_store_get_object(git_commit_object TSRMLS_CC);
    cobj->object = commit;

    add_property_zval(git_commit_object,"author", author);
    add_property_zval(git_commit_object,"committer", committer);

    
    add_property_string_ex(git_commit_object,"tree",sizeof("tree"),git_oid_allocfmt(git_commit_tree_oid(commit)), 1 TSRMLS_CC);

    int parent_count = git_commit_parentcount(commit);
    int i;

    MAKE_STD_ZVAL(parents);
    array_init(parents);
    for (i = 0; i < parent_count; i++) {
        add_next_index_string(parents,git_oid_allocfmt(git_commit_parent_oid(commit,i)),1);
    }
    
    add_property_string_ex(git_commit_object,"message",sizeof("message"),git_commit_message(commit), 1 TSRMLS_CC);
    add_property_zval_ex(git_commit_object,"parents",sizeof("parents"),parents TSRMLS_CC);

    RETURN_ZVAL(git_commit_object,0,1);
}


PHP_METHOD(git_walker, reset)
{
    php_git_walker_t *myobj = (php_git_walker_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_revwalk_reset(myobj->walker);
    RETURN_TRUE;
}

PHP_METHOD(git_walker, sort)
{
    int mode = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "l", &mode) == FAILURE){
        return;
    }

    php_git_walker_t *myobj = (php_git_walker_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_revwalk_sorting(myobj->walker, mode);
    RETURN_TRUE;
}

PHPAPI function_entry php_git_walker_methods[] = {
    PHP_ME(git_walker, __construct, NULL,                    ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, push,        arginfo_git_walker_push, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, next,        NULL,                    ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, hide,        arginfo_git_walker_hide, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, reset,       NULL,                    ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, sort,        arginfo_git_walker_sort, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_walker(TSRMLS_D)
{
    zend_class_entry git_walker_ce;
    INIT_NS_CLASS_ENTRY(git_walker_ce, PHP_GIT_NS,"Revwalk", php_git_walker_methods);
    git_walker_class_entry = zend_register_internal_class(&git_walker_ce TSRMLS_CC);
    git_walker_class_entry->create_object = php_git_walker_new;
}
