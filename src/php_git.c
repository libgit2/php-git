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
#include <spl/spl_array.h>
#include <zend_interfaces.h>
#include <string.h>
#include <time.h>

PHPAPI zend_class_entry *git_class_entry;
PHPAPI zend_class_entry *git_index_class_entry;
PHPAPI zend_class_entry *git_walker_class_entry;
PHPAPI zend_class_entry *git_tree_class_entry;
//Todo: そのうち
//PHPAPI zend_object_handlers php_git_object_handlers;


/**
 * Git Resource
 */
static int le_git;
	
/**
 * GitIndex Resource
 */
static int le_git_index;

/**
 * GitWalker Resource
 */
static int le_git_walker;

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

static git_revwalk *php_get_git_walker(zval *obj TSRMLS_DC) {
    zval **tmp = NULL;
    git_revwalk *walker= NULL;
    int id = 0, type = 0;
    if (zend_hash_find(Z_OBJPROP_P(obj), "walker", strlen("walker") + 1,(void **)&tmp) == FAILURE) {
        return NULL;
    }

    id = Z_LVAL_PP(tmp);
    walker = (git_revwalk *) zend_list_find(id, &type);
    return walker;
}


static void free_git_resource(zend_rsrc_list_entry *resource TSRMLS_DC)
{
    git_repository_free((git_repository *) resource->ptr);
}

static void free_git_index_resource(zend_rsrc_list_entry *resource TSRMLS_DC)
{
    git_index_free((git_index *) resource->ptr);
}

static void free_git_walker_resource(zend_rsrc_list_entry *resource TSRMLS_DC)
{
    git_revwalk_free((git_revwalk*) resource->ptr);
}

// Git Walker(ファイル分割するのを調べるの時間かかりそうだからとりあえず書くよ)

PHP_METHOD(git_walker, __construct)
{
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker_hide, 0, 0, 1)
	ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git_walker, hide)
{
    char *hash;
    int hash_len = 0;
    git_revwalk *walker;
    git_commit *commit;
    git_repository *repository;
    git_oid oid;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	    "s", &hash, &hash_len) == FAILURE){
		return;
	}

    walker = php_get_git_walker(getThis() TSRMLS_DC);
    repository = git_revwalk_repository(walker);
    
    git_oid_mkstr(&oid,hash);
    git_commit_lookup(&commit,repository,&oid);

    git_revwalk_hide(walker,commit);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker_push, 0, 0, 1)
	ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git_walker, push)
{
    char *hash;
    int hash_len = 0;
    git_oid oid;
    git_commit *head;
    git_revwalk *walker;
    git_repository *repository;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	    "s", &hash, &hash_len) == FAILURE){
		return;
	}

    walker = php_get_git_walker(getThis() TSRMLS_DC);
    repository = git_revwalk_repository(walker);
    
    git_oid_mkstr(&oid,hash);
    git_commit_lookup(&head,repository,&oid);
    
    git_revwalk_push(walker,head);
}

PHP_METHOD(git_walker, next)
{
    zval *git_commit_object;
    char *hash;
    int hash_len = 0;
    char oid[GIT_OID_HEXSZ];
    git_commit *commit;
    git_revwalk *walker;
    git_signature *signature;

    walker = php_get_git_walker(getThis() TSRMLS_DC);
    commit = git_revwalk_next(walker);
    if(commit == NULL){
        RETURN_FALSE;
    }
    /**
     * git_signature
     * (char*)->name
     * (char*)->email
     * (git_time)->when
     */
    signature = git_commit_author(commit);

    //printf("commit:%s\n",signature->email);

	MAKE_STD_ZVAL(git_commit_object);
	object_init(git_commit_object);
    git_oid_fmt(&oid,git_commit_id(commit));

    add_property_string_ex(git_commit_object,"oid",4, &oid, 1 TSRMLS_DC);
    add_property_string_ex(git_commit_object,"message",8, git_commit_message(commit), 1 TSRMLS_DC);
    add_property_string_ex(git_commit_object,"message_short",14, git_commit_message_short(commit), 1 TSRMLS_DC);
	//add_property_string_ex(git_commit_object,"data", 5, git_blob_rawcontent(blob), 1 TSRMLS_CC);
    RETURN_ZVAL(git_commit_object,1,0);
}

