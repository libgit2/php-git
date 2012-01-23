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

PHPAPI zend_class_entry *git2_index_class_entry;

static void php_git2_index_free_storage(php_git2_index *object TSRMLS_DC)
{
	if (object->index != NULL) {
		object->index = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_index_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_index);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_index___construct, 0,0,1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\Index::__construct(string $path)
*/
PHP_METHOD(git2_index, __construct)
{
	char *path;
	git_index *index;
	int error, path_len = 0;
	php_git2_index *m_index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}
	
	error = git_index_open(&index, path);
	m_index = PHP_GIT2_GET_OBJECT(php_git2_index, getThis());
	m_index->index = index;
}
/* }}} */



/* Iterator Implementation */

/*
{{{ proto: Git2\Tree::current()
*/
PHP_METHOD(git2_index, current)
{
	php_git2_index *m_index;
	const git_index_entry *entry;
	zval *z_entry;

	m_index     = PHP_GIT2_GET_OBJECT(php_git2_index, getThis());
	entry = git_index_get(m_index->index, m_index->offset);
	if (entry == NULL) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
			"specified offset does not exist. %d");
		RETURN_FALSE;
	}
	fprintf(stderr,"path: %s\n",entry->path);
	//create_tree_entry_from_entry(&z_entry, entry ,m_index->repository);
	//RETURN_ZVAL(z_entry, 0, 1);
}

/*
{{{ proto: Git2\Tree::key()
*/
PHP_METHOD(git2_index, key)
{
	php_git2_index *m_index;

	m_index     = PHP_GIT2_GET_OBJECT(php_git2_index, getThis());
	RETURN_LONG(m_index->offset);
}

/*
{{{ proto: Git2\Tree::valid()
*/
PHP_METHOD(git2_index, next)
{
	php_git2_index *m_index;

	m_index     = PHP_GIT2_GET_OBJECT(php_git2_index, getThis());
	m_index->offset++;
}

/*
{{{ proto: Git2\Tree::rewind()
*/
PHP_METHOD(git2_index, rewind)
{
	php_git2_index *m_index;

	m_index     = PHP_GIT2_GET_OBJECT(php_git2_index, getThis());
	m_index->offset = 0;
}

/*
{{{ proto: Git2\Index::valid()
*/
PHP_METHOD(git2_index, valid)
{
	php_git2_index *m_index;
	int entry_count = 0;
	
	m_index     = PHP_GIT2_GET_OBJECT(php_git2_index, getThis());
	entry_count = git_index_entrycount(m_index->index);
	if (m_index->offset < entry_count && m_index->offset >= 0) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


static zend_function_entry php_git2_index_methods[] = {
	PHP_ME(git2_index, __construct, arginfo_git2_index___construct, ZEND_ACC_PUBLIC)
	/* Iterator Implementation */
	PHP_ME(git2_index, current,     NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(git2_index, key,         NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(git2_index, next,        NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(git2_index, rewind,      NULL,                           ZEND_ACC_PUBLIC)
	PHP_ME(git2_index, valid,       NULL,                           ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_index_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Index", php_git2_index_methods);
	git2_index_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_index_class_entry->create_object = php_git2_index_new;
	zend_class_implements(git2_index_class_entry TSRMLS_CC, 1, spl_ce_Iterator);
}