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

PHPAPI zend_class_entry *git_tree_builder_class_entry;

static void php_git_tree_builder_free_storage(php_git_tree_builder_t *obj TSRMLS_DC)
{
    if(obj->builder){
        git_treebuilder_free(obj->builder);
    }
    if(obj->repository){
        obj->repository = NULL;
    }
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    efree(obj);
}

zend_object_value php_git_tree_builder_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_tree_builder_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_tree_builder_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_builder__construct, 0, 0, 1)
  ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_builder_add, 0, 0, 2)
  ZEND_ARG_INFO(0, hash)
  ZEND_ARG_INFO(0, path)
  ZEND_ARG_INFO(0, attribute)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_builder_remove, 0, 0, 1)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

PHP_METHOD(git_tree_builder, __construct)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *ztree;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &ztree) == FAILURE){
        return;
    }

    if(!instanceof_function(Z_OBJCE_P(ztree), git_tree_class_entry TSRMLS_CC)){
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"argment does not Git\\Tree instance.");
        RETURN_LONG(GIT_ERROR);
    }

    php_git_tree_t *tree = (php_git_tree_t *) zend_object_store_get_object(ztree TSRMLS_CC);

    git_treebuilder *builder;
    if(git_treebuilder_create(&builder,tree->object) != GIT_SUCCESS) {
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"can't create tree builder instance");
        RETURN_LONG(GIT_ERROR);
    }

    this->builder = builder;
    this->repository = tree->repository;
}


PHP_METHOD(git_tree_builder,add)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int error = GIT_ERROR;
    char *hash, *path;
    int hash_len, path_len = 0;
    unsigned int attributes;
    git_oid id;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "ssl", &hash,&hash_len,&path,&path_len,&attributes) == FAILURE){
        return;
    }

    error = git_oid_fromstr(&id, hash);
    if (error != GIT_SUCCESS) {
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"can't create object id.");
        RETURN_FALSE;
    }

    error = git_treebuilder_insert(NULL,this->builder,path,&id,attributes);
    if (error != GIT_SUCCESS) {
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"can't add entry");
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

PHP_METHOD(git_tree_builder,remove)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *path;
    int path_len = 0;
    int error = GIT_ERROR;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &path,&path_len) == FAILURE){
        return;
    }
    
    if (path_len < 1) {
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"must specify target.");
        RETURN_FALSE;
    }

    error = git_treebuilder_remove(this->builder,path);

    if (error == GIT_SUCCESS) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}

PHP_METHOD(git_tree_builder,write)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char out[GIT_OID_HEXSZ+1];
    git_oid oid;
    int error = GIT_ERROR;

    error = git_treebuilder_write(&oid,this->repository,this->builder);
    if(error != GIT_SUCCESS) {
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"can't write tree");
        RETURN_FALSE;
    }

    git_oid_to_string(out,GIT_OID_HEXSZ+1,&oid);
    RETVAL_STRING(out, 1);
}

static zend_function_entry php_git_tree_builder_methods[] = {
    PHP_ME(git_tree_builder, __construct, arginfo_git_tree_builder__construct,ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_builder, add,         arginfo_git_tree_builder_add,       ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_builder, remove,      arginfo_git_tree_builder_remove,    ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_builder, write,       NULL,                               ZEND_ACC_PUBLIC)
    {NULL,NULL,NULL}
};

void git_tree_builder_init(TSRMLS_D)
{
    zend_class_entry git_tree_builder_ce;
    INIT_NS_CLASS_ENTRY(git_tree_builder_ce, PHP_GIT_NS,"TreeBuilder", php_git_tree_builder_methods);
    git_tree_builder_class_entry  = zend_register_internal_class(&git_tree_builder_ce TSRMLS_CC);
    git_tree_builder_class_entry->create_object = php_git_tree_builder_new;
}
