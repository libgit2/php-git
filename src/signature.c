/*
 * The MIT License
 *
 * Copyright (c) 2010 Shuhei Tanuma
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


//GitSignature
ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature__construct, 0, 0, 3)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, email)
    ZEND_ARG_INFO(0, when)
ZEND_END_ARG_INFO()

PHP_METHOD(git_signature, __construct)
{
    char *name;
    int name_len = 0;
    char *email;
    int email_len = 0;
    int time = 0;
    
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
	    "ssl", &name, &name_len, &email, &email_len, &time) == FAILURE){
		return;
	}

	add_property_string_ex(getThis(),"name", 5, name, 1 TSRMLS_CC);
	add_property_string_ex(getThis(),"email",6, email, 1 TSRMLS_CC);
	add_property_long(getThis(),"time",time);
}

// GitSignature
PHPAPI function_entry php_git_signature_methods[] = {
    PHP_ME(git_signature, __construct, arginfo_git_signature__construct, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


void git_init_signature(TSRMLS_D)
{
    zend_class_entry git_signature_ce;
    INIT_CLASS_ENTRY(git_signature_ce, "GitSignature", php_git_signature_methods);
    git_signature_class_entry = zend_register_internal_class(&git_signature_ce TSRMLS_CC);
}