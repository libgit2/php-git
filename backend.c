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

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_backend);
	retval.handlers = &git2_backend_object_handlers;
	return retval;
}

static zend_function_entry php_git2_backend_methods[] = {
	//int (* read)(void **, size_t *, git_otype *,struct git_odb_backend *,const git_oid *);
	//PHP_ME(git2_backend, read, arginfo_git2_backend_read, ZEND_ACC_PUBLIC) 
	//int (* read_prefix)(git_oid *,void **, size_t *, git_otype *,struct git_odb_backend *,const git_oid *,unsigned int);
	//PHP_ME(git2_backend, readPrefix, arginfo_git2_backend_read_prefix, ZEND_ACC_PUBLIC)
	//int (* read_header)(size_t *, git_otype *,struct git_odb_backend *,const git_oid *);
	//PHP_ME(git2_backend, readHeader, arginfo_git2_backend_read_header, ZEND_ACC_PUBLIC)
	//int (* write)(git_oid *,struct git_odb_backend *,const void *,size_t,git_otype);
	//PHP_ME(git2_backend, write, arginfo_git2_backend_write, ZEND_ACC_PUBLIC)
	//int (* exists)(struct git_odb_backend *,const git_oid *);
	//PHP_ME(git2_backend, exists, arginfo_git2_backend_exists, ZEND_ACC_PUBLIC)
	//void (* free)(struct git_odb_backend *);
	//PHP_ME(git2_backend, free, arginfo_git2_backend_free, ZEND_ACC_PUBLIC)
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