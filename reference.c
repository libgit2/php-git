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

PHPAPI zend_class_entry *git2_reference_class_entry;

static void php_git2_reference_free_storage(php_git2_reference *object TSRMLS_DC)
{
	if (object->reference != NULL) {
		object->reference = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_reference_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_reference);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_reference_lookup, 0,0,2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_reference_each, 0,0,2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, filter)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\Reference::lookup(Git2\Repository $repo, string $path)
*/
PHP_METHOD(git2_reference, lookup)
{
	char *path;
	char oid_out[GIT_OID_HEXSZ] = {0};
	int error, path_len = 0;
	git_reference *ref;
	zval *repository, *object;
	git_oid *oid;
	php_git2_repository *m_repository;
	php_git2_reference *m_reference;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"Os", &repository, git2_repository_class_entry, &path, &path_len) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, repository);
	
	error = git_reference_lookup(&ref, m_repository->repository, path);
	if (error == GIT_ENOTFOUND) {
		RETURN_FALSE;
	}
	
	MAKE_STD_ZVAL(object);
	object_init_ex(object,git2_reference_class_entry);
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, object);
	m_reference->reference = ref;

	RETURN_ZVAL(object,0,1);
}
/* }}} */

/*
{{{ proto: Git2\Reference::getTarget()
*/
PHP_METHOD(git2_reference, getTarget)
{
	git_reference *ref;
	php_git2_reference *m_reference;
	
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, getThis());
	
	if (git_reference_type(m_reference->reference) == GIT_REF_OID) {
		const git_oid *oid;
		char oid_out[GIT_OID_HEXSZ] = {0};
		
		oid = git_reference_oid(m_reference->reference);
		git_oid_fmt(oid_out, oid);
		RETVAL_STRINGL(oid_out,GIT_OID_HEXSZ,1);
	} else {
		RETVAL_STRING(git_reference_target(m_reference->reference),1);
	}
}
/* }}} */

/*
{{{ proto: Git2\Reference::getName()
*/
PHP_METHOD(git2_reference, getName)
{
	git_reference *ref;
	php_git2_reference *m_reference;
	
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, getThis());
	
	RETVAL_STRING(git_reference_name(m_reference->reference),1);
}
/* }}} */

/*
{{{ proto: Git2\Reference::getBaseName()
*/
PHP_METHOD(git2_reference, getBaseName)
{
	git_reference *ref;
	zval *result;
	const char *name = NULL;
	const *basename = NULL;
	php_git2_reference *m_reference;
	size_t len;
	
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, getThis());
	
	name  = git_reference_name(m_reference->reference);
	php_basename(name, strlen(name), NULL, 0, &basename, &len TSRMLS_CC);
	RETVAL_STRINGL(basename, len, 0);
}
/* }}} */

/*
{{{ proto: Git2\Reference::resolve()
*/
PHP_METHOD(git2_reference, resolve)
{
	git_reference *resolved;
	php_git2_reference *m_reference;
	zval *object;
	int error;
	
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, getThis());
	error = git_reference_resolve(&resolved, m_reference->reference);
	
	MAKE_STD_ZVAL(object);
	object_init_ex(object, git2_reference_class_entry);
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, object);
	m_reference->reference = resolved;
	
	RETURN_ZVAL(object, 0, 1);
}
/* }}} */



typedef struct {
	unsigned int type;
	git_repository *repository;
	zval *result;
	zend_fcall_info *fci;
	zend_fcall_info_cache *fci_cache;
} php_git2_ref_foreach_cb_t;

static int php_git2_ref_foreach_cb(const char *name, void *opaque)
{
	TSRMLS_FETCH();
	zval *ref;
	git_reference *reference;
	php_git2_ref_foreach_cb_t *payload;
	php_git2_reference *m_reference;
	
	payload = (php_git2_ref_foreach_cb_t *)opaque;
	git_reference_lookup(&reference, payload->repository,name);
	
	MAKE_STD_ZVAL(ref);
	object_init_ex(ref, git2_reference_class_entry);
	m_reference = PHP_GIT2_GET_OBJECT(php_git2_reference, ref);
	m_reference->reference = reference;
	
	if (payload->type == 0) {
		add_next_index_zval(payload->result, ref);
	} else {
		zval *str, *result, *params = NULL;
		MAKE_STD_ZVAL(params);
		MAKE_STD_ZVAL(str);
		ZVAL_STRING(str, name, 1);
		array_init(params);
		add_next_index_zval(params, str);
		
		zend_fcall_info_args(payload->fci, params TSRMLS_CC);
		payload->fci->retval_ptr_ptr = &result;

		if (zend_call_function(payload->fci, payload->fci_cache TSRMLS_CC) == SUCCESS &&
			payload->fci->retval_ptr_ptr && *payload->fci->retval_ptr_ptr) {
		}

		if (Z_BVAL_PP(payload->fci->retval_ptr_ptr)) {
			add_next_index_zval(payload->result, ref);
		} else {
			zval_ptr_dtor(&ref);
		}
		
		zend_fcall_info_args_clear(payload->fci, 1);
		zval_ptr_dtor(&str);
		zval_ptr_dtor(&result);
		zval_ptr_dtor(&params);
		
	}

	return GIT_OK;
}

/*
{{{ proto: Git2\Reference::each(Git2\Repository $repository [,int filter[, Callable $callback]])
*/
PHP_METHOD(git2_reference, each)
{
	git_reference *ref;
	zval *repository,*callback = NULL;
	php_git2_repository *m_repository;
	char *filter;
	php_git2_ref_foreach_cb_t opaque;
	int error, filter_len = 0;
	unsigned int list_flags = GIT_REF_LISTALL;
	zend_fcall_info fci = {
		0,NULL,NULL,NULL,NULL,0,NULL,NULL
	};
	zend_fcall_info_cache fci_cache;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"O|sf", &repository, git2_repository_class_entry, &filter, &filter_len, &fci, &fci_cache) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, repository);
	opaque.type = 0;
	if (fci.size != 0) {
		opaque.type = 1;
		opaque.fci = &fci;
		opaque.fci_cache = &fci_cache;
	}
	opaque.repository = m_repository->repository;
	MAKE_STD_ZVAL(opaque.result);
	array_init(opaque.result);
	
	git_reference_foreach(m_repository->repository, list_flags, &php_git2_ref_foreach_cb, (void *)&opaque);
	
	RETVAL_ZVAL(opaque.result,0,1);
}
/* }}} */


static zend_function_entry php_git2_reference_methods[] = {
	PHP_ME(git2_reference, getTarget, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_reference, getName,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_reference, getBaseName,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(git2_reference, resolve,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_reference, each,      arginfo_git2_reference_each, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
#ifdef lookup
#undef lookup
#endif
	PHP_ME(git2_reference, lookup, arginfo_git2_reference_lookup, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
#ifndef lookup
#define lookup php_lookup
#endif
	{NULL,NULL,NULL}
};

void php_git2_reference_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Reference", php_git2_reference_methods);
	git2_reference_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_reference_class_entry->create_object = php_git2_reference_new;
}