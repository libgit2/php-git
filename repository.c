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

PHPAPI zend_class_entry *git2_repository_class_entry;
void php_git2_repository_init(TSRMLS_D);

static void php_git2_repository_free_storage(php_git2_repository *object TSRMLS_DC)
{
	if (object->repository != NULL) {
		git_repository_free(object->repository);
		object->repository = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_repository_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_repository);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository___construct, 0,0,1)
	ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\Repsotiroy::__construct(string $path)
*/
PHP_METHOD(git2_repository, __construct)
{
	const char *repository_path = NULL;
	int repository_path_len, ret = 0;
	git_repository *repository;
	php_git2_repository *m_repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|s", &repository_path, &repository_path_len) == FAILURE) {
		return;
	}

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (repository_path_len > 0) {
		ret = git_repository_open(&repository, repository_path);
		
		if (ret != GIT_SUCCESS) {
			zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC, git_strerror(ret));
			RETURN_FALSE;
		}
		
		m_repository->repository = repository;
		php_git_add_protected_property_string_ex(getThis(),
			"path",sizeof("path"),
			git_repository_path(repository),
		1 TSRMLS_CC);
	} else {
		m_repository->repository = NULL;
	}
}
/* }}} */

/*
{{{ proto: Git2\Repsotiroy::isEmpty()
*/
PHP_METHOD(git2_repository, isEmpty)
{
	git_repository *repository;
	php_git2_repository *m_repository;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		if (git_repository_is_empty(m_repository->repository)) {
			RETURN_TRUE;
		} else {
			RETURN_FALSE;
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */

/*
{{{ proto: Git2\Repsotiroy::isBare()
*/
PHP_METHOD(git2_repository, isBare)
{
	git_repository *repository;
	php_git2_repository *m_repository;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		if (git_repository_is_bare(m_repository->repository) == 1) {
			RETURN_TRUE;
		} else {
			RETURN_FALSE;
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */


static zend_function_entry php_git2_repository_methods[] = {
	PHP_ME(git2_repository, __construct, arginfo_git2_repository___construct, ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, isEmpty,     NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, isBare,      NULL,                                ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_repository_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Repository", php_git2_repository_methods);
	git2_repository_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_repository_class_entry->create_object = php_git2_repository_new;
}