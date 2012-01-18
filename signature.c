/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2012 Shuhei Tanuma
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

#include "php_git2.h"
#include <date/php_date.h>
#include <time.h>

PHPAPI zend_class_entry *git2_signature_class_entry;

static void php_git2_signature_free_storage(php_git2_signature *object TSRMLS_DC)
{
	if (object->signature != NULL) {
		git_signature_free(object->signature);
		object->signature = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_signature_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_signature);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_signature___construct, 0,0,3)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, email)
	ZEND_ARG_INFO(0, date)
ZEND_END_ARG_INFO()

void php_git2_create_signature(zval *object, char *name, int name_len, char *email, int email_len, zval *date TSRMLS_DC)
{
	zval *z_name, *z_email = NULL;
	
	MAKE_STD_ZVAL(z_name);
	MAKE_STD_ZVAL(z_email);
	ZVAL_STRINGL(z_name,name,name_len,1);
	ZVAL_STRINGL(z_email,email,email_len,1);

	add_property_zval_ex(object, "name", sizeof("name") ,z_name TSRMLS_CC);
	add_property_zval_ex(object, "email",sizeof("email"),z_email TSRMLS_CC);
	add_property_zval_ex(object, "time", sizeof("time") ,date TSRMLS_CC);

	zval_ptr_dtor(&z_email);
	zval_ptr_dtor(&z_name);
}

/*
{{{ proto: Git2\Signature::__construct(string $name, string $email, \DateTime $time)
*/
PHP_METHOD(git2_signature, __construct)
{
	char *name, *email;
	int error, name_len, email_len = 0;
	zval *date = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ssz", &name, &name_len, &email, &email_len, &date) == FAILURE) {
		return;
	}
	
	if (!instanceof_function(Z_OBJCE_P(date), php_date_get_date_ce() TSRMLS_CC)) {
		RETURN_FALSE;
	}
	
	//@memo
	//error = php_git2_call_user_function_v(&timestamp, date, "getTimeStamp", sizeof("getTimeStamp")-1, 0);
	//zval_ptr_dtor(&timestamp);
	php_git2_create_signature(getThis(), name, name_len, email, email_len, date TSRMLS_CC);
}
/* }}} */



static zend_function_entry php_git2_signature_methods[] = {
	PHP_ME(git2_signature, __construct, arginfo_git2_signature___construct, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_signature_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Signature", php_git2_signature_methods);
	git2_signature_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_signature_class_entry->create_object = php_git2_signature_new;
	zend_declare_property_null(git2_signature_class_entry, "name", sizeof("name")-1,  ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(git2_signature_class_entry, "email", sizeof("email")-1,  ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_null(git2_signature_class_entry, "time", sizeof("time")-1,  ZEND_ACC_PUBLIC TSRMLS_CC);
}