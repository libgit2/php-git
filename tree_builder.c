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

PHPAPI zend_class_entry *git2_tree_builder_class_entry;

static void php_git2_tree_builder_free_storage(php_git2_tree_builder *object TSRMLS_DC)
{
	if (object->builder!= NULL) {
		git_treebuilder_free(object->builder);
		object->builder = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_tree_builder_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_tree_builder);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_builder___construct, 0,0,0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_builder_insert, 0,0,0)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_builder_remove, 0,0,0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_builder_write, 0,0,0)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\TreeBuilder::__construct()
*/
PHP_METHOD(git2_tree_builder, __construct)
{
	git_treebuilder *builder;
	php_git2_tree_builder *m_builder;
	
	git_treebuilder_create(&builder, NULL);
	m_builder = PHP_GIT2_GET_OBJECT(php_git2_tree_builder, getThis());
	m_builder->builder = builder;
}
/* }}} */

/*
{{{ proto: Git2\TreeBuilder::insert(Git2\TreeEntry $entry)
*/
PHP_METHOD(git2_tree_builder, insert)
{
	zval *z_name, *z_oid, *z_attributes, *m_entry = NULL;
	php_git2_tree_builder *m_builder;
	git_oid oid;
	int error = 0;
	unsigned int attributes = 0;
	char *name;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"z", &m_entry) == FAILURE) {
		return;
	}

	z_name       =  zend_read_property(git2_tree_entry_class_entry, m_entry,"name",sizeof("name")-1, 0 TSRMLS_CC);
	z_oid        =  zend_read_property(git2_tree_entry_class_entry, m_entry,"oid",sizeof("oid")-1, 0 TSRMLS_CC);
	z_attributes =  zend_read_property(git2_tree_entry_class_entry, m_entry,"attributes",sizeof("attributes")-1, 0 TSRMLS_CC);
	
	name = Z_STRVAL_P(z_name);
	attributes = (unsigned int)Z_LVAL_P(z_attributes);
	
	git_oid_fromstrn(&oid, Z_STRVAL_P(z_name), Z_STRLEN_P(z_name));
	error = git_treebuilder_insert(NULL, m_builder->builder, name, &oid, attributes);
}
/* }}} */

/*
{{{ proto: Git2\TreeBuilder::remove()
*/
PHP_METHOD(git2_tree_builder, remove)
{
}
/* }}} */

/*
{{{ proto: Git2\TreeBuilder::write()
*/
PHP_METHOD(git2_tree_builder, write)
{
}
/* }}} */

/*
{{{ proto: Git2\TreeBuilder::clear()
*/
PHP_METHOD(git2_tree_builder, clear)
{
}
/* }}} */

static zend_function_entry php_git2_tree_builder_methods[] = {
	PHP_ME(git2_tree_builder, __construct, arginfo_git2_tree_builder___construct, ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree_builder, insert,      arginfo_git2_tree_builder_insert, ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree_builder, remove,      arginfo_git2_tree_builder_remove, ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree_builder, clear,       NULL,                             ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree_builder, write,       arginfo_git2_tree_builder_write,  ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_tree_builder_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "TreeBuilder", php_git2_tree_builder_methods);
	git2_tree_builder_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_tree_builder_class_entry->create_object = php_git2_tree_builder_new;
}