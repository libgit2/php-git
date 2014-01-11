/*
 * PHP Libgit2 Extension
 *
 * https://github.com/libgit2/php-git
 *
 * Copyright 2014 Shuhei Tanuma.  All rights reserved.
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
#ifndef PHP_GIT2_H
#define PHP_GIT2_H

#define PHP_GIT2_EXTNAME "git2"
#define PHP_GIT2_EXTVER "0.2.0"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "zend.h"
#include "zend_interfaces.h"
#include "zend_exceptions.h"
#include "ext/standard/php_smart_str.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/standard/php_var.h"
#include "ext/standard/php_string.h"
#include "ext/standard/php_incomplete_class.h"
#include "ext/standard/info.h"
#include "ext/standard/php_array.h"
#include "limits.h"

#include "git2.h"

#include "date/php_date.h"

#include <stdlib.h>

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry git2_module_entry;
#define phpext_git2_ptr &git2_module_entry

ZEND_BEGIN_MODULE_GLOBALS(git2)
	long dummy;
ZEND_END_MODULE_GLOBALS(git2)

ZEND_EXTERN_MODULE_GLOBALS(git2)

#ifdef ZTS
#define GIT2G(v) TSRMG(git2_globals_id, zend_git2_globals *, v)
#else
#define GIT2G(v) (git2_globals.v)
#endif

#define PHP_GIT2_RESOURCE_NAME "git2"

enum php_git2_resource_type {
	PHP_GIT2_TYPE_REPOSITORY,
	PHP_GIT2_TYPE_COMMIT,
	PHP_GIT2_TYPE_TREE,
	PHP_GIT2_TYPE_TREE_ENTRY,
	PHP_GIT2_TYPE_BLOB,
	PHP_GIT2_TYPE_REVWALK,
	PHP_GIT2_TYPE_TREEBUILDER,
	PHP_GIT2_TYPE_REFERENCE,
	PHP_GIT2_TYPE_CONFIG,
	PHP_GIT2_TYPE_OBJECT,
	PHP_GIT2_TYPE_INDEX,
	PHP_GIT2_TYPE_ODB,
	PHP_GIT2_TYPE_REFDB,
	PHP_GIT2_TYPE_STATUS_LIST,
	PHP_GIT2_TYPE_BRANCH_ITERATOR,
	PHP_GIT2_TYPE_TAG,
	PHP_GIT2_TYPE_CRED,
	PHP_GIT2_TYPE_TRANSPORT,
	PHP_GIT2_TYPE_REMOTE,
};

typedef struct php_git2_t {
	enum php_git2_resource_type type;
	union {
		git_repository *repository;
		git_commit *commit;
		git_tree *tree;
		git_tree_entry *tree_entry;
		git_blob *blob;
		git_revwalk *revwalk;
		git_treebuilder *treebuilder;
		git_reference *reference;
		git_config *config;
		git_object *object;
		git_index *index;
		git_odb *odb;
		git_refdb *refdb;
		git_status_list *status_list;
		git_branch_iterator *branch_iterator;
		git_tag *tag;
		git_cred *cred;
		git_transport *transport;
		git_remote *remote;
	} v;
	int should_free_v;
	int resource_id;
	int mutable;
} php_git2_t;

#endif /* PHP_GIT2_H */