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

extern void create_tree_entry_from_entry(zval **object, git_tree_entry *entry);
extern zend_object_value php_git_repository_new(zend_class_entry *ce TSRMLS_DC);

PHPAPI zend_class_entry *git_commit_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_committer, 0, 0, 1)
    ZEND_ARG_INFO(0, committer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_parent, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_author, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_message, 0, 0, 1)
    ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()
    
ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_get_parent, 0, 0, 1)
    ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

static void php_git_commit_free_storage(php_git_commit_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    //RepositoryでFreeされるよ
    obj->object = NULL;
    obj->repository = NULL;
    efree(obj);
}

zend_object_value php_git_commit_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_commit_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_commit_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

PHP_METHOD(git_commit, __construct)
{
    zval *z_repository;
    git_commit *commit;
    git_repository *repository;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }
    object_init_ex(object, git_commit_class_entry);
    php_git_commit_t *cobj = (php_git_commit_t *) zend_object_store_get_object(object TSRMLS_CC);
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(z_repository TSRMLS_CC);

    
    ret = git_commit_new(&commit,myobj->repository);
    if(ret != GIT_SUCCESS){
        //FIXME
        RETURN_FALSE;
    }
    cobj->repository = myobj->repository;
    cobj->object = commit;
}



PHP_METHOD(git_commit, setCommitter)
{
    zval *this = getThis();
    zval *z_signature;
    git_signature *signature;
    php_git_commit_t *c_obj;
    php_git_signature_t *s_obj;
    git_commit *commit;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_signature) == FAILURE){
        return;
    }

    c_obj = (php_git_commit_t *) zend_object_store_get_object(this TSRMLS_CC);
    s_obj = (php_git_signature_t *) zend_object_store_get_object(z_signature TSRMLS_CC);
    git_commit_set_author(c_obj->object, s_obj->signature);
    add_property_zval_ex(object,"committer",10,z_signature);
}

PHP_METHOD(git_commit, getCommitter)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"committer",9, 0 TSRMLS_CC);

    zval_copy_ctor(signature);
    RETURN_ZVAL(signature,0, 0);
}

PHP_METHOD(git_commit, setParent)
{
    zval *this = getThis();
    php_git_commit_t *c_obj;
    php_git_signature_t *s_obj;
    git_commit *commit;
    git_oid oid;
    char *hash;
    int hash_len = 0;
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }

    git_oid_mkstr(&oid, hash);

    c_obj = (php_git_commit_t *) zend_object_store_get_object(this TSRMLS_CC);

    git_commit_lookup(&commit,c_obj->repository,&oid);
    git_commit_add_parent(c_obj->object, commit);
    //FIXME: not parent. parents.
    add_property_string_ex(this,"parent",sizeof("parent"),hash, 1 TSRMLS_CC);
}


PHP_METHOD(git_commit, setAuthor)
{
    zval *this = getThis();
    zval *z_signature;
    git_signature *signature;
    php_git_commit_t *c_obj;
    php_git_signature_t *s_obj;
    git_commit *commit;
    zval *object = getThis();
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_signature) == FAILURE){
        return;
    }

    c_obj = (php_git_commit_t *) zend_object_store_get_object(this TSRMLS_CC);
    s_obj = (php_git_signature_t *) zend_object_store_get_object(z_signature TSRMLS_CC);
    git_commit_set_committer(c_obj->object, s_obj->signature);
    add_property_zval_ex(object,"author",sizeof("author"),z_signature);
}

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

    php_git_commit_t *myobj = (php_git_commit_t *) zend_object_store_get_object(object TSRMLS_CC);
    repository = myobj->repository;

    git_oid_mkstr(&oid, hash);
    git_object_lookup ((git_object **)&tree, repository, &oid, GIT_OBJ_TREE);
    git_commit_set_tree(myobj->object,tree);

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
        char mbuf[41] = {0};
        char *offset;
        const git_oid *moid;
        zval *array_ptr;

        for(i; i < r; i++){
            entry = git_tree_entry_byindex(tree,i);
            moid = git_tree_entry_id(entry);
            git_oid_to_string(mbuf,41,moid);

            MAKE_STD_ZVAL(array_ptr);
            object_init_ex(array_ptr, git_tree_entry_class_entry);

            add_property_string(array_ptr, "name", (char *)git_tree_entry_name(entry), 1);
            add_property_string(array_ptr, "oid", mbuf, 1);
            add_property_long(array_ptr, "mode", git_tree_entry_attributes(entry));

            add_next_index_zval(entries,  array_ptr);
        }

        //add_property_long(git_tree, "entry", git_tree_entrycount(tree));
        add_property_zval(git_tree,"entries", entries);
        add_property_zval(object,"tree",git_tree);
        //

        RETURN_TRUE;
    }
    //
}

