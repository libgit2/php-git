/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2012 Shuhei Tanuma
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

#include "php_git2.h"

PHPAPI zend_class_entry *git2_raw_class_entry;
static zend_object_handlers git2_raw_object_handlers;

static void php_git2_raw_free_storage(php_git2_raw *object TSRMLS_DC)
{
	if (object->object != NULL) {
		git_odb_object_free(object->object);
		object->object = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_raw_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_raw);
	retval.handlers = &git2_raw_object_handlers;
	return retval;
}

static int php_git2_raw_cast_object_tostring(zval *readobj, zval *writeobj, int type TSRMLS_DC)
{
	zval *retval;
	zend_class_entry *ce;
	php_git2_raw *m_raw;

	switch (type) {
		case IS_STRING:
			m_raw = PHP_GIT2_GET_OBJECT(php_git2_raw, readobj);
			INIT_PZVAL(writeobj);
			ZVAL_STRINGL(writeobj,git_odb_object_data(m_raw->object),git_odb_object_size(m_raw->object),1);
			return SUCCESS;
		case IS_BOOL:
			INIT_PZVAL(writeobj);
			ZVAL_BOOL(writeobj, 1);
			return SUCCESS;
		case IS_LONG:
			ce = Z_OBJCE_P(readobj);
			zend_error(E_NOTICE, "Object of class %s could not be converted to int", ce->name);
			INIT_PZVAL(writeobj);
			if (readobj == writeobj) {
				zval_dtor(readobj);
			}
			ZVAL_LONG(writeobj, 1);
			return SUCCESS;
		case IS_DOUBLE:
			ce = Z_OBJCE_P(readobj);
			zend_error(E_NOTICE, "Object of class %s could not be converted to double", ce->name);
			INIT_PZVAL(writeobj);
			if (readobj == writeobj) {
				zval_dtor(readobj);
			}
			ZVAL_DOUBLE(writeobj, 1);
			return SUCCESS;
		default:
			INIT_PZVAL(writeobj);
			Z_TYPE_P(writeobj) = IS_NULL;
			break;
	}
	return FAILURE;
}


/*
{{{ proto: Git2\raw::getContent()
*/
PHP_METHOD(git2_raw, getContent)
{
	php_git2_raw *m_raw;
	git_otype type;
	
	m_raw = PHP_GIT2_GET_OBJECT(php_git2_raw,getThis());
	RETVAL_STRINGL(git_odb_object_data(m_raw->object),git_odb_object_size(m_raw->object),1);
}
/* }}} */


/*
{{{ proto: Git2\raw::getType()
*/
PHP_METHOD(git2_raw, getType)
{
	php_git2_raw *m_raw;
	git_otype type;
	
	m_raw = PHP_GIT2_GET_OBJECT(php_git2_raw,getThis());
	
	type = git_odb_object_type(m_raw->object);
	RETURN_LONG(type);
}
/* }}} */


static zend_function_entry php_git2_raw_methods[] = {
	PHP_ME(git2_raw, getContent, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_raw, getType, NULL, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_raw_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Raw", php_git2_raw_methods);
	git2_raw_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_raw_class_entry->create_object = php_git2_raw_new;

	memcpy(&git2_raw_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	git2_raw_object_handlers.clone_obj = NULL;
	git2_raw_object_handlers.cast_object = php_git2_raw_cast_object_tostring;
}