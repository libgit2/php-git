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

PHPAPI zend_class_entry *git_blob_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_load_string, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_load_file, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()


static void php_git_blob_free_storage(php_git_blob_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);

    if (obj->object != NULL) {
        git_object_close(obj->object);
        obj->object = NULL;
    }
    if(obj->contents != NULL) {
        efree(obj->contents);
        obj->contents = NULL;
    }

    efree(obj);
}

zend_object_value php_git_blob_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_blob_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_blob_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();

    return retval;
}



PHP_METHOD(git_blob, __construct)
{
    zval *z_repository;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }

    php_git_repository_t *git = (php_git_repository_t *) zend_object_store_get_object(z_repository TSRMLS_CC);
    php_git_blob_t *obj = (php_git_blob_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    obj->repository = git->repository;
}

static int php_git_blob_common_load(enum php_git_blob_write_type type,INTERNAL_FUNCTION_PARAMETERS)
{
    php_git_blob_t *this = (php_git_blob_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *contents;
    int contents_len = 0;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &contents, &contents_len) == FAILURE) {
        return -1;
    }

    if(contents_len <= 0) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"can't set null string.");
        return -1;
    }

    this->type = type;
    this->contents = estrndup(contents,contents_len);
    this->contents_len = contents_len;

    return 0;
}

PHP_METHOD(git_blob, loadFile)
{
    php_git_blob_common_load(PHP_GIT_LOAD_FROM_FILE,INTERNAL_FUNCTION_PARAM_PASSTHRU);
    RETURN_TRUE;
}

PHP_METHOD(git_blob, loadString)
{
    php_git_blob_common_load(PHP_GIT_LOAD_FROM_STRING,INTERNAL_FUNCTION_PARAM_PASSTHRU);
    RETURN_TRUE;
}

PHP_METHOD(git_blob, write)
{
    php_git_blob_t *this = (php_git_blob_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid out;
    int ret = 0;

    if (this->type == PHP_GIT_LOAD_FROM_STRING) {
        ret = git_blob_create_frombuffer(&out,this->repository,this->contents,this->contents_len);
        if(ret != GIT_SUCCESS) {
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"can't write blob.");
            RETURN_FALSE;
        }
    } else if(this->type == PHP_GIT_LOAD_FROM_FILE) {
        ret = git_blob_create_fromfile(&out,this->repository,this->contents);
        if(ret != GIT_SUCCESS) {
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"can't write blob.");
            RETURN_FALSE;
        }
    }

    char oid_str[GIT_OID_HEXSZ+1] = {0};
    git_oid_to_string(oid_str,GIT_OID_HEXSZ+1,&out);
    RETVAL_STRING(oid_str,1);
}

static zend_function_entry php_git_blob_methods[] = {
    PHP_ME(git_blob, __construct, arginfo_git_blob__construct,  ZEND_ACC_PUBLIC)
    PHP_ME(git_blob, loadString,  arginfo_git_blob_load_string, ZEND_ACC_PUBLIC)
    PHP_ME(git_blob, loadFile,  arginfo_git_blob_load_file, ZEND_ACC_PUBLIC)
    PHP_ME(git_blob, write,       NULL,                         ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_blob(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Blob", php_git_blob_methods);

    git_blob_class_entry = zend_register_internal_class_ex(&ce, git_object_class_entry, NULL TSRMLS_CC);
    git_blob_class_entry->create_object = php_git_blob_new;
}
