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

PHPAPI function_entry php_git_blob_methods[] = {
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
    INIT_CLASS_ENTRY(ce, "GitBlob", php_git_blob_methods);
    git_blob_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
}