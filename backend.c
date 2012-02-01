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

PHPAPI zend_class_entry *git2_backend_class_entry;
static zend_object_handlers git2_backend_object_handlers;

static int php_git2_backend_exists(git_odb_backend *_backend, const git_oid *oid)
{
	TSRMLS_FETCH();
	zval *retval, *param;
	php_git2_backend_internal *backend;
	int result = GIT_ERROR;
	
	MAKE_STD_ZVAL(param);
	MAKE_STD_ZVAL(retval);
	backend = (php_git2_backend_internal *)_backend;

	zend_call_method_with_1_params(&backend->self, git2_backend_class_entry, NULL, "exists", &retval, param);
	
	if (Z_BVAL_P(retval)) {
		result = GIT_SUCCESS;
	}
	
	zval_ptr_dotr(&param);
	zval_ptr_dotr(&retval);
	
	return result;
}

static int php_git2_backend_write(git_oid *id, git_odb_backend *_backend, const void *buffer, size_t size, git_otype type)
{
	TSRMLS_FETCH();
	php_git2_backend_internal *backend = (php_git2_backend_internal *)_backend;

	return GIT_SUCCESS;
}

static int php_git2_backend_read(void **buffer,size_t size, git_otype *type, git_odb_backend *_backend, const git_oid *id)
{
	TSRMLS_FETCH();
	php_git2_backend_internal *backend;
	return GIT_SUCCESS;
}

static int php_git2_backend_read_header(size_t size, git_otype *type, git_odb_backend *_backend, const git_oid *id)
{
	TSRMLS_FETCH();
	php_git2_backend_internal *backend = (php_git2_backend_internal *)_backend;

	return GIT_SUCCESS;
}

static int php_git2_backend_read_prefix(git_oid *id,void ** buffer, size_t * size, git_otype * type,struct git_odb_backend * _backend,const git_oid * oid,unsigned int length)
{
	TSRMLS_FETCH();
	php_git2_backend_internal *backend = (php_git2_backend_internal *)_backend;

	return GIT_SUCCESS;
}

static void php_git2_backend_free(git_odb_backend *_backend)
{
	TSRMLS_FETCH();
	php_git2_backend_internal *backend = (php_git2_backend_internal *)_backend;
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
	php_git2_backend *m_backend;
	php_git2_backend_internal *internal;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_backend);

	internal = ecalloc(1,sizeof(php_git2_backend_internal));
	internal->parent.read        = &php_git2_backend_read;
	internal->parent.read_prefix = &php_git2_backend_read_prefix;
	internal->parent.read_header = &php_git2_backend_read_header;
	internal->parent.write       = &php_git2_backend_write;
	internal->parent.exists      = &php_git2_backend_exists;
	internal->parent.free        = &php_git2_backend_free;
	
	m_backend->backend = internal;
	
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
	
ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_write, 0,0,2)
	ZEND_ARG_INFO(0, oid)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, size)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_backend_exists, 0,0,1)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

static zend_function_entry php_git2_backend_methods[] = {
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