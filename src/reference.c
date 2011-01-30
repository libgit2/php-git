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

PHPAPI zend_class_entry *git_reference_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_set_name, 0, 0, 1)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_set_target, 0, 0, 1)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_set_oid, 0, 0, 1)
    ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

static void php_git_reference_free_storage(php_git_reference_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);

    if(obj->object){
        obj->object = NULL;
    }

    efree(obj);
}

zend_object_value php_git_reference_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_tag_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_reference_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}


PHP_METHOD(git_reference, setName)
{
    php_git_reference_t *this = (php_git_reference_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *name;
    int name_len = 0;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &name, &name_len) == FAILURE){
        return;
    }

    git_reference_set_name(this->object, name);
    add_property_string_ex(getThis() ,"name",sizeof("name")+1,name, 1 TSRMLS_CC);
}

PHP_METHOD(git_reference, setTarget)
{
    php_git_reference_t *this = (php_git_reference_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *target;
    int target_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &target, &target_len) == FAILURE){
        return;
    }

    git_reference_set_target(this->object, target);
    add_property_string_ex(getThis() ,"target",sizeof("target")+1,target, 1 TSRMLS_CC);
}

PHP_METHOD(git_reference, setOID)
{
    php_git_reference_t *this = (php_git_reference_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *oid;
    git_oid out;
    int oid_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &oid, &oid_len) == FAILURE){
        return;
    }

    git_oid_mkstr(&out, oid);

    git_tag_set_oid(this->object, &out);
    add_property_string_ex(getThis() ,"oid",sizeof("oid")+1,oid, 1 TSRMLS_CC);
}


PHPAPI function_entry php_git_reference_methods[] = {
    //PHP_ME(git_reference, __construct, NULL, ZEND_ACC_PUBLIC)
    //PHP_ME(git_reference, getTarget,   NULL, ZEND_ACC_PUBLIC)
    //PHP_ME(git_reference, getName,     NULL, ZEND_ACC_PUBLIC)
    //PHP_ME(git_reference, resolve, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference, setName,     arginfo_git_reference_set_name, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference, setTarget,   arginfo_git_reference_set_target, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference, setOID,      arginfo_git_reference_set_oid, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_reference(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Reference", php_git_reference_methods);
    git_reference_class_entry = zend_register_internal_class_ex(&ce, git_object_class_entry,NULL TSRMLS_CC);
    git_reference_class_entry->create_object = php_git_reference_new;
    
    zend_declare_property_null(git_reference_class_entry, "oid",sizeof("oid")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_reference_class_entry, "name",sizeof("name")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_reference_class_entry, "target",sizeof("target")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
}