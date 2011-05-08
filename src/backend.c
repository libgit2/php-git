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

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_backend_read, 0, 0, 1)
    ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_backend_read_header, 0, 0, 1)
    ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_backend_exists, 0, 0, 1)
    ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_backend_write, 0, 0, 1)
    ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()


int php_git_backend__exists(git_odb_backend *backend, const git_oid *oid);
int php_git_backend__write(git_oid *id, git_odb_backend *_backend, const void *buffer, size_t size, git_otype type);
int php_git_backend__read(void **buffer,size_t size, git_otype *type, git_odb_backend *_backend, const git_oid *id);
int php_git_backend__read_header(size_t size, git_otype *type, git_odb_backend *_backend, const git_oid *id);
void php_git_backend__free(git_odb_backend *backend);


static void php_git_backend_free_storage(php_git_backend_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    if(obj->backend) {
        php_git_backend_internal *backend = obj->backend;
        efree(obj->backend);
        obj->backend = NULL;
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

int php_git_backend__exists(git_odb_backend *_backend, const git_oid *oid)
{
    TSRMLS_FETCH();
    php_git_backend_internal *object = (php_git_backend_internal *)_backend;
    char out[GIT_OID_HEXSZ+1] = {0};
    git_oid_to_string(out,GIT_OID_HEXSZ+1,oid);

    zval *retval;
    zval *params[1];
    zval func;
    int result;

    MAKE_STD_ZVAL(retval);
    ZVAL_NULL(retval);
    ZVAL_STRING(&func,"exists", 1);
    MAKE_STD_ZVAL(params[0]);
    ZVAL_STRING(params[0],out, 1);

    if(call_user_function(NULL,&object->self,&func,retval,1,params TSRMLS_CC) == FAILURE){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't call exists method");
        return 0;
    }
    result = Z_BVAL_P(retval);
    zval_ptr_dtor(&retval);
    zval_ptr_dtor(&params[0]);
    zval_dtor(&func);

    if(result){
        return 1;
    }else{
        return 0;
    }
}
int php_git_backend__write(git_oid *id, git_odb_backend *_backend, const void *buffer, size_t size, git_otype type)
{
    TSRMLS_FETCH();
    php_git_backend_internal *object = (php_git_backend_internal *)_backend;
    int ret = 0;
    char out[GIT_OID_HEXSZ+1] = {0};
    zval *retval;
    zval *params[1];
    zval func;
    MAKE_STD_ZVAL(retval);
    ZVAL_NULL(retval);
    ZVAL_STRING(&func,"write", 1);


    MAKE_STD_ZVAL(params[0]);
    object_init_ex(params[0],git_rawobject_class_entry);

    git_oid_to_string(out,GIT_OID_HEXSZ,id);
    
    add_property_stringl_ex(params[0],"data",sizeof("data"),(char *)buffer,size,1 TSRMLS_CC);
    add_property_stringl_ex(params[0],"id",  sizeof("id"),  (char *)out,   GIT_OID_HEXSZ,1 TSRMLS_CC);
    add_property_long(params[0],"type",type);
    add_property_long(params[0],"len",size);

    if(call_user_function(NULL,&object->self,&func,retval,1,params TSRMLS_CC) == FAILURE){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't call write method");
        return GIT_ERROR;
    }
    if (Z_BVAL_P(retval)) {
        ret = GIT_SUCCESS;
    } else {
        ret = GIT_ERROR;
    }
    
    zval_ptr_dtor(&retval);

    // do not free Git\RawObject here.
    //zval_ptr_dtor(&params[0]);
    zval_dtor(&func);

    return ret;
}
int php_git_backend__read(void **buffer,size_t size, git_otype *type, git_odb_backend *_backend, const git_oid *oid)
{
    TSRMLS_FETCH();
    php_git_backend_internal *object = (php_git_backend_internal *)_backend;
    char out[GIT_OID_HEXSZ+1] = {0};
    git_oid_to_string(out,GIT_OID_HEXSZ+1,oid);
    int result = GIT_ERROR;

    zval *retval;
    zval *params[1];
    zval func;

    MAKE_STD_ZVAL(retval);
    ZVAL_NULL(retval);

    ZVAL_STRING(&func,"read", 1);

    MAKE_STD_ZVAL(params[0]);
    ZVAL_STRING(params[0],out, 1);

    if(call_user_function(NULL,&object->self,&func,retval,1,params TSRMLS_CC) == FAILURE){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't call read method");
        result =  GIT_ERROR;
        goto cleanup;
    }

    if(Z_BVAL_P(retval) == false) {
        result =  GIT_ERROR;
        goto cleanup;
    }

    if(!instanceof_function(Z_OBJCE_P(retval), git_rawobject_class_entry TSRMLS_CC)){
        fprintf(stderr,"read interface must return Git\\RawObject");
        result =  GIT_ERROR;
        goto cleanup;
    }

    zval *str = zend_read_property(git_rawobject_class_entry, retval,"data",4, 0 TSRMLS_CC);
    zval *len = zend_read_property(git_rawobject_class_entry, retval,"len",3, 0 TSRMLS_CC);
    zval *tp = zend_read_property(git_rawobject_class_entry, retval,"type",4, 0 TSRMLS_CC);

    buffer = calloc(1,Z_LVAL_P(len));
    memcpy(buffer,Z_STRVAL_P(str),Z_LVAL_P(len));
    type = Z_LVAL_P(tp);
    size = Z_LVAL_P(len);

    result = GIT_SUCCESS;


cleanup:
    zval_ptr_dtor(&retval);
    zval_ptr_dtor(&params[0]);
    zval_dtor(&func);
    return result;
}

int php_git_backend__read_header(size_t size, git_otype *type, git_odb_backend *_backend, const git_oid *oid)
{
    TSRMLS_FETCH();
    php_git_backend_internal *object = (php_git_backend_internal *)_backend;
    char out[GIT_OID_HEXSZ+1] = {0};
    git_oid_to_string(out,GIT_OID_HEXSZ+1,oid);

    zval *retval;
    zval *params[1];
    zval func;

    MAKE_STD_ZVAL(retval);
    ZVAL_NULL(retval);

    ZVAL_STRING(&func,"read", 1);

    MAKE_STD_ZVAL(params[0]);
    ZVAL_STRING(params[0],out, 1);

    if(call_user_function(NULL,&object->self,&func,retval,1,params TSRMLS_CC) == FAILURE){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't call read method");
        return GIT_ERROR;
    }

    if(!instanceof_function(Z_OBJCE_P(retval), git_rawobject_class_entry TSRMLS_CC)){
        fprintf(stderr,"read interface must return Git\\RawObject");
        return GIT_ENOTFOUND;
    }

    zval *len = zend_read_property(git_rawobject_class_entry, retval,"len",3, 0 TSRMLS_CC);
    zval *tp = zend_read_property(git_rawobject_class_entry, retval,"type",4, 0 TSRMLS_CC);

    type = Z_LVAL_P(tp);
    size = Z_LVAL_P(len);
    
    zval_ptr_dtor(&retval);
    zval_ptr_dtor(&params[0]);
    zval_dtor(&func);
    
    return GIT_SUCCESS;
}

void php_git_backend__free(git_odb_backend *backend)
{
    TSRMLS_FETCH();
    php_git_backend_internal *object = (php_git_backend_internal *)backend;

    zval *retval;
    zval func;

    MAKE_STD_ZVAL(retval);
    ZVAL_NULL(retval);

    ZVAL_STRING(&func,"free", 1);

    if(call_user_function(NULL,&object->self,&func,retval,0,NULL TSRMLS_CC) == FAILURE){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't call free method");

        return;
    }

    zval_ptr_dtor(&retval);
    zval_dtor(&func);
}


PHP_METHOD(git_backend, __construct)
{
    php_git_backend_t *this =  (php_git_backend_t *)zend_object_store_get_object(getThis() TSRMLS_CC);
    php_git_backend_internal *internal;

    internal = ecalloc(1,sizeof(php_git_backend_internal));
    internal->parent.read        = &php_git_backend__read;
    internal->parent.read_header = &php_git_backend__read_header;
    internal->parent.write       = &php_git_backend__write;
    internal->parent.exists      = &php_git_backend__exists;
    internal->parent.free        = &php_git_backend__free;
    internal->self = getThis();

    this->backend = internal;
}

PHPAPI function_entry php_git_backend_methods[] = {
    PHP_ME(git_backend, __construct, NULL,    ZEND_ACC_PUBLIC)
    PHP_ABSTRACT_ME(git_backend, read,        arginfo_git_backend_read)
    PHP_ABSTRACT_ME(git_backend, read_header, arginfo_git_backend_read_header)
    PHP_ABSTRACT_ME(git_backend, exists,      arginfo_git_backend_exists)
    PHP_ABSTRACT_ME(git_backend, write,       arginfo_git_backend_write)
    PHP_ABSTRACT_ME(git_backend, free,        NULL)
    {NULL, NULL, NULL}
};

void git_init_backend(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Backend", php_git_backend_methods);
    git_backend_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    git_backend_class_entry->create_object = php_git_backend_new;
}