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

zval* php_git_read_protected_property(zend_class_entry *scope, zval *object, char *name, int name_length TSRMLS_DC)
{
    zval **data;
    char *key;
    long *length;
    zend_mangle_property_name(&key,&length,"*",1,name,name_length,0);
    if (zend_hash_find(Z_OBJPROP_P(object),key,length,(void **)&data) != SUCCESS) {
        data = NULL;
    }

    efree(key);
    return (zval *)*data;
}

int php_git_add_protected_property_string_ex(zval *object, char *name, int name_length, char *data, zend_bool duplicate TSRMLS_DC)
{
    zval *tmp;
    char *key;
    long *length;
    MAKE_STD_ZVAL(tmp);
    ZVAL_STRING(tmp,data,duplicate);
    zend_mangle_property_name(&key,&length,"*",1,name,name_length,0);
    zend_hash_update(Z_OBJPROP_P(object),key,length,&tmp,sizeof(zval *),NULL);
    efree(key);
    
    return SUCCESS;
}

int php_git_add_protected_property_zval_ex(zval *object, char *name, int name_length, zval *data TSRMLS_DC)
{
    char *key;
    long *length;
    zend_mangle_property_name(&key,&length,"*",1,name,name_length,0);
    zend_hash_update(Z_OBJPROP_P(object),key,length,&data,sizeof(zval *),NULL);
    efree(key);

    return SUCCESS;
}

void php_git_throw_exception(zend_class_entry *exception,int error_code, char *message TSRMLS_DC)
{
    if(exception == NULL) {
        //will be fix soon.
        exception = spl_ce_RuntimeException;
    }

    if(message != NULL) {
        zend_throw_exception_ex(exception, 0 TSRMLS_CC, message);
    } else {
        zend_throw_exception_ex(exception, 0 TSRMLS_CC, git_strerror(error_code));
    }
}

int php_git_odb_init(zval **object, git_odb *database TSRMLS_DC)
{
    zval *backends;

    MAKE_STD_ZVAL(*object);
    object_init_ex(*object,git_odb_class_entry);
    php_git_odb_t *odb_t = (php_git_odb_t *) zend_object_store_get_object(*object TSRMLS_CC);
    odb_t->odb = database;

    MAKE_STD_ZVAL(backends);
    array_init(backends);

    php_git_add_protected_property_zval_ex(*object,"backends",sizeof("backends"),backends TSRMLS_CC);

    return SUCCESS;
}

void php_git_commit_init(zval **object, git_commit *commit, git_repository *repository TSRMLS_DC)
{
    zval *author, *committer;

    MAKE_STD_ZVAL(*object);
    object_init_ex(*object,git_commit_class_entry);

    create_signature_from_commit(&author, git_commit_author(commit));
    create_signature_from_commit(&committer, git_commit_committer(commit));

    php_git_commit_t *cobj = (php_git_commit_t *) zend_object_store_get_object(*object TSRMLS_CC);
    cobj->object = commit;
    cobj->repository = repository;


    int parent_count = git_commit_parentcount(commit);
    int i;
    zval *parents;
    MAKE_STD_ZVAL(parents);
    array_init(parents);
    for (i = 0; i < parent_count; i++) {
        add_next_index_string(parents,git_oid_allocfmt(git_commit_parent_oid(commit,i)),1);
    }
    
    php_git_add_protected_property_zval_ex(*object,"author",sizeof("author"),author TSRMLS_CC);
    php_git_add_protected_property_zval_ex(*object,"committer",sizeof("committer"),committer TSRMLS_CC);
    php_git_add_protected_property_string_ex(*object,"tree",sizeof("tree"),git_oid_allocfmt(git_commit_tree_oid(commit)),1 TSRMLS_CC);
    php_git_add_protected_property_string_ex(*object,"message",sizeof("message"),git_commit_message(commit), 1 TSRMLS_CC);
    php_git_add_protected_property_zval_ex(*object,"parents",sizeof("parents"),parents TSRMLS_CC);
}

// probably this method will be deplicated.
int git_tree_entry_resolve_byname(git_tree_entry **object, git_tree *tree, git_repository *repository, const char *path)
{
    const git_tree_entry *entry;
    git_tree *tmp = tree;
    int attribute, length, offset, position, len;
    char buffer[256];
    memset(buffer,'\0',256);
    char *p;
    offset = 0;
    position = 0;
    len = 0;
    length = strlen(path);
    p = path;

    int ret = GIT_ERROR;

    while (position < length) {
        if(path[position] == '/') {
            memcpy(buffer,p, position-offset);
            buffer[position-offset] = '\0';

            offset = position+1;
            p+=offset;

            entry = git_tree_entry_byname(tmp,buffer);
            if(entry == NULL) {
                RETURN_FALSE;
            }

            attribute = git_tree_entry_attributes(entry);
            tmp = NULL;
            ret = git_tree_entry_2object(&tmp,repository,entry);
            if(ret != GIT_SUCCESS) {
                RETURN_FALSE;
            }
        } else if (position == length-1) {
            memset(buffer,'\0',256);
            memcpy(buffer,p, position+1-offset);

            int c = git_tree_entrycount(tmp);
            int i = 0;
            for(i =0; i < c; i++){
                git_tree_entry *e = git_tree_entry_byindex(tmp,i);
            }
            //entry_sort_cmp
            entry = git_tree_entry_byname(tmp,"git2.h");
            if(entry == NULL) {
                RETURN_FALSE;
            }
        }
        position++;
    }

    *object = entry;
    if(entry == NULL) {
        return GIT_ERROR;
    } else {
        return GIT_SUCCESS;
    }
}


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
    git_tree_builder_init(TSRMLS_C);
    git_tree_iterator_init(TSRMLS_C);
    git_init_tree(TSRMLS_C);
    git_init_commit(TSRMLS_C);
    git_init_tree_entry(TSRMLS_C);
    git_init_tag(TSRMLS_C);
    git_init_blob(TSRMLS_C);
    git_init_odb(TSRMLS_C);
    git_init_rawobject(TSRMLS_C);
    git_init_backend(TSRMLS_C);
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
    php_printf("PHP libgit2 Extension\n");
    php_info_print_table_start();
    php_info_print_table_row(2,"Version", PHP_GIT_EXTVER "-dev");
    php_info_print_table_row(2,"libgit2 version", LIBGIT2_VERSION);
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
