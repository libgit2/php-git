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

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()


static void php_git_tag_free_storage(php_git_tag_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    if(obj->tag){
        obj->tag = NULL;
    }
    efree(obj);
}

zend_object_value php_git_tag_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_signature_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_tag_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

PHP_METHOD(git_tag, getMessage)
{
    zval *message = zend_read_property(git_tag_class_entry, getThis(),"message",7, 0 TSRMLS_CC);
    RETVAL_STRING(message,0);
}

PHP_METHOD(git_tag, getName)
{
    zval *name = zend_read_property(git_tag_class_entry, getThis(),"name",4, 0 TSRMLS_CC);
    RETVAL_STRING(name,0);
}

PHP_METHOD(git_tag, getType)
{
    zval *type = zend_read_property(git_tag_class_entry, getThis(),"type",4, 0 TSRMLS_CC);
    RETVAL_LONG(type);
}



PHP_METHOD(git_tag, __construct)
{
    php_git_tag_t *this = (php_git_tag_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    php_git_repository_t *r_obj;
    zval *repository;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &repository) == FAILURE){
        return;
    }

    if(!instanceof_function(Z_OBJCE_P(repository), git_repository_class_entry TSRMLS_CC)){
        // FIXME
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git\\Tag parameter only allow Git\\Repository.");
        return;
    }
    r_obj = (php_git_repository_t *) zend_object_store_get_object(repository TSRMLS_CC);
    git_tag_new(this->tag,r_obj->repository);
}


PHPAPI function_entry php_git_tag_methods[] = {
    PHP_ME(git_tag, __construct, arginfo_git_tag__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_tag, getMessage,  NULL,                       ZEND_ACC_PUBLIC)
    PHP_ME(git_tag, getName,     NULL,                       ZEND_ACC_PUBLIC)
    PHP_ME(git_tag, getType,     NULL,                       ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_tag(TSRMLS_D)
{
    zend_class_entry git_tag_ce;
    INIT_NS_CLASS_ENTRY(git_tag_ce, PHP_GIT_NS,"Tag", php_git_tag_methods);
    git_tag_class_entry = zend_register_internal_class(&git_tag_ce TSRMLS_CC);
    git_tag_class_entry->create_object = php_git_tag_new;

    zend_declare_property_null(git_tag_class_entry, "target", sizeof("target")-1,  ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_tag_class_entry, "name",   sizeof("name")-1,    ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_tag_class_entry, "tagger", sizeof("tagger")-1,  ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_tag_class_entry, "message",sizeof("message")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
}