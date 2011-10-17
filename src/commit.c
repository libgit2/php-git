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

extern void create_tree_entry_from_entry(zval **object, git_tree_entry *entry, git_repository *repository);
extern zend_object_value php_git_repository_new(zend_class_entry *ce TSRMLS_DC);

PHPAPI zend_class_entry *git_commit_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_get_parent, 0, 0, 1)
    ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_author, 0, 0, 1)
    ZEND_ARG_INFO(0, author)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_committer, 0, 0, 1)
    ZEND_ARG_INFO(0, committer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_parents, 0, 0, 1)
    ZEND_ARG_INFO(0, parents)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_message, 0, 0, 1)
    ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_set_tree, 0, 0, 1)
    ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_write, 0, 0, 1)
    ZEND_ARG_INFO(0, update_ref)
ZEND_END_ARG_INFO()

static void php_git_commit_free_storage(php_git_commit_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
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
    zval *object = getThis();
    zval *z_repository;
    git_commit *commit;
    git_repository *repository;
    int ret;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }
    object_init_ex(object, git_commit_class_entry);
    php_git_commit_t *cobj = (php_git_commit_t *) zend_object_store_get_object(object TSRMLS_CC);
    php_git_repository_t *myobj = (php_git_repository_t *) zend_object_store_get_object(z_repository TSRMLS_CC);

    
    cobj->repository = myobj->repository;
}

PHP_METHOD(git_commit, getCommitter)
{
    zval *object = getThis();
    zval *signature = zend_read_property(git_commit_class_entry, object,"committer",9, 0 TSRMLS_CC);

    zval_copy_ctor(signature);
    RETURN_ZVAL(signature,0, 0);
}

PHP_METHOD(git_commit, getMessage)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    const char *message;
    
    message = git_commit_message(this->object);
    RETURN_STRING(message,1);
}

PHP_METHOD(git_commit, getShortMessage)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    const char *message;
    
    message = git_commit_message_short(this->object);
    RETURN_STRING(message,1);
}

PHP_METHOD(git_commit, getTree)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_tree *ref_tree, *tree;
    git_oid *tree_oid;
    zval *git_tree, *entry;
    const git_oid *oid;

    git_commit_tree(&ref_tree, this->object);
    oid = git_object_id((git_object*)ref_tree);

    int ret = git_object_lookup((git_object **)&tree, git_object_owner((git_object*)this->object),oid, GIT_OBJ_TREE);
    if(ret != GIT_SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "specified tree not found.");
        return;
    }


    MAKE_STD_ZVAL(git_tree);
    object_init_ex(git_tree, git_tree_class_entry);
    php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
    tobj->object = tree;
    tobj->repository = this->repository;

    RETURN_ZVAL(git_tree,0,1);
}

PHP_METHOD(git_commit, setAuthor)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *author;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &author) == FAILURE){
        return;
    }

    if(!instanceof_function(Z_OBJCE_P(author), git_signature_class_entry TSRMLS_CC)){
        fprintf(stderr,"Git\\Commit::setAuthor() requires Git\\Signature");
        return;
    }

    add_property_zval(getThis(),"author", author);
}

PHP_METHOD(git_commit, setCommitter)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *committer;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &committer) == FAILURE){
        return;
    }

    if(!instanceof_function(Z_OBJCE_P(committer), git_signature_class_entry TSRMLS_CC)){
        fprintf(stderr,"Git\\Commit::setCommitter() requires Git\\Signature");
        return;
    }

    add_property_zval(getThis(),"committer", committer);
}

PHP_METHOD(git_commit, setTree)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *tree;
    int tree_len;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &tree,&tree_len) == FAILURE){
        return;
    }

    add_property_string(getThis(),"tree", tree,1);
}


PHP_METHOD(git_commit, setParents)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *parents;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &parents) == FAILURE){
        return;
    }

    add_property_zval(getThis(),"parents", parents);
}

