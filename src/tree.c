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

PHPAPI zend_class_entry *git_tree_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_add, 0, 0, 3)
    ZEND_ARG_INFO(0, hash)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_path, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

static void php_git_tree_free_storage(php_git_tree_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    //Todo: which engine shoud free (php / libgit2)
    obj->object = NULL;
    efree(obj);
}

zend_object_value php_git_tree_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_tree_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_tree_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

PHP_METHOD(git_tree, count)
{
    php_git_tree_t *this= (php_git_tree_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    RETVAL_LONG(git_tree_entrycount(this->object));
}


PHP_METHOD(git_tree, path)
{
    //TODO
    php_git_tree_t *this= (php_git_tree_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *path;
    int path_len= 0;
    git_tree_entry *entry;
    int ret = 0;
    git_object *object;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &path, &path_len) == FAILURE){
        return;
    }
    entry = git_tree_entry_byname(this->object,path);

    if(entry == NULL){
        return;
    }else{
        ret = git_tree_entry_2object(&object, entry);

        if (ret != GIT_SUCCESS) {
            zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"something uncaught error happend.");
            RETURN_FALSE;
        }
        git_otype type = git_object_type(object);

        if(type == GIT_OBJ_TREE) {
            // Todo: refactoring below block
            git_tree *tree = (git_tree*)object;
            git_oid *tree_oid;
            zval *git_tree;
            zval *entries;
            zval *entry;

            MAKE_STD_ZVAL(git_tree);
            MAKE_STD_ZVAL(entries);
            array_init(entries);
            object_init_ex(git_tree, git_tree_class_entry);
            php_git_tree_t *tobj = (php_git_tree_t *) zend_object_store_get_object(git_tree TSRMLS_CC);
            tobj->object = tree;
            int r = git_tree_entrycount(tree);
            int i = 0;
            for(i; i < r; i++){
                create_tree_entry_from_entry(&entry,git_tree_entry_byindex(tree,i));
                add_next_index_zval(entries, entry);
            }
            add_property_zval(git_tree,"entries", entries);
            RETURN_ZVAL(git_tree,0,0);

        }else if(type == GIT_OBJ_BLOB){
            // Todo: refactoring below block
            zval *git_object;
            MAKE_STD_ZVAL(git_object);
            object_init_ex(git_object, git_blob_class_entry);
            php_git_blob_t *blobobj = (php_git_blob_t *) zend_object_store_get_object(git_object TSRMLS_CC);
            blobobj->object = (git_blob *)object;

            add_property_stringl_ex(git_object,"data", sizeof("data"), (char *)git_blob_rawcontent((git_blob *)object),git_blob_rawsize((git_blob *)object), 1 TSRMLS_CC);
            RETURN_ZVAL(git_object,0,0);
        } else {
            zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,
                            "Git\\Tree::path can resolve GIT_OBJ_TREE or GIT_OBJ_BLOB. unhandled object type %d found.", git_object_type(object));
            RETURN_FALSE;
        }
    }
}

PHP_METHOD(git_tree, add)
{
    zval *object = getThis();
    git_tree_entry *entry;
    char *filename;
    char *entry_oid;
    int entry_oid_len;
    int filename_len = 0;
    int attr = 0;

    git_oid oid;
    git_tree *tree;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "ssl", &entry_oid, &entry_oid_len,&filename,&filename_len,&attr) == FAILURE){
        return;
    }

    git_oid_mkstr(&oid, entry_oid);
    php_git_tree_t *myobj = (php_git_tree_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int ret = git_tree_add_entry(&entry, myobj->object, &oid, filename, attr);
    if(ret != GIT_SUCCESS) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "can't add tree entry");
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(git_tree, __construct)
{
    zval *z_repository;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }

    php_git_repository_t *git = (php_git_repository_t *) zend_object_store_get_object(z_repository TSRMLS_CC);
    php_git_tree_t *obj = (php_git_tree_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    
    int ret = git_tree_new(&obj->object,git->repository);

    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "can't create new tree");
        RETURN_FALSE;
    }
}

PHPAPI function_entry php_git_tree_methods[] = {
    PHP_ME(git_tree, __construct, arginfo_git_tree__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_tree, count,       NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_tree, path,        arginfo_git_tree_path,       ZEND_ACC_PUBLIC)
    PHP_ME(git_tree, add,         arginfo_git_tree_add,        ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_tree(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Tree", php_git_tree_methods);
    git_tree_class_entry = zend_register_internal_class_ex(&ce, git_object_class_entry, NULL TSRMLS_CC);
    git_tree_class_entry->create_object = php_git_tree_new;
    
    zend_class_implements(git_tree_class_entry TSRMLS_CC, 1, spl_ce_Countable);
}