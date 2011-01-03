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

extern int le_git;
extern int le_git_tree;
extern int le_git_commit;
extern git_repository *php_get_git_repository(zval *obj TSRMLS_DC);

static git_commit *php_get_git_commit(zval *obj TSRMLS_DC) {
    zval **tmp = NULL;
    int id = 0, type = 0;
    if (zend_hash_find(Z_OBJPROP_P(obj), "commit", strlen("commit") + 1,(void **)&tmp) == FAILURE) {
        return NULL;
    }

    id = Z_LVAL_PP(tmp);
    return (git_commit *) zend_list_find(id, &type);
}


//GitCommit
ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, __construct)
{
    /*
        $commit = new GitCommit($repo);
        $repo->Commit();
    */

    zval *z_repository;
    git_commit *commit;
    git_repository *repository;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }
    repository = (git_repository *)php_get_git_repository(z_repository TSRMLS_DC);
    //git_repository_newobject(&commit, repository, GIT_OBJ_COMMIT);
    object_init_ex(object, git_commit_class_entry);
    add_property_zval(object, "repository", z_repository);
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_committer, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setCommitter)
{
    zval *z_signature;
    git_signature *signature;
    git_repository *repository;
    git_commit *commit;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_signature) == FAILURE){
        return;
    }

    /*
    commit = php_get_git_commit(getThis() TSRMLS_CC);
    signature = git_signature_new(
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"name",4, 0 TSRMLS_CC)),
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"email",5, 0 TSRMLS_CC)),
        Z_LVAL_P(zend_read_property(git_signature_class_entry, z_signature,"time",4, 0 TSRMLS_CC)),
        0
    );
    git_commit_set_committer(commit, signature);
    */
    add_property_zval_ex(object,"committer",10,z_signature);
}

PHP_METHOD(git_commit, getCommitter)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"committer",9, 0 TSRMLS_CC);
    RETURN_ZVAL(signature,0, 0);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_author, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setAuthor)
{
    zval *z_signature;
    git_signature *signature;
    git_repository *repository;
    git_commit *commit;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_signature) == FAILURE){
        return;
    }

    /*
    commit = php_get_git_commit(getThis() TSRMLS_CC);
    signature = git_signature_new(
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"name",4, 0 TSRMLS_CC)),
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"email",5, 0 TSRMLS_CC)),
        Z_LVAL_P(zend_read_property(git_signature_class_entry, z_signature,"time",4, 0 TSRMLS_CC)),
        0
    );
    */
    //git_commit_set_author(commit, signature);
    add_property_zval_ex(object,"author",7,z_signature);
}

PHP_METHOD(git_commit, write)
{
    zval *this = getThis();
    git_repository *repository;
    git_commit *commit;

    zval *repo = zend_read_property(git_commit_class_entry,this,"repository",sizeof("repository")-1,0 TSRMLS_CC);
    repository = php_get_git_repository(repo TSRMLS_CC);

    git_commit_new(&commit,repository);
    zval *author = zend_read_property(git_commit_class_entry,this,"author",sizeof("author")-1,0 TSRMLS_CC);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setTree)
{
    zval *object = getThis();
    char *hash;
    int hash_len;
    char *filename;
    git_oid oid;
    git_tree *tree;
    git_repository *repository;
    git_object *git_obj;
    int attr;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }
    zval *repo = zend_read_property(git_commit_class_entry,object,"repository",sizeof("repository")-1,0 TSRMLS_CC);
    repository = php_get_git_repository(repo TSRMLS_CC);
    git_oid_mkstr(&oid, hash);
    git_repository_lookup (&tree, repository, &oid, GIT_OBJ_TREE);
    if(tree){
        //コピペ
        zval *git_tree;
        zval *entries;
        git_tree_entry *entry;
        MAKE_STD_ZVAL(git_tree);
        MAKE_STD_ZVAL(entries);
        array_init(entries);
        object_init_ex(git_tree, git_tree_class_entry);

        int r = git_tree_entrycount(tree);
        int i = 0;
        char mbuf[40];
        char *offset;
        git_oid *moid;
        zval *array_ptr;

        for(i; i < r; i++){
            entry = git_tree_entry_byindex(tree,i);
            moid = git_tree_entry_id(entry);
            git_oid_to_string(mbuf,41,moid);

            MAKE_STD_ZVAL(array_ptr);
            object_init_ex(array_ptr, git_tree_entry_class_entry);

            add_property_string(array_ptr, "name", git_tree_entry_name(entry), 1);
            add_property_string(array_ptr, "oid", mbuf, 1);
            add_property_long(array_ptr, "attr", git_tree_entry_attributes(entry));

            add_next_index_zval(entries,  array_ptr);
        }

        //add_property_long(git_tree, "entry", git_tree_entrycount(tree));
        int ret = zend_list_insert(tree, le_git_tree);
        add_property_resource(git_tree, "tree", ret);
        add_property_zval(git_tree,"entries", entries);
        add_property_zval(object,"tree",git_tree);
        //

        RETURN_TRUE;
    }
    //
}


PHP_METHOD(git_commit, getAuthor)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"author",6, 0 TSRMLS_CC);
    RETURN_ZVAL(signature,0, 0);
}

PHPAPI function_entry php_git_commit_methods[] = {
    PHP_ME(git_commit, __construct,  arginfo_git_commit__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setTree,  arginfo_git_commit_set_tree, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setAuthor,  arginfo_git_commit_set_author, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getAuthor, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setCommitter,  arginfo_git_commit_set_committer, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getCommitter,  NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, write, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_commit(TSRMLS_C)
{
    zend_class_entry git_commit_ce;
    INIT_CLASS_ENTRY(git_commit_ce, "GitCommit", php_git_commit_methods);
    git_commit_class_entry = zend_register_internal_class(&git_commit_ce TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "author",sizeof("author")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "committer",sizeof("committer")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
}