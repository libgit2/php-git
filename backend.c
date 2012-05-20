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
#include <Zend/zend_interfaces.h>

PHPAPI zend_class_entry *git2_backend_class_entry;
static zend_object_handlers git2_backend_object_handlers;

static int php_git2_backend_exists(git_odb_backend *_backend, const git_oid *oid)
{
	TSRMLS_FETCH();
	zval *retval, *param;
	php_git2_backend_internal *m_backend;
	const char out[GIT_OID_HEXSZ+1] = {0};
	int result = -1;
	
	MAKE_STD_ZVAL(param);
	git_oid_fmt(out, oid);
	ZVAL_STRING(param, out, 1);
	m_backend = (php_git2_backend_internal*)_backend;
	
	zend_call_method_with_1_params(&m_backend->self, Z_OBJCE_P(m_backend->self), NULL, "exists", &retval, param);
	
	if (Z_BVAL_P(retval)) {
		result = GIT_OK;
	}
	
	zval_ptr_dtor(&param);
	zval_ptr_dtor(&retval);
	
	return (result == GIT_OK);
}

static int php_git2_backend_write(git_oid *id, git_odb_backend *_backend, const void *buffer, size_t size, git_otype type)
{
	zval *z_id, *z_buffer, *z_size, *z_type, *retval, **value;
	int error = GIT_ERROR;
	char t_id[GIT_OID_HEXSZ] = {0};
	TSRMLS_FETCH();
	php_git2_backend_internal *backend;
	
	MAKE_STD_ZVAL(z_id);
	MAKE_STD_ZVAL(z_buffer);
	MAKE_STD_ZVAL(z_size);
	MAKE_STD_ZVAL(z_type);
	backend = (php_git2_backend_internal *)_backend;
	
	git_oid_fmt(t_id, id);
	ZVAL_STRINGL(z_id, t_id, GIT_OID_HEXSZ,1);
	ZVAL_STRINGL(z_buffer, buffer, size, 1);
	ZVAL_LONG(z_size, size);
	ZVAL_LONG(z_type, type);
	
	php_git2_call_user_function_v(&retval, backend->self, "write", sizeof("write")-1,4,z_id,z_buffer,z_size,z_type);
	
	zval_ptr_dtor(&z_id);
	zval_ptr_dtor(&z_buffer);
	zval_ptr_dtor(&z_size);
	zval_ptr_dtor(&z_type);
	
	if (Z_TYPE_P(retval) == IS_BOOL && Z_BVAL_P(retval)) {
		error = GIT_OK;
	}
	zval_ptr_dtor(&retval);

	return error;
}

static int php_git2_backend_read(void **buffer,size_t *size, git_otype *type, git_odb_backend *_backend, const git_oid *id)
{
	TSRMLS_FETCH();
	zval *retval, *z_oid, *z_type = NULL;
	php_git2_backend_internal *m_backend;
	const char out[GIT_OID_HEXSZ+1] = {0};
	int result = GIT_ERROR;

	MAKE_STD_ZVAL(z_oid);
	MAKE_STD_ZVAL(z_type);
	git_oid_fmt(out, id);

	ZVAL_STRING(z_oid, out, 1);
	ZVAL_LONG(z_type, type);
	m_backend = (php_git2_backend_internal*)_backend;
	
	zend_call_method_with_2_params(&m_backend->self, Z_OBJCE_P(m_backend->self), NULL, "read", &retval, z_oid, z_type);
	if (Z_TYPE_P(retval) == IS_ARRAY) {
		HashTable *hash;
		zval **value_pp, *data, *z_size;

		hash = Z_ARRVAL_P(retval);

		if (zend_hash_find(hash,"data",sizeof("data"),(void **)&value_pp) != FAILURE) {
			data = *value_pp;
		}

		if (zend_hash_find(hash,"size",sizeof("size"),(void **)&value_pp) != FAILURE) {
			size = *value_pp;
		}
		
		*buffer = estrndup(Z_STRVAL_P(data),Z_STRLEN_P(data));
		*size = Z_LVAL_P(z_size);
		
	}
	zval_ptr_dtor(&z_oid);
	zval_ptr_dtor(&z_type);
	zval_ptr_dtor(&retval);
	
	return result;
}


static int php_git2_backend_read_header(size_t *size, git_otype *type, git_odb_backend *_backend, const git_oid *id)
{
	TSRMLS_FETCH();
	zval *retval, *z_oid, *z_type;
	php_git2_backend_internal *m_backend;
	const char out[GIT_OID_HEXSZ] = {0};
	int result = GIT_ERROR;
	
	MAKE_STD_ZVAL(z_oid);
	MAKE_STD_ZVAL(z_type);
	git_oid_fmt(out, id);
	ZVAL_STRING(z_oid, out, 1);
	m_backend = (php_git2_backend_internal*)_backend;
	
	zend_call_method_with_2_params(&m_backend->self, Z_OBJCE_P(m_backend->self), NULL, "readHeader", &retval, z_oid, z_type);
	if (Z_TYPE_P(retval) == IS_ARRAY) {
		HashTable *hash;
		zval **value_pp, *data, *z_size;

		hash = Z_ARRVAL_P(retval);

		if (zend_hash_find(hash,"data",sizeof("data"),(void **)&value_pp) != FAILURE) {
			data = *value_pp;
		}

		if (zend_hash_find(hash,"size",sizeof("size"),(void **)&value_pp) != FAILURE) {
			z_size = *value_pp;
		}
		
		*size = Z_LVAL_P(z_size);
		
	}
	zval_ptr_dtor(&z_oid);
	zval_ptr_dtor(&z_type);
	zval_ptr_dtor(&retval);
	
	return result;
}

