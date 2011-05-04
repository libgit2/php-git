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

PHPAPI zend_class_entry *git_backend_class_entry;

static void php_git_backend_free_storage(php_git_backend_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    if(obj->backend) {
        php_git_backend_internal *backend = obj->backend;
    }
    efree(obj);
}


zend_object_value php_git_backend_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_backend_t *backend;
    zval *tmp;

    backend = ecalloc(1, sizeof(php_git_backend_t));
    zend_object_std_init( &backend->zo, ce TSRMLS_CC );

    zend_hash_copy(backend->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(backend, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_backend_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();

    return retval;
}

PHPAPI function_entry php_git_backend_methods[] = {
    {NULL, NULL, NULL}
};

void git_init_backend(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Backend", php_git_backend_methods);
    git_backend_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    git_backend_class_entry->create_object = php_git_backend_new;
}