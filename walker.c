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

static const double resize_factor = 1.75;
static const unsigned int minimum_size = 8;

typedef struct{
	git_oid oid;
	unsigned int interested;
} php_git2_revwalk_element;

int php_git2_vector_init(php_git2_vector *v, size_t initial_size)
{
	assert(v);
	memset(v, 0x0, sizeof(php_git2_vector));

	if (initial_size == 0) {
		initial_size = minimum_size;
	}

	v->_alloc_size = initial_size;
	v->length = 0;

	v->contents = emalloc(v->_alloc_size * sizeof(void *));
}

static int php_git2_resize_vector(php_git2_vector *v)
{
	v->_alloc_size = ((unsigned int)(v->_alloc_size * resize_factor)) + 1;
	if (v->_alloc_size < minimum_size)
		v->_alloc_size = minimum_size;

	v->contents = erealloc(v->contents, v->_alloc_size * sizeof(void *));

	return 0;
}

int php_git2_vector_insert(php_git2_vector *v, void *element)
{
	assert(v);

	if (v->length >= v->_alloc_size && php_git2_resize_vector(v) < 0) {
		return -1;
	}

	v->contents[v->length++] = element;
	return 0;
}

void php_git2_vector_clear(php_git2_vector *v)
{
	assert(v);
	v->length = 0;
}

void php_git2_vector_free(php_git2_vector *v)
{
	assert(v);

	efree(v->contents);
	v->contents = NULL;

	v->length = 0;
	v->_alloc_size = 0;
}


static void php_git2_walker_free_storage(php_git2_walker *object TSRMLS_DC)
{
	int i = 0;
	if (object->walker != NULL) {
		git_revwalk_free(object->walker);
		object->walker = NULL;
	}
	if (object->current != NULL) {
		efree(object->current);
		object->current = NULL;
	}

	for (i = 0; i < object->vector.length; i++) {
		efree(object->vector.contents[i]);
	}
	php_git2_vector_free(&object->vector);

	/* the repository will be free'd by Git2\Repository */
	object->repository = NULL;
	
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_walker_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_walker);
	object->dirty = 0;

	object->current = emalloc(sizeof(git_oid));
	php_git2_vector_init(&object->vector, 8);

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
	
	if (error != GIT_OK) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "can't create a Git2\\Walker instance.");
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
	int sha_len = 0, error = 0;
	php_git2_revwalk_element *elm;

	/* @todo: also supports Git2\Commit object */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &sha, &sha_len) == FAILURE) {
		return;
	}
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	elm = emalloc(sizeof(php_git2_revwalk_element));
	elm->interested = 1;
	
	git_oid_fromstrn(&elm->oid, sha, sha_len);
	error = git_revwalk_push(m_walker->walker, &elm->oid);
	
	if (error != GIT_OK) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "Git2\\Walker::push failed.");
	}

	php_git2_vector_insert(&m_walker->vector, elm);
}
/* }}} */

/*
{{{ proto: Git2\Walker::hide(string $hex_sha_unintersting)
*/
PHP_METHOD(git2_walker, hide)
{
	php_git2_walker *m_walker;
	char *sha;
	int sha_len = 0, error = 0;
	git_oid oid;
	php_git2_revwalk_element *elm;

	/* @todo: also supports Git2\Commit object */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &sha, &sha_len) == FAILURE) {
		return;
	}
	
	m_walker     = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	elm = emalloc(sizeof(php_git2_revwalk_element));
	elm->interested = 0;

	git_oid_fromstrn(&elm->oid, sha, sha_len);
	error = git_revwalk_hide(m_walker->walker, &elm->oid);

	if (error != GIT_OK) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "Git2\\Walker::push failed.");
	}
	php_git2_vector_insert(&m_walker->vector, elm);
}
/* }}} */


/*
{{{ proto: Git2\Walker::reset()
*/
PHP_METHOD(git2_walker, reset)
{
	php_git2_walker *m_walker;
	int i = 0;

	m_walker = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_revwalk_reset(m_walker->walker);
	m_walker->dirty = 0;
	
	for (i = 0; i < m_walker->vector.length; i++) {
		php_git2_revwalk_element *elm = m_walker->vector.contents[i];
		efree(elm);
	}
	
	php_git2_vector_clear(&m_walker->vector);
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
	
	error  = git_object_lookup(&object, m_walker->repository, m_walker->current, GIT_OBJ_COMMIT);
	result = php_git2_object_new(m_walker->repository, object TSRMLS_CC);
	RETVAL_ZVAL(result, 0, 1);
}

/*
{{{ proto: Git2\Walker::key()
*/
PHP_METHOD(git2_walker, key)
{
	char out[GIT_OID_HEXSZ] = {0};
	php_git2_walker *m_walker;
	int error = 0;

	m_walker = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	git_oid_fmt(out, m_walker->current);

	RETURN_STRINGL(out, GIT_OID_HEXSZ, 1);
}

/*
{{{ proto: Git2\Walker::next()
*/
PHP_METHOD(git2_walker, next)
{
	php_git2_walker *m_walker;
	int error = 0;

	m_walker = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	error = git_revwalk_next(m_walker->current, m_walker->walker);
	m_walker->dirty = 1;

	if (error != GIT_OK) {
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
	int i = 0, error = 0;
	m_walker = PHP_GIT2_GET_OBJECT(php_git2_walker, getThis());
	
	if (m_walker->dirty) {
		git_revwalk_reset(m_walker->walker);
		
		for (i = 0; i < m_walker->vector.length; i++) {
			php_git2_revwalk_element *elm = m_walker->vector.contents[i];
			
			if (elm->interested) {
				error = git_revwalk_push(m_walker->walker, &elm->oid);
			} else {
				error = git_revwalk_hide(m_walker->walker, &elm->oid);
			}

			if (error != GIT_OK) {
				zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "Git2\\Walker::rewind failed. probably you pushed or hided invalied oid.");
			}
		}
		
		if (m_walker->current == NULL) {
			m_walker->current = emalloc(sizeof(git_oid));
		}

		assert(m_walker->current);
		error = git_revwalk_next(m_walker->current, m_walker->walker);
		m_walker->dirty = 1;
	} else {
		error = git_revwalk_next(m_walker->current, m_walker->walker);
		m_walker->dirty = 1;
		
		if (error != GIT_OK) {
			zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "Git2\\Walker::rewind failed. probably you pushed or hided invalied oid.");
		}
	}

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