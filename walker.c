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
	
PHPAPI zend_class_entry *git2_walker_class_entry;

static void php_git2_walker_free_storage(php_git2_walker *object TSRMLS_DC)
{
	if (object->walker != NULL) {
		git_revwalk_free(object->walker);
		object->walker = NULL;
	}
	if (object->current != NULL) {
		efree(object->current);
		object->current = NULL;
	}

	/* the repository will be free'd by Git2\Repository */
	object->repository = NULL;
	
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_walker_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_walker);

	object->current = emalloc(sizeof(git_oid));
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_walker___construct, 0,0,1)
	ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_walker_sorting, 0,0,1)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_walker_push, 0,0,1)
	ZEND_ARG_INFO(0, sha)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_walker_hide, 0,0,1)
	ZEND_ARG_INFO(0, sha)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\Walker::__construct(Git2\Repository $repo)
*/
PHP_METHOD(git2_walker, __construct)
{
	php_git2_repository *m_repository;
	php_git2_walker *m_walker;
	zval *repository;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"O", &repository, git2_repository_class_entry) == FAILURE) {
		return;
	}
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, repository);
	
	error = git_revwalk_new(&m_walker->walker, m_repository->repository);
	
	if (error != GIT_SUCCESS) {
		/* @todo error handling */
	}
	m_walker->repository = m_repository->repository;
}
/* }}} */

/*
{{{ proto: Git2\Walker::sorting(long $mode)
*/
PHP_METHOD(git2_walker, sorting)
{
	php_git2_walker *m_walker;
	long mode = GIT_SORT_NONE;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &mode) == FAILURE) {
		return;
	}
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_revwalk_sorting(m_walker->walker, (unsigned int)mode);
}
/* }}} */

/*
{{{ proto: Git2\Walker::push(string $hex_sha_intersting)
*/
PHP_METHOD(git2_walker, push)
{
	php_git2_walker *m_walker;
	char *sha;
	int sha_len = 0;
	int error = 0;
	git_oid oid;

	/* @todo: also supports Git2\Commit object */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &sha, &sha_len) == FAILURE) {
		return;
	}
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	
	git_oid_fromstrn(&oid, sha, sha_len);
	git_revwalk_reset(m_walker->walker);
	git_revwalk_push(m_walker->walker, &oid);
	memcpy(m_walker->current, &oid, sizeof(git_oid));
}
/* }}} */

/*
{{{ proto: Git2\Walker::hide(string $hex_sha_unintersting)
*/
PHP_METHOD(git2_walker, hide)
{
	php_git2_walker *m_walker;
	char *sha;
	int sha_len = 0;
	int error = 0;
	git_oid oid;

	/* @todo: also supports Git2\Commit object */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &sha, &sha_len) == FAILURE) {
		return;
	}
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_oid_fromstrn(&oid, sha, sha_len);
	git_revwalk_hide(m_walker->walker, &oid);
}
/* }}} */


/*
{{{ proto: Git2\Walker::reset()
*/
PHP_METHOD(git2_walker, reset)
{
	php_git2_walker *m_walker;

	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_revwalk_reset(m_walker->walker);
}
/* }}} */


/* Iterator Implementation */

/*
{{{ proto: Git2\Walker::current()
*/
PHP_METHOD(git2_walker, current)
{
	php_git2_walker *m_walker;
	zval *result;
	git_object *object;
	int error = 0;

	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	error = git_object_lookup(&object, m_walker->repository, m_walker->current, GIT_OBJ_COMMIT);
	result = php_git2_object_new(m_walker->repository, object TSRMLS_CC);
	RETVAL_ZVAL(result,0,1);
}

/*
{{{ proto: Git2\Walker::key()
*/
PHP_METHOD(git2_walker, key)
{
	char out[GIT_OID_HEXSZ] = {0};
	php_git2_walker *m_walker;

	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_oid_fmt(out, m_walker->current);
	RETURN_STRINGL(out,GIT_OID_HEXSZ,1);
}

/*
{{{ proto: Git2\Walker::valid()
*/
PHP_METHOD(git2_walker, next)
{
	php_git2_walker *m_walker;
	int error = 0;

	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	error = git_revwalk_next(m_walker->current, m_walker->walker);
	if (error != GIT_SUCCESS) {
		efree(m_walker->current);
		m_walker->current = NULL;
	}
}

/*
{{{ proto: Git2\Walker::rewind()
*/
PHP_METHOD(git2_walker, rewind)
{
	php_git2_walker *m_walker;

	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_revwalk_reset(m_walker->walker);
	if (m_walker->current == NULL) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
		"does not specify interested hash before calling Git2\\Walker::rewind.");
		RETURN_FALSE;
	}
	git_revwalk_push(m_walker->walker, m_walker->current);
	git_revwalk_next(m_walker->current, m_walker->walker);
}

/*
{{{ proto: Git2\Walker::valid()
*/
PHP_METHOD(git2_walker, valid)
{
	php_git2_walker *m_walker;
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	if (m_walker->current != NULL) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

static zend_function_entry php_git2_walker_methods[] = {
	PHP_ME(git2_walker, __construct, arginfo_git2_walker___construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(git2_walker, sorting,     arginfo_git2_walker_sorting,     ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, push,        arginfo_git2_walker_push,        ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, hide,        arginfo_git2_walker_hide,        ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, reset,       NULL,                            ZEND_ACC_PUBLIC)
	/* Iterator Implementation */
	PHP_ME(git2_walker, current,     NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, key,         NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, next,        NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, rewind,      NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_walker, valid,       NULL,                            ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_walker_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Walker", php_git2_walker_methods);
	git2_walker_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_walker_class_entry->create_object = php_git2_walker_new;
	zend_class_implements(git2_walker_class_entry TSRMLS_CC, 1, spl_ce_Iterator);
}