/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2010-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Shuhei Tanuma <stanuma@zynga.co.jp>                          |
  +----------------------------------------------------------------------+
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