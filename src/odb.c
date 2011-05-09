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

PHPAPI zend_class_entry *git_odb_class_entry;

int php_git_odb_add_backend(git_odb **odb, zval *backend, int priority);
int php_git_odb_add_alternate(git_odb **odb, zval *backend, int priority);


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_add_backend,0, 0, 1)
    ZEND_ARG_INFO(0, backend)
ZEND_END_ARG_INFO()

static void php_git_odb_free_storage(php_git_odb_t *obj TSRMLS_DC)
{
    if(obj->odb != NULL){
        obj->odb = NULL;
    }
    zend_object_std_dtor(&obj->zo TSRMLS_CC);

    efree(obj);
}

zend_object_value php_git_odb_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_odb_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_odb_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

PHP_METHOD(git_odb, __construct)
{
    php_git_odb_t *this = (php_git_odb_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_odb *odb;
    int ret = 0;
    ret = git_odb_new(&this->odb);
    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"can't create Git\\ODB");
    }
}


int php_git_odb_add_alternate(git_odb **odb, zval *backend, int priority)
{
    TSRMLS_FETCH();
    int ret = GIT_SUCCESS;
    php_git_backend_t *b;
    if(!instanceof_function(Z_OBJCE_P(backend), git_backend_class_entry TSRMLS_CC)){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"alternate must extends Git\\Backend");
        return GIT_ERROR;
    }

    b = (php_git_backend_t *) zend_object_store_get_object(backend TSRMLS_CC);
    ret = git_odb_add_alternate(*odb,(git_odb_backend *)b->backend, priority);

    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC,"can't add alternate");
        return GIT_ERROR;
    }
    
    return ret;
}


int php_git_odb_add_backend(git_odb **odb, zval *backend, int priority)
{
    TSRMLS_FETCH();
    int ret = GIT_SUCCESS;
    php_git_backend_t *b;
    if(!instanceof_function(Z_OBJCE_P(backend), git_backend_class_entry TSRMLS_CC)){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,"backend must extends Git\\Backend");
        return GIT_ERROR;
    }

    b = (php_git_backend_t *) zend_object_store_get_object(backend TSRMLS_CC);
    ret = git_odb_add_backend(*odb,(git_odb_backend *)b->backend, priority);

    if(ret != GIT_SUCCESS){
        php_error_docref(NULL TSRMLS_CC, E_WARNING,"can't add backend");
        return GIT_ERROR;
    }

    Z_ADDREF_P(backend);
    return ret;
}

PHP_METHOD(git_odb, addBackend)
{
    php_git_odb_t *this = (php_git_odb_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *backend;
    int priority = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &backend, &priority) == FAILURE){
        return;
    }
    
    php_git_odb_add_backend(&this->odb,backend, priority);
}

PHP_METHOD(git_odb, addAlternate)
{
    php_git_odb_t *this = (php_git_odb_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *backend;
    int priority = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &backend, &priority) == FAILURE){
        return;
    }
    
    php_git_odb_add_alternate(&this->odb,backend, priority);
}


PHPAPI function_entry php_git_odb_methods[] = {
    PHP_ME(git_odb, __construct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_odb, addBackend, arginfo_git_odb_add_backend, ZEND_ACC_PUBLIC)
    PHP_ME(git_odb, addAlternate, arginfo_git_odb_add_backend, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_odb(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"ODB", php_git_odb_methods);
    git_odb_class_entry = zend_register_internal_class_ex(&ce, git_odb_class_entry,NULL TSRMLS_CC);
    git_odb_class_entry->create_object = php_git_odb_new;
}