// GitIndex implements Iterator
PHP_METHOD(git_index, current)
{
    git_index *index;
    zval *entry_count;
	index  = php_get_git_index( getThis() TSRMLS_CC);
    zval *offset;
    //FIXME: ほぼGit::getIndexのコピペ。
    long *z_offset;
	git_index_entry *entry;
	zval *git_index_entry;
	char oid[GIT_OID_HEXSZ];

    offset = zend_read_property(git_index_class_entry,getThis(),"offset",6,0 TSRMLS_DC);
    z_offset = Z_LVAL_P(offset);
	entry = git_index_get(index,z_offset);
    if(entry == NULL){
        return;
    }

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

PHP_METHOD(git_index, key)
{
    git_index *index;
	git_index_entry *entry;
    zval *entry_count;
    zval *offset;

	char oid[GIT_OID_HEXSZ];
	index  = php_get_git_index( getThis() TSRMLS_CC);
    offset = zend_read_property(git_index_class_entry,getThis(),"offset",6,0 TSRMLS_DC);
	entry = git_index_get(index,Z_LVAL_P(offset));
    if(entry == NULL){
        return;
    }
    git_oid_fmt(oid,&entry->oid);
    
    RETVAL_STRINGL(&oid,GIT_OID_HEXSZ,1);
}

PHP_METHOD(git_index, next)
{
    zval *offset;
    offset = zend_read_property(git_index_class_entry,getThis(),"offset",6,0 TSRMLS_DC);
    zend_update_property_long(git_index_class_entry, getThis(), "offset",6, Z_LVAL_P(offset)+1 TSRMLS_DC);

    RETURN_TRUE;
}

PHP_METHOD(git_index, rewind)
{
    add_property_long(getThis(), "offset", 0);
}

PHP_METHOD(git_index, valid)
{
    zval *entry_count;
    zval *offset;
    long *z_entry_count;
    long *z_offset;

    entry_count = zend_read_property(git_index_class_entry,getThis(),"entry_count",11,0 TSRMLS_DC);
    offset = zend_read_property(git_index_class_entry,getThis(),"offset",6,0 TSRMLS_DC);
    z_entry_count = Z_LVAL_P(entry_count);
    z_offset = Z_LVAL_P(offset);
    
    if(z_offset < z_entry_count && z_offset >= 0){
        RETURN_TRUE;
    }else{
        RETURN_FALSE;
    }
}


// GitIndex implements Countable
PHP_METHOD(git_index, count)
{
    git_index *index;
    zval *entry_count;
	index  = php_get_git_index( getThis() TSRMLS_CC);
    entry_count = zend_read_property(git_index_class_entry,getThis(),"entry_count",11,0 TSRMLS_DC);

    long *count = Z_LVAL_P(entry_count);

    RETVAL_LONG(count);
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

    add_property_long(object, "offset", 0);
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
    add_property_long(index_object, "offset", 0);
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getTree)
{
    zval *object = getThis();
	git_repository *repository;
    git_tree *tree;
    git_oid oid;
    char *hash;
    int hash_len = 0;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	    "s", &hash, &hash_len) == FAILURE){
		return;
	}
    git_oid_mkstr(&oid, hash);
    
	repository = php_get_git_repository( object TSRMLS_CC);
    int ret = git_tree_lookup(&tree, repository, &oid);
    if(ret != GIT_SUCCESS){
        //FIXME
        printf("not found");
        RETURN_FALSE;
    }
    
    printf("entry_count:%d\n",git_tree_entrycount(tree));
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_git_walker, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getWalker)
{
    zval *object = getThis();
	git_repository *repository;
    git_index *index;
    //FIXME: GitWalkerを呼びたいけどコレでいいの？
    zval *walker_object = emalloc(sizeof(zval));
    git_revwalk *walk;
    int ret = 0;

	repository = php_get_git_repository( object TSRMLS_CC);
    object_init_ex(walker_object, git_walker_class_entry);

    ret = git_revwalk_new(&walk,repository);

    ret = zend_list_insert(walk, le_git_walker);
    add_property_resource(walker_object, "walker", ret);

    zend_list_addref(ret);
    RETURN_ZVAL(walker_object,1,0);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_get_branch, 0, 0, 1)
    ZEND_ARG_INFO(0, branch)
