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
    git_repository_newobject(&commit, repository, GIT_OBJ_COMMIT);
    object_init_ex(object, git_commit_class_entry);

    ret = zend_list_insert(commit, le_git_commit);

    add_property_resource(object, "commit", ret);
    zend_list_addref(ret);
}



ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_commiter, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()
PHP_METHOD(git_commit, setCommiter)
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

    commit = php_get_git_commit(getThis() TSRMLS_CC);
    signature = git_signature_new(
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"name",4, 0 TSRMLS_CC)),
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"email",5, 0 TSRMLS_CC)),
        Z_LVAL_P(zend_read_property(git_signature_class_entry, z_signature,"time",4, 0 TSRMLS_CC)),
        0
    );
    git_commit_set_author(commit, signature);
    add_property_zval_ex(object,"commiter",9,z_signature);
}
PHP_METHOD(git_commit, getCommiter)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"commiter",8, 0 TSRMLS_CC);
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

    commit = php_get_git_commit(getThis() TSRMLS_CC);
    signature = git_signature_new(
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"name",4, 0 TSRMLS_CC)),
        Z_STRVAL_P(zend_read_property(git_signature_class_entry, z_signature,"email",5, 0 TSRMLS_CC)),
        Z_LVAL_P(zend_read_property(git_signature_class_entry, z_signature,"time",4, 0 TSRMLS_CC)),
        0
    );
    git_commit_set_author(commit, signature);
    add_property_zval_ex(object,"author",7,z_signature);
}

PHP_METHOD(git_commit, getAuthor)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"author",6, 0 TSRMLS_CC);
    RETURN_ZVAL(signature,0, 0);
}

PHPAPI function_entry php_git_commit_methods[] = {
    PHP_ME(git_commit, __construct,  arginfo_git_commit__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setAuthor,  arginfo_git_commit_set_author, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getAuthor, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setCommiter,  arginfo_git_commit_set_commiter, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_commit(TSRMLS_C)
{
    zend_class_entry git_commit_ce;
    INIT_CLASS_ENTRY(git_commit_ce, "GitCommit", php_git_commit_methods);
    git_commit_class_entry = zend_register_internal_class(&git_commit_ce TSRMLS_CC);
}