PHP_METHOD(git_commit, setMessage)
{
    php_git_commit_t *this;
    char *message;
    int message_len = 0;
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &message, &message_len) == FAILURE){
        return;
    }
    this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_commit_set_message(this->object,message);

    RETURN_TRUE;
}


PHP_METHOD(git_commit, getMessage)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    const char *message;
    
    message = git_commit_message(this->object);
    RETURN_STRING(message,1 TSRMLS_C);
}

PHP_METHOD(git_commit, getShortMessage)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    const char *message;
    
    message = git_commit_message_short(this->object);
    RETURN_STRING(message,1 TSRMLS_C);
}

PHP_METHOD(git_commit, getTree)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_tree *ref_tree;
    git_commit_tree(&ref_tree, this->object);
    const git_oid *oid = 	git_object_id((git_object*)ref_tree);

    git_tree *tree;
    int ret = git_object_lookup((git_object **)&tree, git_object_owner((git_object*)this->object),oid, GIT_OBJ_TREE);
    if(ret != GIT_SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "specified tree not found.");
        return;
    }

    git_oid *tree_oid;
    zval *git_tree;
    zval *entry;

    MAKE_STD_ZVAL(git_tree);
    object_init_ex(git_tree, git_tree_class_entry);
    php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
    tobj->object = tree;

/*
    int r = git_tree_entrycount(tree);
    int i = 0;

    for(i; i < r; i++){
        create_tree_entry_from_entry(&entry,git_tree_entry_byindex(tree,i));
        add_next_index_zval(entries, entry);
    }

    add_property_zval(git_tree,"entries", entries);
*/
    RETURN_ZVAL(git_tree,0,0);
}

PHP_METHOD(git_commit, getAuthor)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"author",6, 0 TSRMLS_CC);

    zval_copy_ctor(signature);
    RETURN_ZVAL(signature,0, 0);
}

PHP_METHOD(git_commit, getParent)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    php_git_commit_t *obj;
    git_commit *commit;
    zval *zcommit;
    int offset = 0;
    int ret = 0;
    zval *author;
    zval *committer;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "|l", &offset) == FAILURE){
        return;
    }
    
    ret = git_commit_parent(&commit, this->object,offset);
    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "specified offset not found.");
        RETURN_FALSE;
    }

    
    MAKE_STD_ZVAL(zcommit);
    object_init_ex(zcommit,git_commit_class_entry);
    obj = (php_git_commit_t *) zend_object_store_get_object(zcommit TSRMLS_CC);
    obj->object = commit;

    create_signature_from_commit(&author, git_commit_author(obj->object));
    create_signature_from_commit(&committer, git_commit_committer(obj->object));
    
    add_property_zval(zcommit,"author", author);
    add_property_zval(zcommit,"committer", committer);

    RETURN_ZVAL(zcommit,1,0);

    efree(zcommit);
    efree(author);
    efree(committer);
}

PHPAPI function_entry php_git_commit_methods[] = {
    PHP_ME(git_commit, __construct,     arginfo_git_commit__construct,   ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setTree,         arginfo_git_commit_set_tree,     ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getTree,         NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setAuthor,       arginfo_git_commit_set_author,   ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getAuthor,       NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setCommitter,    arginfo_git_commit_set_committer,ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getCommitter,    NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setMessage,      arginfo_git_commit_set_message,  ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getMessage,      NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getShortMessage, NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setParent,       arginfo_git_commit_set_parent,   ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getParent,       arginfo_git_commit_get_parent,   ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_commit(TSRMLS_C)
{
    zend_class_entry git_commit_ce;
    INIT_NS_CLASS_ENTRY(git_commit_ce, PHP_GIT_NS,"Commit", php_git_commit_methods);

    git_commit_class_entry = zend_register_internal_class_ex(&git_commit_ce,git_object_class_entry,NULL TSRMLS_CC);
	git_commit_class_entry->create_object = php_git_commit_new;
    zend_declare_property_null(git_commit_class_entry, "author",   sizeof("author")-1,    ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "committer",sizeof("committer")-1, ZEND_ACC_PUBLIC TSRMLS_CC);
}