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
#include <date/php_date.h>
#include <zend_interfaces.h>
#include <string.h>
#include <time.h>


void create_signature_from_commit(zval **signature, git_signature *sig)
{
    char *name;
    MAKE_STD_ZVAL(*signature);
    object_init_ex(*signature,git_signature_class_entry);
    php_git_signature_t *object = (php_git_signature_t *) zend_object_store_get_object(*signature TSRMLS_CC);
    object->signature = sig;
    
    add_property_string(*signature,"name",sig->name,1 TSRMLS_CC);
    add_property_string(*signature,"email",sig->email,1 TSRMLS_CC);
    add_property_long(*signature,"time",sig->when.time);
}


static void php_git_signature_free_storage(php_git_signature_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    
    if(obj->signature){
        // do not free.
        //git_signature_free(obj->signature);
    }
    obj->signature = NULL;
    efree(obj);
}

zend_object_value php_git_signature_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	php_git_signature_t *obj;
	zval *tmp;

	obj = ecalloc(1, sizeof(*obj));
	zend_object_std_init( &obj->zo, ce TSRMLS_CC );
	zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_signature_free_storage,
        NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature__construct, 0, 0, 3)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, email)
    ZEND_ARG_INFO(0, when)
ZEND_END_ARG_INFO()

PHP_METHOD(git_signature, __construct)
{
    zval *this = getThis();
    char *name;
    int name_len = 0;
    char *email;
    int email_len = 0;
    zval *time;
    php_git_signature_t *myobj;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "ssz", &name, &name_len, &email, &email_len, &time) == FAILURE){
        return;
    }

    if(!instanceof_function(Z_OBJCE_P(time), php_date_get_date_ce() TSRMLS_CC)){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Git\\Signature third parameter must be DateTime instance.");
        return;
    }
    myobj = (php_git_signature_t *) zend_object_store_get_object(this TSRMLS_CC);
    //Todo: timeはDateTime型にしたい

	zval *retval;
    zval *offset;
    zval func;
    zval func2;
    ZVAL_STRING(&func,"getTimestamp", 1);

	MAKE_STD_ZVAL(retval);
	ZVAL_NULL(retval);
	MAKE_STD_ZVAL(offset);
	ZVAL_NULL(offset);

    call_user_function(EG(function_table),&time,&func,retval,0,NULL TSRMLS_CC);
    
    ZVAL_STRING(&func2,"getOffset", 1);
    call_user_function(EG(function_table),&time,&func2,offset,0,NULL TSRMLS_CC);

    myobj->signature = git_signature_new(name,email,Z_LVAL_P(retval),Z_LVAL_P(offset)/60);

    add_property_string_ex(this,"name", 5, name, 1 TSRMLS_CC);
    add_property_string_ex(this,"email",6, email, 1 TSRMLS_CC);
    add_property_long(this,"time",Z_LVAL_P(retval));

	zval_ptr_dtor(&retval);
    zval_dtor(&func);
	zval_ptr_dtor(&offset);
    zval_dtor(&func2);
}

// GitSignature
PHPAPI function_entry php_git_signature_methods[] = {
    PHP_ME(git_signature, __construct, arginfo_git_signature__construct, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


void git_init_signature(TSRMLS_D)
{
    zend_class_entry git_signature_ce;
    INIT_NS_CLASS_ENTRY(git_signature_ce, PHP_GIT_NS,"Signature", php_git_signature_methods);

    git_signature_class_entry = zend_register_internal_class(&git_signature_ce TSRMLS_CC);
    git_signature_class_entry->create_object = php_git_signature_new;
}