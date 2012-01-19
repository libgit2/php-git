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

#ifndef PHP_GIT2_H
#  define PHP_GIT2_H

#  define PHP_GIT2_EXTNAME "git2"
#  define PHP_GIT2_EXTVER "0.2.1"

#  ifdef HAVE_CONFIG_H
#    include "config.h"
#  endif

#  include "php.h"
#  include "ext/spl/spl_exceptions.h"
#  include <git2.h>
#  include <git2/odb_backend.h>

extern zend_module_entry git2_module_entry;

#  define phpext_git2_ptr &git_module_entry;
#  define PHP_GIT2_NS "Git2"

extern PHPAPI zend_class_entry *git2_repository_class_entry;
extern PHPAPI zend_class_entry *git2_commit_class_entry;
extern PHPAPI zend_class_entry *git2_blob_class_entry;
extern PHPAPI zend_class_entry *git2_tree_class_entry;
extern PHPAPI zend_class_entry *git2_tree_builder_class_entry;
extern PHPAPI zend_class_entry *git2_tree_entry_class_entry;
extern PHPAPI zend_class_entry *git2_tree_signature_entry;

typedef struct{
	zend_object zo;
	git_repository *repository;
} php_git2_repository;

typedef struct{
	zend_object zo;
	git_commit *commit;
} php_git2_commit;

typedef struct{
	zend_object zo;
	git_blob *blob;
} php_git2_blob;

typedef struct{
	zend_object zo;
	git_tree *tree;
} php_git2_tree;

typedef struct{
	zend_object zo;
	git_tree_entry *entry;
} php_git2_tree_entry;

typedef struct{
	zend_object zo;
	git_treebuilder *builder;
} php_git2_tree_builder;


typedef struct{
	zend_object zo;
	git_signature *signature;
} php_git2_signature;

#  define PHP_GIT2_GET_OBJECT(STRUCT_NAME, OBJECT) (STRUCT_NAME *) zend_object_store_get_object(OBJECT TSRMLS_CC);

#  if ZEND_MODULE_API_NO >= 20100525
#  define PHP_GIT2_STD_CREATE_OBJECT(STRUCT_NAME) \
	STRUCT_NAME *object;\
	\
	object = ecalloc(1, sizeof(*object));\
	zend_object_std_init(&object->zo, ce TSRMLS_CC);\
	object_properties_init(&object->zo, ce);
	\
	retval.handle = zend_objects_store_put(object,\
		(zend_objects_store_dtor_t)zend_objects_destroy_object,\
		(zend_objects_free_object_storage_t) STRUCT_NAME##_free_storage ,\
	NULL TSRMLS_CC);\
	retval.handlers = zend_get_std_object_handlers();
#  else
#  define PHP_GIT2_STD_CREATE_OBJECT(STRUCT_NAME) \
	STRUCT_NAME *object;\
	zval *tmp = NULL;\
	\
	object = ecalloc(1, sizeof(*object));\
	zend_object_std_init(&object->zo, ce TSRMLS_CC);\
	zend_hash_copy(object->zo.properties, &ce->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *)); \
	\
	retval.handle = zend_objects_store_put(object,\
		(zend_objects_store_dtor_t)zend_objects_destroy_object,\
		(zend_objects_free_object_storage_t) STRUCT_NAME##_free_storage ,\
	NULL TSRMLS_CC);\
	retval.handlers = zend_get_std_object_handlers();
#  endif

extern int php_git2_add_protected_property_string_ex(zval *object, char *name, int name_length, char *data, zend_bool duplicate TSRMLS_DC);
extern zval* php_git2_object_new(php_git2_repository *repository, git_object *object TSRMLS_DC);
extern int php_git2_call_user_function_v(zval **retval, zval *obj, char *method, unsigned int method_len, unsigned int param_count, ...);

#endif /* PHP_GIT2_H */