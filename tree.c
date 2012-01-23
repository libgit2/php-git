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
#include <spl/spl_array.h>
#include <zend_interfaces.h>

PHPAPI zend_class_entry *git2_tree_class_entry;

static void php_git2_tree_free_storage(php_git2_tree *object TSRMLS_DC)
{
	if (object->tree != NULL) {
		git_tree_free(object->tree);
		object->tree = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_tree_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_tree);
	object->offset = 0;
	return retval;
}


/* Iterator Implementation */

/*
{{{ proto: Git2\Tree::current()
*/
PHP_METHOD(git2_tree, current)
{
	php_git2_tree *m_tree;
	const git_tree_entry *entry;
	zval *z_entry;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	entry = git_tree_entry_byindex(m_tree->tree, m_tree->offset);
	if (entry == NULL) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
			"specified offset does not exist. %d");
		RETURN_FALSE;
	}
	create_tree_entry_from_entry(&z_entry, entry ,m_tree->repository);
	RETURN_ZVAL(z_entry, 0, 1);
}

/*
{{{ proto: Git2\Tree::key()
*/
PHP_METHOD(git2_tree, key)
{
	php_git2_tree *m_tree;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	RETURN_LONG(m_tree->offset);
}

/*
{{{ proto: Git2\Tree::valid()
*/
PHP_METHOD(git2_tree, next)
{
	php_git2_tree *m_tree;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	m_tree->offset++;
}

/*
{{{ proto: Git2\Tree::rewind()
*/
PHP_METHOD(git2_tree, rewind)
{
	php_git2_tree *m_tree;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	m_tree->offset = 0;
}

/*
{{{ proto: Git2\Tree::valid()
*/
PHP_METHOD(git2_tree, valid)
{
	php_git2_tree *m_tree;
	int entry_count = 0;
	
	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	entry_count = git_tree_entrycount(m_tree->tree);
	if (m_tree->offset < entry_count && m_tree->offset >= 0) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


static zend_function_entry php_git2_tree_methods[] = {
	/* Iterator Implementation */
	PHP_ME(git2_tree, current,     NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, key,         NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, next,        NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, rewind,      NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, valid,       NULL,                            ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_tree_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Tree", php_git2_tree_methods);
	git2_tree_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_tree_class_entry->create_object = php_git2_tree_new;
	zend_class_implements(git2_tree_class_entry TSRMLS_CC, 1, spl_ce_Iterator);
}