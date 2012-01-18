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

PHPAPI zend_class_entry *git2_commit_class_entry;

static void php_git2_commit_free_storage(php_git2_commit *object TSRMLS_DC)
{
	if (object->commit != NULL) {
		git_commit_free(object->commit);
		object->commit = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_commit_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_commit);
	return retval;
}

/*
{{{ proto: Git2\Commit::getMessage()
*/
PHP_METHOD(git2_commit, getMessage)
{
	char *data;
	php_git2_commit *m_commit;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		RETURN_STRING(git_commit_message(m_commit->commit),1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getMessageEncoding()
*/
PHP_METHOD(git2_commit, getMessageEncoding)
{
	char *encoding;
	php_git2_commit *m_commit;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		encoding = git_commit_message_encoding(m_commit->commit);
		if (encoding != NULL) {
			RETURN_STRING(encoding,1);
		} else {
			RETURN_STRING("UTF-8",1);
		}
	} 
	RETURN_FALSE;
}
/* }}} */


/*
{{{ proto: Git2\Commit::parentCount()
*/
PHP_METHOD(git2_commit, parentCount)
{
	unsigned int parent_count = 0;
	php_git2_commit *m_commit;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		parent_count = git_commit_parentcount(m_commit->commit);
		RETURN_LONG(parent_count);
	}
	RETURN_FALSE;
}
/* }}} */

static zend_function_entry php_git2_commit_methods[] = {
	PHP_ME(git2_commit, getMessage,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getMessageEncoding, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, parentCount,        NULL, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_commit_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Commit", php_git2_commit_methods);
	git2_commit_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_commit_class_entry->create_object = php_git2_commit_new;
}