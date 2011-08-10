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

extern void create_tree_entry_from_entry(zval **object, git_tree_entry *entry,git_repository *repository);

PHPAPI zend_class_entry *git_tree_iterator_class_entry;
extern void php_tree_index_entry_create(zval **index, git_tree_entry *entry);

static void php_git_tree_iterator_free_storage(php_git_tree_iterator_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    obj->tree = NULL;
    efree(obj);
}

zend_object_value php_git_tree_iterator_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_tree_iterator_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_tree_iterator_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_iterator__construct, 0, 0, 1)
  ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

PHP_METHOD(git_tree_iterator, current)
{
    php_git_tree_iterator_t *this = (php_git_tree_iterator_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_tree_entry *entry;
    zval *git_tree_entry;
    
    entry = git_tree_entry_byindex(this->tree,this->offset);
    if(entry == NULL){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "specified offset does not exist. %d");
        RETURN_FALSE;
    }
    create_tree_entry_from_entry(&git_tree_entry,entry,this->repository);
    RETURN_ZVAL(git_tree_entry,0,1);
}

PHP_METHOD(git_tree_iterator, key)
{
    php_git_tree_iterator_t *this = (php_git_tree_iterator_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    RETURN_LONG(this->offset);
}

PHP_METHOD(git_tree_iterator, next)
{
    php_git_tree_iterator_t *this = (php_git_tree_iterator_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    this->offset++;

    RETURN_TRUE;
}

PHP_METHOD(git_tree_iterator, rewind)
{
    php_git_tree_iterator_t *this = (php_git_tree_iterator_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    this->offset = 0;
}

PHP_METHOD(git_tree_iterator, valid)
{
    php_git_tree_iterator_t *this = (php_git_tree_iterator_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int entry_count = git_tree_entrycount(this->tree);

    if(this->offset < entry_count && this->offset >= 0){
        RETURN_TRUE;
    }else{
        RETURN_FALSE;
    }
}

PHP_METHOD(git_tree_iterator, __construct)
{
    php_git_tree_iterator_t *this = (php_git_tree_iterator_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *php_tree_index;
    php_git_tree_t *tree;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &php_tree_index) == FAILURE){
        return;
    }
    tree = (php_git_tree_t *) zend_object_store_get_object(php_tree_index TSRMLS_CC);

    this->tree = tree->object;
    this->offset = 0;
}


static zend_function_entry php_git_tree_iterator_methods[] = {
    PHP_ME(git_tree_iterator, __construct, arginfo_git_tree_iterator__construct,ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_iterator, current,     NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_iterator, key,         NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_iterator, next,        NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_iterator, rewind,      NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_tree_iterator, valid,       NULL,                        ZEND_ACC_PUBLIC)
    {NULL,NULL,NULL}
};

void git_tree_iterator_init(TSRMLS_D)
{
    zend_class_entry git_tree_iterator_ce;
    INIT_NS_CLASS_ENTRY(git_tree_iterator_ce, PHP_GIT_NS,"TreeIterator", php_git_tree_iterator_methods);
    git_tree_iterator_class_entry  = zend_register_internal_class(&git_tree_iterator_ce TSRMLS_CC);
    git_tree_iterator_class_entry->create_object = php_git_tree_iterator_new;
    zend_class_implements(git_tree_iterator_class_entry TSRMLS_CC, 1, spl_ce_Iterator);
}