ZEND_END_ARG_INFO()

PHP_METHOD(git, getBranch)
{
    zval *object = getThis();
    zval *prop;
	git_repository *repository;
    char *branch;
    char buf[255];
    int branch_len = 0;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	        "s", &branch, &branch_len) == FAILURE){
		return;
	}

	repository = php_get_git_repository( object TSRMLS_CC);
    prop = zend_read_property(git_class_entry,object,"path",4,0 TSRMLS_DC);
    char *uhi = Z_STRVAL_P(prop);
    
    //FIXME: 適当すぎる
    FILE *fp;
    sprintf(&buf,"%s/refs/heads/%s",uhi,branch);
    fp = fopen(&buf,"r");
    memset(buf,0,sizeof(buf));
    fread(buf,1,40,fp);
    fclose(fp);
    
    RETVAL_STRINGL(buf,40,1 TSRMLS_DC);
}


// Git
PHPAPI function_entry php_git_methods[] = {
	PHP_ME(git, __construct, arginfo_git_construct, ZEND_ACC_PUBLIC)
	PHP_ME(git, getObject, arginfo_git_get_object, ZEND_ACC_PUBLIC)
    PHP_ME(git, getIndex, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git, getBranch, arginfo_git_get_branch, ZEND_ACC_PUBLIC)
    PHP_ME(git, getWalker, arginfo_git_walker, ZEND_ACC_PUBLIC) // FIXME
    PHP_ME(git, getTree, arginfo_git_get_tree, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};


// GitIndex
PHPAPI function_entry php_git_index_methods[] = {
	PHP_ME(git_index, __construct, arginfo_git_index_construct, ZEND_ACC_PUBLIC)
	PHP_ME(git_index, getEntry, arginfo_git_index_get_entry, ZEND_ACC_PUBLIC)
	PHP_ME(git_index, refresh, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, find, arginfo_git_index_find, ZEND_ACC_PUBLIC)
    // Countable
    PHP_ME(git_index, count, NULL, ZEND_ACC_PUBLIC)
    // Iterator
    PHP_ME(git_index, current, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, key, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, next, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, rewind, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, valid, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

// GitWalker
PHPAPI function_entry php_git_walker_methods[] = {
    PHP_ME(git_walker, __construct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, push, arginfo_git_walker_push, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, next, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, hide, arginfo_git_walker_hide, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHPAPI function_entry php_git_tree_methods[] = {
    PHP_ME(git_walker, __construct, NULL, ZEND_ACC_PUBLIC)
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
    zend_class_implements(git_index_class_entry TSRMLS_CC, 2, spl_ce_Countable, spl_ce_Iterator);


    zend_class_entry git_walker_ce;
    INIT_CLASS_ENTRY(git_walker_ce,"GitWalker",php_git_walker_methods);
    git_walker_class_entry = zend_register_internal_class(&git_walker_ce TSRMLS_CC);
    
    zend_class_entry git_tree_ce;
    INIT_CLASS_ENTRY(git_tree_ce, "GitTree", php_git_tree_methods);
    git_tree_class_entry = zend_register_internal_class(&git_tree_ce TSRMLS_CC);

    /**
	 * Resources
	 */
	le_git = zend_register_list_destructors_ex(free_git_resource, NULL, "Git", module_number);
	le_git_index = zend_register_list_destructors_ex(free_git_index_resource, NULL, "GitIndex", module_number);
    le_git_walker = zend_register_list_destructors_ex(free_git_walker_resource, NULL, "GitWalker", module_number);

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
