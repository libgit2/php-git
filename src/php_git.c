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
#include <string.h>
#include <time.h>

PHPAPI zend_class_entry *git_class_entry;
PHPAPI zend_class_entry *git_index_class_entry;
PHPAPI zend_object_handlers php_git_object_handlers;

/**
 * Git Resource
 */
static int le_git;
	
/**
 * GitIndex Resource
 */
static int le_git_index;

// Git index(ファイル分割するのを調べるの時間かかりそうだからとりあえず書くよ)

static git_index *php_get_git_index(zval *obj TSRMLS_DC) {
    zval **tmp = NULL;
    git_index *index = NULL;
    int id = 0, type = 0;
    if (zend_hash_find(Z_OBJPROP_P(obj), "entries", strlen("entries") + 1,(void **)&tmp) == FAILURE) {
        return NULL;
    }

    id = Z_LVAL_PP(tmp);
    index = (git_index *) zend_list_find(id, &type);
    return index;
}

static git_repository *php_get_git_repository(zval *obj TSRMLS_DC) {
    zval **tmp = NULL;
    git_repository *repository = NULL;
    int id = 0, type = 0;
    if (zend_hash_find(Z_OBJPROP_P(obj), "repository", strlen("repository") + 1,(void **)&tmp) == FAILURE) {
        return NULL;
    }

    id = Z_LVAL_PP(tmp);
    repository = (git_repository *) zend_list_find(id, &type);
    return repository;
}

static void free_git_resource(zend_rsrc_list_entry *resource TSRMLS_DC)
{
    git_repository_free((git_repository *) resource->ptr);
}

static void free_git_index_resource(zend_rsrc_list_entry *resource TSRMLS_DC)
{
    git_index_free((git_index *) resource->ptr);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_find, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

PHP_METHOD(git_index, find)
{
	int offset = 0;
    char *path;
    int path_len = 0;
	git_index *index = NULL;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	    "s", &path, &path_len) == FAILURE){
		return;
	}

	index  = php_get_git_index( getThis() TSRMLS_CC);
    offset = git_index_find(index,path);

    if(offset >= 0){
        RETURN_LONG(offset);
    }
}

PHP_METHOD(git_index, refresh)
{
	git_index *index = NULL;
	index = php_get_git_index( getThis() TSRMLS_CC);
	git_index_read(index);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_get_entry, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

PHP_METHOD(git_index, getEntry)
{
	int offset = 0;
	git_index *index = NULL;
	git_index_entry *entry;
	zval *git_index_entry;
	char oid[GIT_OID_HEXSZ];

	index = php_get_git_index( getThis() TSRMLS_CC);
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
			"l", &offset) == FAILURE){
		return;
	}

	entry = git_index_get(index,offset);

    git_oid_fmt(oid,&entry->oid);

	MAKE_STD_ZVAL(git_index_entry);
	object_init(git_index_entry);

	add_property_string_ex(git_index_entry,"path", 5, entry->path, 1 TSRMLS_CC);
	add_property_string_ex(git_index_entry,"oid",4,oid, 1 TSRMLS_CC);
	add_property_long(git_index_entry,"dev",entry->dev);
	add_property_long(git_index_entry,"ino",entry->ino);
	add_property_long(git_index_entry,"mode",entry->mode);
	add_property_long(git_index_entry,"uid",entry->uid);
	add_property_long(git_index_entry,"gid",entry->gid);
	add_property_long(git_index_entry,"file_size",entry->file_size);
	add_property_long(git_index_entry,"flags",entry->flags);
	add_property_long(git_index_entry,"flags_extended",entry->flags_extended);
	add_property_long(git_index_entry,"ctime",time(&entry->ctime.seconds));
	add_property_long(git_index_entry,"mtime",time(&entry->mtime.seconds));
	
    RETURN_ZVAL(git_index_entry,1, 0);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_construct, 0, 0, 1)
  ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

PHP_METHOD(git_index, __construct)
{
	const char *repository_path = NULL;
	int ret = 0;
	int arg_len = 0;
	git_index *index;
	zval *object = getThis();
    object_init_ex(object, git_index_class_entry);

	if(!object){
		php_error_docref(NULL TSRMLS_CC, E_WARNING,
			"Constructor called statically!");
		RETURN_FALSE;
	}

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							"s", &repository_path, &arg_len) == FAILURE){
		return;
	}

    ret = git_index_open_bare(&index,repository_path);
    if(ret != GIT_SUCCESS){
    	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git repository not found.");
    	RETURN_FALSE;
    }
    git_index_read(index);

    ret = zend_list_insert(index, le_git_index);

    add_property_resource(object, "entries", ret);
	add_property_string_ex(object, "path",5,repository_path, 1 TSRMLS_CC);
	add_property_long(object, "entry_count",git_index_entrycount(index));
    zend_list_addref(ret);
}


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


