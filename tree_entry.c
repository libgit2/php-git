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

PHPAPI zend_class_entry *git2_tree_entry_class_entry;

static void php_git2_tree_entry_free_storage(php_git2_tree_entry *object TSRMLS_DC)
{
	if (object->entry != NULL) {
		git_tree_entry_free(object->entry);
		object->entry = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_tree_entry_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_tree_entry);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_entry___construct, 0,0,1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\TreeEntry::__construct([array $entry])
*/
PHP_METHOD(git2_tree_entry, __construct)
{
	zval *z_entry= NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|z", &z_entry) == FAILURE) {
		return;
	}

	if (z_entry != NULL) {
		zval **zvalue = NULL;
		zval *zvaluep = NULL;
		
		if (zend_hash_find(Z_ARRVAL_P(z_entry),"name",sizeof("name"),(void **)&zvalue) != FAILURE) {
			zvaluep = *zvalue;
			add_property_string_ex(getThis(), "name",sizeof("name"),Z_STRVAL_P(zvaluep) ,1 TSRMLS_CC);
			zvalue = NULL;
			zvaluep = NULL;
		}
		if (zend_hash_find(Z_ARRVAL_P(z_entry),"attributes",sizeof("attributes"),(void **)&zvalue) != FAILURE) {
			zvaluep = *zvalue;
			add_property_long_ex(getThis(), "attributes",sizeof("attributes"),Z_LVAL_P(zvaluep) TSRMLS_CC);
			zvalue = NULL;
			zvaluep = NULL;
		}
		if (zend_hash_find(Z_ARRVAL_P(z_entry),"oid",sizeof("oid"),(void **)&zvalue) != FAILURE) {
			zvaluep = *zvalue;
			add_property_string_ex(getThis(), "oid",sizeof("oid"),Z_STRVAL_P(zvaluep),1 TSRMLS_CC);
			zvalue = NULL;
			zvaluep = NULL;
		}
	}
}
/* }}} */



static zend_function_entry php_git2_tree_entry_methods[] = {
	PHP_ME(git2_tree_entry, __construct, arginfo_git2_tree_entry___construct, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_tree_entry_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "TreeEntry", php_git2_tree_entry_methods);
	git2_tree_entry_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_tree_entry_class_entry->create_object = php_git2_tree_entry_new;

	zend_declare_property_null(git2_tree_entry_class_entry, "name", sizeof("name")-1,             ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(git2_tree_entry_class_entry, "oid", sizeof("oid")-1,               ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(git2_tree_entry_class_entry, "attributes", sizeof("attributes")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
}