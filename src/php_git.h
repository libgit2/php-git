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

#ifndef PHP_GIT_H

#define PHP_GIT_H

#define PHP_GIT_EXTNAME "git"
#define PHP_GIT_EXTVER "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include <git2.h>

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry git_module_entry;
#define phpext_git_ptr &git_module_entry;

#define REGISTER_GIT_CONST_LONG(const_name, value) { \
    zend_class_entry **git_class_entry;	\
    if (zend_hash_find(CG(class_table), "git", sizeof("git"), (void **) &git_class_entry) != FAILURE)	\
        zend_declare_class_constant_long(*git_class_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);	\
}	\

PHPAPI zend_class_entry *git_class_entry;
PHPAPI zend_class_entry *git_index_class_entry;
PHPAPI zend_class_entry *git_walker_class_entry;
PHPAPI zend_class_entry *git_tree_class_entry;
PHPAPI zend_class_entry *git_tree_entry_class_entry;
PHPAPI zend_class_entry *git_commit_class_entry;
PHPAPI zend_class_entry *git_signature_class_entry;
PHPAPI zend_class_entry *git_rawobject_class_entry;
PHPAPI zend_class_entry *git_tag_class_entry;
PHPAPI zend_class_entry *git_object_class_entry;
PHPAPI zend_class_entry *git_blob_class_entry;

#endif /* PHP_GIT_H */