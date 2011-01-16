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
#include <git2/odb_backend.h>

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry git_module_entry;
#define phpext_git_ptr &git_module_entry;
#define PHP_GIT_NS "Git"

PHPAPI zend_class_entry *git_class_entry;
PHPAPI zend_class_entry *git_repository_class_entry;
PHPAPI zend_class_entry *git_object_class_entry;
PHPAPI zend_class_entry *git_index_class_entry;
PHPAPI zend_class_entry *git_walker_class_entry;
PHPAPI zend_class_entry *git_tree_class_entry;
PHPAPI zend_class_entry *git_tree_entry_class_entry;
PHPAPI zend_class_entry *git_commit_class_entry;
PHPAPI zend_class_entry *git_signature_class_entry;
PHPAPI zend_class_entry *git_rawobject_class_entry;
PHPAPI zend_class_entry *git_tag_class_entry;
PHPAPI zend_class_entry *git_blob_class_entry;
PHPAPI zend_class_entry *git_odb_class_entry;
PHPAPI zend_class_entry *git_backend_class_entry;


//これ外部に公開したくないんだけどやり方分からんので調べる
typedef struct{
    zend_object zo;
    git_repository *repository;
    git_index *index;
} php_git_index_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
} php_git_repository_t;


typedef struct{
    zend_object zo;
    git_tree_entry *entry;
} php_git_tree_entry_t;


typedef struct{
    zend_object zo;
    git_repository *repository;
    git_revwalk *walker;
} php_git_walker_t;

typedef struct{
    git_odb_backend parent;
    zval *self;
} php_git_backend_internal;

typedef struct{
    zend_object zo;
    php_git_backend_internal *backend;
} php_git_backend_t;

typedef struct{
    zend_object zo;
    git_signature *signature;
} php_git_signature_t;

typedef struct{
    zend_object zo;
    git_odb *odb;
} php_git_odb_t;


typedef struct{
    zend_object zo;
    git_rawobj *object;
} php_git_rawobject_t;

typedef struct{
    zend_object zo;
    git_object *object;
} php_git_object_t;

// extends git_object
typedef struct{
    zend_object zo;
    git_commit *object;
    git_repository *repository;
} php_git_commit_t;

typedef struct{
    zend_object zo;
    git_tree *object;
} php_git_tree_t;

typedef struct{
    zend_object zo;
    git_tag *object;
} php_git_tag_t;


typedef struct{
    zend_object zo;
    git_blob *object;
} php_git_blob_t;


#endif /* PHP_GIT_H */