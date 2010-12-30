/*
 * The MIT License
 *
 * Copyright (c) 2010 Shuhei Tanuma
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

#include "php_git.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_string_to_type, 0, 0, 1)
	ZEND_ARG_INFO(0, string_type)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_string_to_type)
{
	const char *string_type = NULL;
	int string_len = 0;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &string_type, &string_len) == FAILURE){
		return;
	}

	RETVAL_LONG(git_object_string2type(string_type))
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_type_to_string, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_type_to_string)
{
	git_otype t;
	int type;
	const char *str;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &type) == FAILURE){
		return;
	}
	t = (git_otype)type;
	str = git_object_type2string(t);

	RETVAL_STRING(str,1);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_hex_to_raw, 0, 0, 1)
	ZEND_ARG_INFO(0, hex)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_hex_to_raw)
{
	git_oid oid;

	const char *hex = NULL;
	int hex_len = 0;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &hex, &hex_len) == FAILURE){
		return;
	}
	
	git_oid_mkstr(&oid, hex);
	RETVAL_STRINGL((&oid)->id,GIT_OID_RAWSZ,1);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_raw_to_hex, 0, 0, 1)
  ZEND_ARG_INFO(0, raw)
ZEND_END_ARG_INFO()

PHP_FUNCTION(git_raw_to_hex)
{
	git_oid oid;
	const char *raw = NULL;
	char out[GIT_OID_HEXSZ];
	int raw_len = 0;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"s",
		&raw, &raw_len) == FAILURE){
		return;
	}
	
	git_oid_mkraw(&oid, raw);
	git_oid_fmt(out, &oid);

	RETVAL_STRINGL(out,GIT_OID_HEXSZ,1);
}


PHP_FUNCTION(git_hello_world)
{
	php_printf("Hello World\n");
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_construct, 0, 0, 1)
  ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

PHP_METHOD(git_index, __construct)
{
	zval *object = getThis();
	const char *repository_path = NULL;
	int arg_len = 0;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							"s", &repository_path, &arg_len) == FAILURE){
		return;
	}
	PHPWRITE(repository_path,arg_len);

    git_index_entry *entry;
    git_index *index;
    git_index_open_bare(&index,repository_path);
    char oid[40];

    git_index_read(index);
    git_index_entrycount(index);

    int offset = git_index_find(index,"README.md");
    php_printf("offset:%d\n",offset);
    entry = git_index_get(index,offset);
    
    git_oid_fmt(oid,&entry->oid);
    php_printf("oid: %s\n",oid);
    php_printf("path: %s\n",entry->path);
    php_printf("ctime: %s",ctime(&entry->ctime.seconds));
    php_printf("mtime: %s",ctime(&entry->mtime.seconds));

	
	php_printf("hello");
}

/**
 * Classのエントリーポイント
 */
PHPAPI zend_class_entry *git_class_entry;

PHPAPI function_entry php_git_methods[] = {
	{NULL, NULL, NULL}
};

/*
まだはやいお
static zend_class_entry *git_index_class_entry;
static zend_object_handlers php_git_object_handlers;

static function_entry php_git_index_methods[] = {
	PHP_ME(git_index, __construct, arginfo_git_index_construct, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
*/

static function_entry php_git_functions[] = {
	PHP_FE(git_hello_world,NULL)
	PHP_FE(git_hex_to_raw, arginfo_git_index_construct)
	PHP_FE(git_raw_to_hex, arginfo_git_raw_to_hex)
	PHP_FE(git_type_to_string, arginfo_git_type_to_string)
	PHP_FE(git_string_to_type, arginfo_git_string_to_type)
	{NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(git) {
	zend_class_entry git_ce;
	INIT_CLASS_ENTRY(git_ce, "Git", php_git_methods);
	git_class_entry = zend_register_internal_class(&git_ce TSRMLS_CC);

/*
まだはやいお
  zend_class_entry git_index_ce;
  INIT_CLASS_ENTRY(git_index_ce,"GitIndex",php_git_index_methods);
  git_index_class_entry = zend_register_internal_class(&git_index_ce TSRMLS_CC);
*/
	REGISTER_GIT_CONST_LONG("SORT_NONE", 0)
	REGISTER_GIT_CONST_LONG("SORT_TOPO", 1)
	REGISTER_GIT_CONST_LONG("SORT_DATE", 2)
	REGISTER_GIT_CONST_LONG("SORT_REVERSE", 4)

	REGISTER_GIT_CONST_LONG("OBJ_ANY", GIT_OBJ_ANY)
	REGISTER_GIT_CONST_LONG("OBJ_BAD", GIT_OBJ_BAD)
	REGISTER_GIT_CONST_LONG("OBJ_COMMIT", GIT_OBJ_COMMIT)
	REGISTER_GIT_CONST_LONG("OBJ_TREE", GIT_OBJ_TREE)
	REGISTER_GIT_CONST_LONG("OBJ_BLOB", GIT_OBJ_BLOB)
	REGISTER_GIT_CONST_LONG("OBJ_TAG", GIT_OBJ_TAG)

	return SUCCESS;
}


PHP_MINFO_FUNCTION(git)
{
	php_printf("PHP Git Extension\n");
	php_info_print_table_start();
	php_info_print_table_row(2,"Version", PHP_GIT_EXTVER " (development)");
	php_info_print_table_row(2, "Authors", "Shuhei Tanuma 'stanuma@zynga.co.jp' (lead)\n");
	php_info_print_table_end();
}

zend_module_entry git_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_GIT_EXTNAME,
	php_git_functions,	/* Functions */
	PHP_MINIT(git),	/* MINIT */
	NULL, 	/* MSHUTDOWN */
	NULL, 	/* RINIT */
	NULL,	/* RSHUTDOWN */
	PHP_MINFO(git),	/* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GIT_EXTVER,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GIT
ZEND_GET_MODULE(git)
#endif
