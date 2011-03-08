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

PHPAPI zend_class_entry *git_rawobject_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_rawobject_set_content, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_rawobject__construct, 0, 0, 2)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

static void php_git_rawobject_free_storage(php_git_rawobject_t *obj TSRMLS_DC)
{
    if(obj->object->data){
        efree(obj->object->data);
        obj->object->data = NULL;
    }

    if(obj->object){
        efree(obj->object);
        obj->object= NULL;
    }

    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    efree(obj);
}

zend_object_value php_git_rawobject_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_rawobject_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_rawobject_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

PHP_METHOD(git_raw_object, __construct)
{
    char *data;
    int data_len = 0;
    int type = 0;
    int len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "lsl", &type, &data, &data_len, &len) == FAILURE){
        return;
    }
    php_git_rawobject_t *this= (php_git_rawobject_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    this->object = emalloc(sizeof(git_rawobj));
    this->object->data = NULL;
    this->object->type = type;
    this->object->len  = len;
    this->object->data = emalloc(len);
    memcpy(this->object->data,data,len);

    add_property_stringl_ex(getThis(), "data",sizeof("data"),data,len,1 TSRMLS_CC);
    add_property_long(getThis(), "type",type);
    add_property_long(getThis(), "len",len);
}

PHP_METHOD(git_raw_object, getId)
{
    php_git_rawobject_t *this = (php_git_rawobject_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid oid;
    char out[GIT_OID_HEXSZ+1] = {0};

    git_rawobj_hash(&oid,this->object);
    git_oid_to_string(out,GIT_OID_HEXSZ+1,&oid);

    RETVAL_STRING(out,1);
}


PHPAPI function_entry php_git_rawobject_methods[] = {
    PHP_ME(git_raw_object, __construct, arginfo_git_rawobject__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_raw_object, getId,       NULL,                             ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_rawobject(TSRMLS_D)
{
    zend_class_entry git_rawobject_ce;
    INIT_NS_CLASS_ENTRY(git_rawobject_ce, PHP_GIT_NS,"RawObject", php_git_rawobject_methods);

    git_rawobject_class_entry = zend_register_internal_class(&git_rawobject_ce TSRMLS_CC);
	git_rawobject_class_entry->create_object = php_git_rawobject_new;
}