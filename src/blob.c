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

static void php_git_blob_free_storage(php_git_blob_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    //git_repositoryがfreeしてくれる
    obj->object = NULL;
    efree(obj);
}

zend_object_value php_git_blob_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_repository_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_blob_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();

	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()
    
ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_set_content, 0, 0, 1)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO()


PHP_METHOD(git_blob, __construct)
{
    zval *z_repository;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_repository) == FAILURE){
        return;
    }

    php_git_repository_t *git = (php_git_repository_t *) zend_object_store_get_object(z_repository TSRMLS_CC);
    php_git_blob_t *obj = (php_git_blob_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    
    int ret = git_blob_new(&obj->object,git->repository);

    if(ret != GIT_SUCCESS){
        php_printf("can't create new blob");
    }
}


PHP_METHOD(git_blob, setContent)
{
    char *string;
    size_t string_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &string, &string_len) == FAILURE){
        return;
    }

    php_git_blob_t *obj = (php_git_blob_t *) zend_object_store_get_object(getThis() TSRMLS_CC);

    int ret = git_blob_set_rawcontent(obj->object,string, string_len);
    if(ret != GIT_SUCCESS){
        php_printf("can't create new blob");
    }
    add_property_string_ex(getThis(), "data",sizeof("data")+1,string, 1 TSRMLS_CC);
}





PHPAPI function_entry php_git_blob_methods[] = {
    PHP_ME(git_blob, __construct, arginfo_git_blob__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_blob, setContent, arginfo_git_blob_set_content, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_blob(TSRMLS_D)
{
/*
    struct git_object {
	git_oid id;
	git_repository *repo;
	git_odb_source source;
	int in_memory:1, modified:1;
};
*/
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Blob", php_git_blob_methods);

    git_blob_class_entry = zend_register_internal_class_ex(&ce, git_object_class_entry, NULL TSRMLS_CC);
	git_blob_class_entry->create_object = php_git_blob_new;

}