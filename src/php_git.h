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


//これ外部に公開したくないんだけどやり方分からんので調べる
typedef struct{
    zend_object zo;
    git_repository *repository;
    git_index *index;
} php_git_index_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
} php_git_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
    git_tree *tree;
} php_git_tree_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
    git_commit *commit;
} php_git_commit_t;

#endif /* PHP_GIT_H */