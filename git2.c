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

extern void php_git2_repository_init(TSRMLS_D);
extern void php_git2_commit_init(TSRMLS_D);
extern void php_git2_blob_init(TSRMLS_D);
extern void php_git2_tree_init(TSRMLS_D);
extern void php_git2_tree_builder_init(TSRMLS_D);
extern void php_git2_signature_init(TSRMLS_D);
extern void php_git2_walker_init(TSRMLS_D);
extern void php_git2_reference_init(TSRMLS_D);


int php_git2_call_user_function_v(zval **retval, zval *obj, char *method, unsigned int method_len, unsigned int param_count, ...)
{
	va_list ap;
	size_t i;
	int error = 0;
	zval **params, *method_name, *ret= NULL;
	TSRMLS_FETCH();
	
	if (param_count > 0) {
		params = emalloc(sizeof(zval**) * param_count);
		va_start(ap, param_count);
		for (i = 0; i < param_count; i ++) {
			params[i] = va_arg(ap, zval*);
		}
		va_end(ap);
	} else {
		params = NULL;
	}
	
	MAKE_STD_ZVAL(ret);
	MAKE_STD_ZVAL(method_name);
	
	ZVAL_NULL(ret);
	ZVAL_STRINGL(method_name, method, method_len, 1);

	error = call_user_function(NULL, &obj, method_name, ret, param_count, params TSRMLS_CC);
	
	if (param_count > 0) {
		for (i = 0; i < param_count; i++) {
			if (params[i] != NULL) {
				zval_ptr_dtor(&params[i]);
			}
		}
		efree(params);
		params = NULL;
	}
	*retval = ret;
	zval_ptr_dtor(&method_name);

	return error;
}

zval* php_git2_object_new(git_repository *repository, git_object *object TSRMLS_DC)
{
	zval *result = NULL;
	MAKE_STD_ZVAL(result);
	
	switch (git_object_type(object)) {
		case GIT_OBJ_COMMIT: {
			php_git2_commit *m_obj = NULL;
			
			object_init_ex(result, git2_commit_class_entry);
			m_obj = PHP_GIT2_GET_OBJECT(php_git2_commit, result);
			m_obj->commit = (git_commit*)object;
			break;
		}
		case GIT_OBJ_BLOB: {
			php_git2_blob *m_obj = NULL;
			
			object_init_ex(result, git2_blob_class_entry);
			m_obj = PHP_GIT2_GET_OBJECT(php_git2_blob, result);
			m_obj->blob = (git_blob*)object;
			break;
		}
		case GIT_OBJ_TREE: {
			php_git2_tree *m_obj = NULL;
			unsigned int *numbers = 0;
			int i = 0;
			zval *m_array;
			
			object_init_ex(result, git2_tree_class_entry);
			m_obj = PHP_GIT2_GET_OBJECT(php_git2_tree, result);
			m_obj->tree = (git_tree*)object;
			m_obj->repository = repository;
			numbers = git_tree_entrycount(m_obj->tree);
			MAKE_STD_ZVAL(m_array);
			array_init(m_array);
			
			for (i = 0;i < numbers; i++) {
				const char *entry_name = {0};
				const char entry_oid[GIT_OID_HEXSZ+1] = {0};
				const git_tree_entry *entry;
				const git_oid *oid = NULL;
				zval *m_entry = NULL;
				
				entry = git_tree_entry_byindex(m_obj->tree, i);
				entry_name = git_tree_entry_name(entry);
				oid = git_tree_entry_id(entry);
				git_oid_fmt(entry_oid, oid);
				
				MAKE_STD_ZVAL(m_entry);
				object_init_ex(m_entry, git2_tree_entry_class_entry);
				add_property_stringl_ex(m_entry, "name", sizeof("name"), entry_name, strlen(entry_name), 1 TSRMLS_CC);
				add_property_stringl_ex(m_entry, "oid", sizeof("oid"), entry_oid, strlen(entry_oid), 1 TSRMLS_CC);
				add_property_long_ex(m_entry, "attributes", sizeof("attributes"), git_tree_entry_attributes(entry) TSRMLS_CC);
				add_next_index_zval(m_array, m_entry);
			}
			
			add_property_zval_ex(result, "entries",sizeof("entries"),m_array TSRMLS_CC);
			zval_ptr_dtor(&m_array);
			
			break;
		}
		case GIT_OBJ_TAG: {
			break;
		}
		default:
			break;
	}
	
	return result;
}

int php_git2_add_protected_property_string_ex(zval *object, char *name, int name_length, char *data, zend_bool duplicate TSRMLS_DC)
{
	zval *tmp;
	char *key;
	int length;

	MAKE_STD_ZVAL(tmp);
	ZVAL_STRING(tmp,data,duplicate);
	zend_mangle_property_name(&key, &length, "*",1,name,name_length,0);
	zend_hash_update(Z_OBJPROP_P(object),key,length,&tmp,sizeof(zval *),NULL);
	efree(key);

	return SUCCESS;
}


PHP_MINIT_FUNCTION(git2)
{
	php_git2_repository_init(TSRMLS_C);
	php_git2_commit_init(TSRMLS_C);
	php_git2_blob_init(TSRMLS_C);
	php_git2_tree_init(TSRMLS_C);
	php_git2_tree_builder_init(TSRMLS_C);
	php_git2_tree_entry_init(TSRMLS_C);
	php_git2_signature_init(TSRMLS_C);
	php_git2_walker_init(TSRMLS_C);
	php_git2_reference_init(TSRMLS_C);
	php_git2_index_entry_init(TSRMLS_C);
	php_git2_index_init(TSRMLS_C);
	
	return SUCCESS;
}

PHP_MINFO_FUNCTION(git2)
{
	php_printf("PHP libgit2 Extension\n");
	php_info_print_table_start();
	php_info_print_table_row(2,"Version", PHP_GIT2_EXTVER "-dev");
	php_info_print_table_row(2,"libgit2 version", LIBGIT2_VERSION);
	php_info_print_table_end();
}

zend_module_entry git2_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_GIT2_EXTNAME,
	NULL,				/* Functions */
	PHP_MINIT(git2),	/* MINIT */
	NULL,				/* MSHUTDOWN */
	NULL,				/* RINIT */
	NULL,				/* RSHUTDOWN */
	PHP_MINFO(git2),	/* MFINFO */
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GIT2_EXTVER,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GIT2
ZEND_GET_MODULE(git2)
#endif