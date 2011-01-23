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

PHPAPI zend_class_entry *git_object_class_entry;

static void php_git_object_free_storage(php_git_object_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);

    if(obj->object){
        obj->object = NULL;
    }

    efree(obj);
}

zend_object_value php_git_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_object_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_object_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}


PHP_METHOD(git_object, getId)
{
    php_git_object_t *this = (php_git_object_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid *oid;
    char out[40];

    oid = git_object_id((git_object *)this->object);
    git_oid_to_string(out,GIT_OID_HEXSZ+1,oid);
    
    RETVAL_STRING(out,1);
}

PHP_METHOD(git_object, getType)
{
    php_git_object_t *this = (php_git_object_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_otype type;

    type = git_object_type((git_object *)this->object);
    
    RETVAL_LONG(type);
}

PHP_METHOD(git_object, write)
{
    php_git_object_t *this = (php_git_object_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid *oid;
    char out[40];
    int ret = 0;

    ret = git_object_write((git_object *)this->object);
    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,
            "Can't write object:%d:",ret);
        RETURN_FALSE;
    }

    oid = git_object_id((git_object *)this->object);
    git_oid_to_string(out,41,oid);
    
    RETVAL_STRING(out,1);
}

PHPAPI function_entry php_git_object_methods[] = {
    PHP_ME(git_object, getId,   NULL,ZEND_ACC_PUBLIC)
    PHP_ME(git_object, getType, NULL,ZEND_ACC_PUBLIC)
    PHP_ME(git_object, write,   NULL,ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_object(TSRMLS_D)
{
    zend_class_entry git_object_ce;
    INIT_NS_CLASS_ENTRY(git_object_ce, PHP_GIT_NS,"Object", php_git_object_methods);
    git_object_class_entry = zend_register_internal_class(&git_object_ce TSRMLS_CC);
    git_object_class_entry->create_object = php_git_object_new;
}