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

// GitTree
PHPAPI function_entry php_git_tree_entry_methods[] = {
    {NULL, NULL, NULL}
};

void git_init_tree_entry(TSRMLS_D)
{
    zend_class_entry git_tree_entry_ce;
    INIT_CLASS_ENTRY(git_tree_entry_ce, "GitTreeEntry", php_git_tree_entry_methods);
    git_tree_entry_class_entry = zend_register_internal_class(&git_tree_entry_ce TSRMLS_CC);
}