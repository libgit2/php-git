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

static void php_git_tree_entry_free_storage(php_git_tree_entry_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    obj->entry = NULL;
    efree(obj);
}

zend_object_value php_git_tree_entry_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_tree_entry_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_tree_entry_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_set_id, 0, 0, 1)
    ZEND_ARG_INFO(0, hash)
ZEND_END_ARG_INFO()

PHP_METHOD(git_tree_entry, setId)
{
    php_git_tree_entry_t *this = (php_git_tree_entry_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *hash;
    int hash_len = 0;
    git_oid oid;
    
    int ret = 0;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &hash, &hash_len) == FAILURE){
        return;
    }
    git_oid_mkstr(&oid,hash);
    git_tree_entry_set_id(this->entry,&oid);

    char out[40];
    git_oid_to_string(&out,41,git_tree_entry_id(this->entry));
    printf(">oid<: %s\n",out);
    
    add_property_string(getThis(), "oid", hash, 1 TSRMLS_C);
    
    RETVAL_STRING(hash, 1);
}


PHPAPI function_entry php_git_tree_entry_methods[] = {
    PHP_ME(git_tree_entry, setId, arginfo_git_tree_entry_set_id, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_tree_entry(TSRMLS_D)
{
    zend_class_entry git_tree_entry_ce;
    INIT_CLASS_ENTRY(git_tree_entry_ce, "GitTreeEntry", php_git_tree_entry_methods);
    git_tree_entry_class_entry = zend_register_internal_class(&git_tree_entry_ce TSRMLS_CC);
	git_tree_entry_class_entry->create_object = php_git_tree_entry_new;
}