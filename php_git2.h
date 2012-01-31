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
#  include <date/php_date.h>
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
extern PHPAPI zend_class_entry *git2_signature_class_entry;
extern PHPAPI zend_class_entry *git2_walker_class_entry;
extern PHPAPI zend_class_entry *git2_reference_class_entry;
extern PHPAPI zend_class_entry *git2_index_class_entry;
extern PHPAPI zend_class_entry *git2_index_entry_class_entry;
extern PHPAPI zend_class_entry *git2_config_class_entry;
extern PHPAPI zend_class_entry *git2_remote_class_entry;
extern PHPAPI zend_class_entry *git2_tag_class_entry;
extern PHPAPI zend_class_entry *git2_odb_class_entry;
extern PHPAPI zend_class_entry *git2_raw_class_entry;
extern PHPAPI zend_class_entry *git2_backend_class_entry;

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
	unsigned int offset;
	git_repository *repository;
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

typedef struct{
	zend_object zo;
	git_reference *reference;
} php_git2_reference;

typedef struct{
	zend_object zo;
	git_revwalk *walker;
	git_oid *current;
	git_repository *repository;
} php_git2_walker;

typedef struct{
	zend_object zo;
	git_index *index;
	unsigned int offset;
} php_git2_index;

typedef struct{
	zend_object zo;
	git_index_entry *entry;
} php_git2_index_entry;

typedef struct{
	zend_object zo;
	git_config *config;
} php_git2_config;

typedef struct{
	zend_object zo;
	git_remote *remote;
} php_git2_remote;

typedef struct{
	zend_object zo;
	git_tag *tag;
} php_git2_tag;

typedef struct{
	zend_object zo;
	git_odb *odb;
} php_git2_odb;

typedef struct{
	zend_object zo;
	git_odb_object *object;
} php_git2_raw;

typedef struct{
	zend_object zo;
	git_odb_backend *backend;
} php_git2_backend;


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


extern zval* php_git_read_protected_property(zend_class_entry *scope, zval *object, char *name, int name_length TSRMLS_DC);
extern int php_git2_add_protected_property_string_ex(zval *object, char *name, int name_length, char *data, zend_bool duplicate TSRMLS_DC);
extern int php_git2_add_protected_property_zval_ex(zval *object, char *name, int name_length, zval *data, zend_bool duplicate TSRMLS_DC);
extern zval* php_git2_object_new(git_repository *repository, git_object *object TSRMLS_DC);
extern int php_git2_call_user_function_v(zval **retval, zval *obj, char *method, unsigned int method_len, unsigned int param_count, ...);

extern inline void php_git2_create_signature(zval *object, char *name, int name_len, char *email, int email_len, zval *date TSRMLS_DC);


static inline php_git2_create_signature_from_commit(zval **object, git_commit *commit, int type TSRMLS_DC)
{
	zval *ret;
	zval *z_signature, *date;
	char time_str[12] = {0};
	const git_signature *author;
	php_git2_signature *m_signature;

	if (type == 0) {
		author = git_commit_author(commit);
	} else {
		author = git_commit_committer(commit);
	}

	MAKE_STD_ZVAL(ret);
	MAKE_STD_ZVAL(date);

	object_init_ex(ret,git2_signature_class_entry);
	m_signature = PHP_GIT2_GET_OBJECT(php_git2_signature, ret);
	add_property_string_ex(ret,"name",sizeof("name"), author->name,1 TSRMLS_CC);
	add_property_string_ex(ret,"email",sizeof("email"),author->email,1 TSRMLS_CC);

	php_date_instantiate(php_date_get_date_ce(), date TSRMLS_CC);
	snprintf(time_str,12,"%c%ld",'@',author->when.time);
	php_date_initialize(zend_object_store_get_object(date TSRMLS_CC), time_str, strlen(time_str), NULL, NULL, 0 TSRMLS_CC);

	add_property_zval(ret,"time",date);
	zval_ptr_dtor(&date);
	*object = ret;
}

static inline void create_tree_entry_from_entry(zval **object, git_tree_entry *entry, git_repository *repository)
{
	TSRMLS_FETCH();
	char buf[GIT_OID_HEXSZ] = {0};
	const git_oid *oid;
	php_git2_tree_entry *m_entry;

	MAKE_STD_ZVAL(*object);
	object_init_ex(*object, git2_tree_entry_class_entry);
	m_entry = PHP_GIT2_GET_OBJECT(php_git2_tree_entry, *object);

	m_entry->entry = entry;
	oid = git_tree_entry_id(entry);
	git_oid_to_string(buf,GIT_OID_HEXSZ,oid);

	add_property_string(*object, "name", (char *)git_tree_entry_name(entry), 1);
	add_property_string(*object, "oid", buf, 1);
	add_property_long(*object, "attributes", git_tree_entry_attributes(entry));
}

static inline void php_git2_create_index_entry(zval **object, git_index_entry *entry TSRMLS_DC)
{
	zval *tmp = NULL;
	char oid_out[GIT_OID_HEXSZ] = {0};
	
	MAKE_STD_ZVAL(tmp);
	object_init_ex(tmp, git2_index_entry_class_entry);
	git_oid_fmt(oid_out, &entry->oid);

	add_property_string_ex(tmp, "path", sizeof("path"), entry->path, 1 TSRMLS_CC);
	add_property_stringl_ex(tmp, "oid", sizeof("oid"), oid_out,GIT_OID_HEXSZ, 1 TSRMLS_CC);
	add_property_long(tmp, "dev", entry->dev);
	add_property_long(tmp, "ino", entry->ino);
	add_property_long(tmp, "mode", entry->mode);
	add_property_long(tmp, "uid", entry->uid);
	add_property_long(tmp, "gid", entry->gid);
	add_property_long(tmp, "file_size", entry->file_size);
	add_property_long(tmp, "flags", entry->flags);
	add_property_long(tmp, "flags_extended", entry->flags_extended);
	add_property_long(tmp, "ctime", entry->ctime.seconds);
	add_property_long(tmp, "mtime", entry->mtime.seconds);
	
	*object = tmp;
}

#define PHP_GIT2_EXCEPTION_CHECK(errorcode) \
	if (errorcode < 0) { \
		zend_throw_exception_ex(NULL, 0 TSRMLS_CC,"%s\n(error code %d) at %s:%d", git_lasterror(), errorcode, __FILE__, __LINE__); \
		git_clearerror(); \
		return; \
	} \

static inline void php_git2_exception_check(int errorcode TSRMLS_DC)
{
	if (errorcode < 0) {
		zend_throw_exception_ex(NULL, 0 TSRMLS_CC,"%s\n(error code %d)", git_lasterror(), errorcode);
		fprintf(stderr,"moe");
		git_clearerror();
		return;
	}
}

#endif /* PHP_GIT2_H */