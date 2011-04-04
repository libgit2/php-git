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

extern void create_tree_entry_from_entry(zval **object, git_tree_entry *entry,git_repository *repository);

PHPAPI zend_class_entry *git_tree_builder_class_entry;
extern void php_tree_index_entry_create(zval **index, git_tree_entry *entry);

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
    php_git_tree_t *tree = (php_git_tree_t *) zend_object_store_get_object(ztree TSRMLS_CC);

    git_treebuilder *builder;
    git_treebuilder_create(&builder,tree->object);
    this->builder = builder;
    this->repository = tree->repository;
}


PHP_METHOD(git_tree_builder,add)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int ret = 0;
    char *path;
    int path_len = 0;
    unsigned int attributes;
    git_tree_entry *entry;
    git_oid id;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "sl", &path,&path_len,&attributes) == FAILURE){
        return;
    }

    ret = git_treebuilder_insert(&entry,this->builder,path,&id,attributes);
    if(ret == GIT_SUCCESS) {
        RETURN_TRUE;
    }
}

PHP_METHOD(git_tree_builder,remove)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int ret = 0;
    char *path;
    int path_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "sl", &path,&path_len) == FAILURE){
        return;
    }

    ret = git_treebuilder_remove(this->builder,path);
    if(ret == GIT_SUCCESS) {
        RETURN_TRUE;
    }
}

PHP_METHOD(git_tree_builder,write)
{
    php_git_tree_builder_t *this = (php_git_tree_builder_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid oid;
    char out[GIT_OID_HEXSZ+1];

    int ret = git_treebuilder_write(&oid,this->repository,this->builder);
    if(ret == GIT_SUCCESS) {
        git_oid_to_string(out,GIT_OID_HEXSZ+1,&oid);
        RETVAL_STRING(out, 1);
    }
}

PHPAPI function_entry php_git_tree_builder_methods[] = {
    PHP_ME(git_tree_builder, __construct, arginfo_git_tree_builder__construct,ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_builder, add,         arginfo_git_tree_builder_add,       ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_builder, remove,      arginfo_git_tree_builder_remove,    ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_builder, write,       NULL,                               ZEND_ACC_PUBLIC)
};

void git_tree_builder_init(TSRMLS_D)
{
    zend_class_entry git_tree_builder_ce;
    INIT_NS_CLASS_ENTRY(git_tree_builder_ce, PHP_GIT_NS,"TreeBuilder", php_git_tree_builder_methods);
    git_tree_builder_class_entry  = zend_register_internal_class(&git_tree_builder_ce TSRMLS_CC);
    git_tree_builder_class_entry->create_object = php_git_tree_builder_new;
}
