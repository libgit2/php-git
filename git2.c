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