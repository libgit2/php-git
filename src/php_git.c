/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2011 Shuhei Tanuma
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
#include <spl/spl_array.h>
#include <zend_interfaces.h>
#include <string.h>
#include <time.h>

PHPAPI zend_class_entry *git_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_string_to_type, 0, 0, 1)
    ZEND_ARG_INFO(0, string_type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_type_to_string, 0, 0, 1)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_hex_to_raw, 0, 0, 1)
    ZEND_ARG_INFO(0, hex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_raw_to_hex, 0, 0, 1)
    ZEND_ARG_INFO(0, raw)
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

PHPAPI function_entry php_git_methods[] = {
    {NULL, NULL, NULL}
};

// Git Global Functions
PHPAPI function_entry php_git_functions[] = {
    PHP_FE(git_hex_to_raw, arginfo_git_hex_to_raw)
    PHP_FE(git_raw_to_hex, arginfo_git_raw_to_hex)
    PHP_FE(git_type_to_string, arginfo_git_type_to_string)
    PHP_FE(git_string_to_type, arginfo_git_string_to_type)
    {NULL, NULL, NULL}
};

void git_init(TSRMLS_D)
{
    zend_class_entry git_ce;
    INIT_NS_CLASS_ENTRY(git_ce, PHP_GIT_NS,"Git", php_git_methods);
    git_class_entry = zend_register_internal_class(&git_ce TSRMLS_CC);
}

PHP_MINIT_FUNCTION(git) {
    git_init(TSRMLS_C);
    git_init_object(TSRMLS_C);
    git_init_reference(TSRMLS_C);
    php_git_repository_init(TSRMLS_C);
    git_index_iterator_init(TSRMLS_C);
    git_index_entry_init(TSRMLS_C);
    git_index_init(TSRMLS_C);
    git_init_signature(TSRMLS_C);
    git_init_walker(TSRMLS_C);
    git_tree_iterator_init(TSRMLS_C);
    git_init_tree(TSRMLS_C);
    git_init_commit(TSRMLS_C);
    git_init_tree_entry(TSRMLS_C);
    git_init_tag(TSRMLS_C);
    git_init_blob(TSRMLS_C);
    git_init_odb(TSRMLS_C);
    //git_init_backend(TSRMLS_C);
    git_init_reference_manager(TSRMLS_C);

    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Revwalk"), "SORT_NONE",    0, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Revwalk"), "SORT_TOPO",    1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Revwalk"), "SORT_DATE",    2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Revwalk"), "SORT_REVERSE", 4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Object"), "Any",    GIT_OBJ_ANY,    CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Object"), "Bad",    GIT_OBJ_BAD,    CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Object"), "Commit", GIT_OBJ_COMMIT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Object"), "Tree",   GIT_OBJ_TREE,   CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Object"), "Blob",   GIT_OBJ_BLOB,   CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(ZEND_NS_NAME(PHP_GIT_NS,"Object"), "Tag",    GIT_OBJ_TAG,    CONST_CS | CONST_PERSISTENT);

    return SUCCESS;
}


PHP_MINFO_FUNCTION(git)
{
    php_printf("PHP Git Extension\n");
    php_info_print_table_start();
    php_info_print_table_row(2,"Version", PHP_GIT_EXTVER " (1st alpha development)");
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