PHP_METHOD(git_commit, write)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid oid, tree_oid, **parents, **p, *tmp;
    php_git_signature_t *author, *committer;
    zval *z_author, *z_committer, *z_parents, **data;
    char *update_ref, *message, *tree_oid_str = NULL;
    char out[GIT_OID_HEXSZ+1];
    int count, i, update_ref_len = 0;
    git_reference *ref;

    HashTable *array_hash;
    HashPosition pointer;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "|s", &update_ref,&update_ref_len) == FAILURE){
        return;
    }
    
    if(ZEND_NUM_ARGS() == 0) {
        if(git_reference_lookup(&ref,this->repository,"HEAD")==GIT_SUCCESS){
            if (git_reference_type(ref) == GIT_REF_SYMBOLIC) {
                git_reference *ref2;
                git_reference_resolve(&ref2,ref);
                update_ref = (char *)git_reference_name(ref2);
            } else {
                update_ref = (char *)git_reference_name(ref);
            }
        }
    }


    tree_oid_str = Z_STRVAL_P(zend_read_property(git_commit_class_entry, getThis(),"tree",sizeof("tree")-1, 0 TSRMLS_CC));
    git_oid_fromstr(&tree_oid, tree_oid_str);

    z_author = zend_read_property(git_commit_class_entry, getThis(),"author",sizeof("author")-1, 0 TSRMLS_CC);
    author = (php_git_signature_t *) zend_object_store_get_object(z_author TSRMLS_CC);

    z_committer = zend_read_property(git_commit_class_entry, getThis(),"committer",sizeof("committer")-1, 0 TSRMLS_CC);
    committer = (php_git_signature_t *) zend_object_store_get_object(z_committer TSRMLS_CC);
    
    z_parents = zend_read_property(git_commit_class_entry, getThis(),"parents",sizeof("parents")-1, 0 TSRMLS_CC);

    count = zend_hash_num_elements(Z_ARRVAL_P(z_parents));


    array_hash = Z_ARRVAL_P(z_parents);
    parents = (git_oid**)calloc(count,sizeof(git_oid));
    p = parents;

    for (zend_hash_internal_pointer_reset_ex(array_hash, &pointer);
        zend_hash_has_more_elements_ex(array_hash,&pointer) == SUCCESS;
        zend_hash_move_forward_ex(array_hash,&pointer)
    ) {
        tmp = (git_oid *)malloc(sizeof(git_oid));
        zend_hash_get_current_data_ex(array_hash, (void **)&data, &pointer);
        git_oid_fromstr(tmp,Z_STRVAL_PP(data));

        *p = tmp;
        p++;
    }
    
    message = Z_STRVAL_P(zend_read_property(git_commit_class_entry, getThis(),"message",sizeof("message")-1, 0 TSRMLS_CC));
    git_commit_create(&oid,
        this->repository,
        update_ref,
        author->signature,
        committer->signature,
		NULL, // Message encoding (Should probably fix this at some point)
        message,
        &tree_oid,
        count,
        parents
    );

    git_oid_to_string(out,GIT_OID_HEXSZ+1,&oid);

    for(i = 0; i < count;i++){
        free(parents[i]);
    }
    free(parents);

    RETVAL_STRING(out,1);
}

PHP_METHOD(git_commit, setMessage)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *message;
    int message_len;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &message,&message_len) == FAILURE){
        return;
    }

    add_property_string(getThis(),"message", message, 1);
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
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC, "specified offset not found");
        RETURN_FALSE;
    }

    php_git_commit_init(&zcommit, commit, this->repository TSRMLS_CC);

    RETURN_ZVAL(zcommit,0,1);
}

PHP_METHOD(git_commit, getId)
{
    php_git_commit_t *this = (php_git_commit_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_oid *oid = git_commit_id(this->object);
    char id[GIT_OID_HEXSZ+1] = {0};
    
    git_oid_to_string(id,GIT_OID_HEXSZ+1,oid);
    
    RETURN_STRING(id,1);
}

static zend_function_entry php_git_commit_methods[] = {
    PHP_ME(git_commit, __construct,     arginfo_git_commit__construct,   ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getId,           NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setAuthor,       arginfo_git_commit_set_author,   ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setCommitter,    arginfo_git_commit_set_committer,ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setParents,      arginfo_git_commit_set_parents,  ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setMessage,      arginfo_git_commit_set_message,  ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, setTree,         arginfo_git_commit_set_tree,     ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, write,           NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getTree,         NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getAuthor,       NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getCommitter,    NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getMessage,      NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getShortMessage, NULL,                            ZEND_ACC_PUBLIC)
    PHP_ME(git_commit, getParent,       arginfo_git_commit_get_parent,   ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_commit(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Commit", php_git_commit_methods);
    git_commit_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    git_commit_class_entry->create_object = php_git_commit_new;

    zend_declare_property_null(git_commit_class_entry, "author",   sizeof("author")-1,    ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "committer",sizeof("committer")-1, ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "parents",  sizeof("parents")-1,   ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "message",  sizeof("message")-1,   ZEND_ACC_PROTECTED TSRMLS_CC);
    zend_declare_property_null(git_commit_class_entry, "tree",     sizeof("tree")-1,      ZEND_ACC_PROTECTED TSRMLS_CC);
}