PHP_METHOD(git, getIndex)
{
    zval *object = getThis();
	git_repository *repository;
    git_index *index;
    //FIXME: GitIndexを呼びたいけどコレでいいの？
    zval *index_object = emalloc(sizeof(zval));
    int ret = 0;

	repository = php_get_git_repository( object TSRMLS_CC);
    object_init_ex(index_object, git_index_class_entry);

    ret = git_index_open_inrepo(&index, repository);
    if(ret != GIT_SUCCESS){
    	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git repository not found.");
    	RETURN_FALSE;
    }
    git_index_read(index);

    ret = zend_list_insert(index, le_git_index);

    add_property_resource(index_object, "entries", ret);
    //Todo: Read from Git object.
	//add_property_string_ex(index_object, "path",5,index->index_file_path, 1 TSRMLS_CC);
	add_property_long(index_object, "entry_count",git_index_entrycount(index));
    zend_list_addref(ret);

    RETURN_ZVAL(index_object,1,0);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_object, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getObject)
{
    zval *object = getThis();
    zval *git_raw_object;
	git_repository *repository;
    git_odb *odb;
    git_blob *blob;
    git_oid oid;

    char *hash;
    int hash_len = 0;
    int ret = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	    "s", &hash, &hash_len) == FAILURE){
		return;
	}
    
    git_oid_mkstr(&oid, hash);
    
	repository = php_get_git_repository( object TSRMLS_CC);
    odb = git_repository_database(repository);
    
    if(git_odb_exists(odb,hash)){
		RETURN_FALSE;
    }else{
        ret = git_blob_lookup(&blob, repository,&oid);
        
        if(ret == GIT_SUCCESS){
        	MAKE_STD_ZVAL(git_raw_object);
        	object_init(git_raw_object);

        	add_property_string_ex(git_raw_object,"data", 5, git_blob_rawcontent(blob), 1 TSRMLS_CC);
            RETURN_ZVAL(git_raw_object,1,0);
        }else{
            RETURN_FALSE;
        }
    }

}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

PHP_METHOD(git, __construct)
{
	const char *repository_path = NULL;
	int ret = 0;
	int arg_len = 0;
	git_repository *repository;
	zval *object = getThis();

    object_init_ex(object, git_class_entry);

	if(!object){
		php_error_docref(NULL TSRMLS_CC, E_WARNING,
			"Constructor called statically!");
		RETURN_FALSE;
	}

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
							"s", &repository_path, &arg_len) == FAILURE){
		return;
	}

    ret = git_repository_open(&repository,repository_path);
    if(ret != GIT_SUCCESS){
    	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git repository not found.");
    	RETURN_FALSE;
    }

    ret = zend_list_insert(repository, le_git);

    add_property_resource(object, "repository", ret);
	add_property_string_ex(object, "path",5,repository_path, 1 TSRMLS_CC);
    zend_list_addref(ret);
}

// Git
PHPAPI function_entry php_git_methods[] = {
	PHP_ME(git, __construct, arginfo_git_construct, ZEND_ACC_PUBLIC)
	PHP_ME(git, getObject, arginfo_git_get_object, ZEND_ACC_PUBLIC)
    PHP_ME(git, getIndex, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};


// GitIndex
PHPAPI function_entry php_git_index_methods[] = {
	PHP_ME(git_index, __construct, arginfo_git_index_construct, ZEND_ACC_PUBLIC)
	PHP_ME(git_index, getEntry, arginfo_git_index_get_entry, ZEND_ACC_PUBLIC)
	PHP_ME(git_index, refresh, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, find, arginfo_git_index_find, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

// Git Global Functions
PHPAPI function_entry php_git_functions[] = {
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

	zend_class_entry git_index_ce;
	INIT_CLASS_ENTRY(git_index_ce,"GitIndex",php_git_index_methods);
	git_index_class_entry = zend_register_internal_class(&git_index_ce TSRMLS_CC);

	/**
	 * Resources
	 */
	le_git = zend_register_list_destructors_ex(free_git_resource, NULL, "Git", module_number);
	le_git_index = zend_register_list_destructors_ex(free_git_index_resource, NULL, "GitIndex", module_number);

	/**
	 * Git::Constants
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
