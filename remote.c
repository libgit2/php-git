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

PHPAPI zend_class_entry *git2_remote_class_entry;

static void php_git2_remote_free_storage(php_git2_remote *object TSRMLS_DC)
{
	if (object->remote != NULL) {
		free(object->remote);
		object->remote = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_remote_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_remote);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_remote___construct, 0,0,2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_remote_connect, 0,0,1)
	ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\Remote::__construct(Git2\Repository $repository, string $url)
*/
PHP_METHOD(git2_remote, __construct)
{
	char *path;
	git_config *config;
	int error, path_len = 0;
	zval *repository;
	php_git2_repository *m_repository;
	php_git2_remote *m_remote;
	git_remote *remote;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"Os", &repository,git2_repository_class_entry, &path, &path_len) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, repository);
	m_remote = PHP_GIT2_GET_OBJECT(php_git2_remote, getThis());
	if (git_remote_valid_url(path)) {
		error = git_remote_new(
			&remote,
			m_repository->repository,
			path,
			NULL
		);
	} else {
		error = git_remote_load(&remote,m_repository->repository, path);
	}
	m_remote->remote = remote;
}
/* }}} */

/*
{{{ proto: Git2\Remote::connect(int type)
*/
PHP_METHOD(git2_remote, connect)
{
	php_git2_remote *m_remote;
	int error = 0;
	long direction = 0;
	
	m_remote = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &direction) == FAILURE) {
		return;
	}
	
	if (direction == 0) {
		direction = GIT_DIR_FETCH;
	}
	
	error = git_remote_connect(m_remote->remote, direction);
}
/* }}} */

static zend_function_entry php_git2_remote_methods[] = {
	PHP_ME(git2_remote, __construct, arginfo_git2_remote___construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(git2_remote, connect, arginfo_git2_remote_connect, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_remote_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Remote", php_git2_remote_methods);
	git2_remote_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_remote_class_entry->create_object = php_git2_remote_new;
}