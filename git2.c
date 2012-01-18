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
extern void php_git2_signature_init(TSRMLS_D);


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

zval* php_git2_object_new(php_git2_repository *repository, git_object *object TSRMLS_DC)
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
			
			object_init_ex(result, git2_tree_class_entry);
			m_obj = PHP_GIT2_GET_OBJECT(php_git2_tree, result);
			m_obj->tree = (git_tree*)object;
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
	php_git2_signature_init(TSRMLS_C);
	
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