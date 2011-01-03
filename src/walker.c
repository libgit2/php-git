/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2010-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Shuhei Tanuma <stanuma@zynga.co.jp>                          |
  +----------------------------------------------------------------------+
*/

#include "php_git.h"
#include <spl/spl_array.h>
#include <zend_interfaces.h>
#include <string.h>
#include <time.h>


git_revwalk *php_get_git_walker(zval *obj TSRMLS_DC) {
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


// GitWalker
PHPAPI function_entry php_git_walker_methods[] = {
    PHP_ME(git_walker, __construct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, push, arginfo_git_walker_push, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, next, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_walker, hide, arginfo_git_walker_hide, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};



void git_init_walker(TSRMLS_D)
{
    zend_class_entry git_walker_ce;
    INIT_CLASS_ENTRY(git_walker_ce,"GitWalker",php_git_walker_methods);
    git_walker_class_entry = zend_register_internal_class(&git_walker_ce TSRMLS_CC);
}