static int php_git2_backend_read_prefix(git_oid *id,void ** buffer, size_t * size, git_otype * type,struct git_odb_backend * _backend,const git_oid * oid,unsigned int length)
{
	TSRMLS_FETCH();
	zval *retval, *z_oid, *z_type;
	php_git2_backend_internal *m_backend;
	const char out[GIT_OID_HEXSZ+1] = {0};
	int result = GIT_ERROR;
	
	MAKE_STD_ZVAL(z_oid);
	MAKE_STD_ZVAL(z_type);
	git_oid_fmt(out, id);
	ZVAL_STRING(z_oid, out, 1);
	m_backend = (php_git2_backend_internal*)_backend;
	
	zend_call_method_with_2_params(&m_backend->self, Z_OBJCE_P(m_backend->self), NULL, "readPrefix", &retval, z_oid, z_type);
	if (Z_TYPE_P(retval) == IS_ARRAY) {
		HashTable *hash;
		zval **value_pp, *data, *z_size;

		hash = Z_ARRVAL_P(retval);

		if (zend_hash_find(hash,"data",sizeof("data"),(void **)&value_pp) != FAILURE) {
			data = *value_pp;
		}

		if (zend_hash_find(hash,"size",sizeof("size"),(void **)&value_pp) != FAILURE) {
			size = *value_pp;
		}

		if (zend_hash_find(hash,"oid",sizeof("oid"),(void **)&value_pp) != FAILURE) {
			z_oid = *value_pp;
		}
		
		*buffer = estrndup(Z_STRVAL_P(data),Z_STRLEN_P(data));
		*size = Z_LVAL_P(z_size);
		git_oid_fromstr(id, Z_STRVAL_P(z_oid));
	}
	zval_ptr_dtor(&z_oid);
	zval_ptr_dtor(&z_type);
	zval_ptr_dtor(&retval);
	
	return result;
}

static void php_git2_backend_free(struct git_odb_backend *_backend)
{
	TSRMLS_FETCH();
	zval *retval;
	php_git2_backend_internal *m_backend;
	m_backend = (php_git2_backend_internal*)_backend;
	
	zend_call_method_with_0_params(&m_backend->self, Z_OBJCE_P(m_backend->self), NULL, "free", &retval);
	zval_ptr_dtor(&retval);
	
	zval_ptr_dtor(&m_backend->self);
}

static void php_git2_backend_free_storage(php_git2_backend *object TSRMLS_DC)
{
	if (object->backend != NULL) {
		object->backend = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_backend_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git2_backend_internal *internal;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_backend);

	/* php_git2_backend_internal free'd by odb_backend. do not use ecalloc here. */
	internal = calloc(1,sizeof(php_git2_backend_internal));
	internal->parent.read        = &php_git2_backend_read;
	internal->parent.read_prefix = &php_git2_backend_read_prefix;
	internal->parent.read_header = &php_git2_backend_read_header;
	internal->parent.write       = &php_git2_backend_write;
	internal->parent.exists      = &php_git2_backend_exists;
	internal->parent.free        = &php_git2_backend_free;

	object->backend = (struct git_odb_backend*)internal;
	
	retval.handlers = &git2_backend_object_handlers;

	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_read, 0,0,2)
	ZEND_ARG_INFO(0, oid)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_read_prefix, 0,0,2)
	ZEND_ARG_INFO(0, oid)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_read_header, 0,0,2)
	ZEND_ARG_INFO(0, oid)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()
	
ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_write, 0,0,4)
	ZEND_ARG_INFO(0, oid)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, size)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_exists, 0,0,1)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()


/*
{{{ proto: Git2\Backend::__construct()
*/
PHP_METHOD(git2_backend, __construct)
{
	php_git2_backend *m_backend;
	php_git2_backend_internal * m_internal;
	m_backend = PHP_GIT2_GET_OBJECT(php_git2_backend, getThis());
	
	m_internal = (php_git2_backend_internal*)m_backend->backend;
	
	/* i'd like to move below line to php_git2_backend_new but i don't have a good idea */
	m_internal->self = getThis();
	Z_ADDREF_P(m_internal->self);
}
/* }}} */

static zend_function_entry php_git2_backend_methods[] = {
	PHP_ME(git2_backend, __construct, NULL, ZEND_ACC_PUBLIC)
	/* int (* read)(void **, size_t *, git_otype *,struct git_odb_backend *,const git_oid *); */
	PHP_ABSTRACT_ME(git2_backend, read, arginfo_git2_backend_read) 
	/* int (* read_prefix)(git_oid *,void **, size_t *, git_otype *,struct git_odb_backend *,const git_oid *,unsigned int); */
	PHP_ABSTRACT_ME(git2_backend, readPrefix, arginfo_git2_backend_read_prefix)
	/* int (* read_header)(size_t *, git_otype *,struct git_odb_backend *,const git_oid *); */
	PHP_ABSTRACT_ME(git2_backend, readHeader, arginfo_git2_backend_read_header)
	/* int (* write)(git_oid *,struct git_odb_backend *,const void *,size_t,git_otype); */
	PHP_ABSTRACT_ME(git2_backend, write, arginfo_git2_backend_write)
	/* int (* exists)(struct git_odb_backend *,const git_oid *); */
	PHP_ABSTRACT_ME(git2_backend, exists, arginfo_git2_backend_exists)
	/* void (* free)(struct git_odb_backend *); */
	PHP_ABSTRACT_ME(git2_backend, free, NULL)
	{NULL,NULL,NULL}
};

void php_git2_backend_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Backend", php_git2_backend_methods);
	git2_backend_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_backend_class_entry->create_object = php_git2_backend_new;

	memcpy(&git2_backend_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	git2_backend_object_handlers.clone_obj = NULL;
}