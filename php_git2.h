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
#define PHP_GIT2_EXTVER "0.3.0"

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
#include "git2/odb.h"
#include "git2/odb_backend.h"
#include "git2/trace.h"
#include "git2/sys/filter.h"
#include "git2/sys/odb_backend.h"

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


#ifdef ZTS
#define GIT2_TSRMLS_SET(target) void ***tsrm_ls = target;
#define GIT2_TSRMLS_DECL void ***tsrm_ls;
#define GIT2_TSRMLS_SET2(target, value) target->tsrm_ls = value;
#else
#define GIT2_TSRMLS_SET(target)
#define GIT2_TSRMLS_SET2(target, value)
#define GIT2_TSRMLS_DECL
#endif

enum php_git2_resource_type {
	PHP_GIT2_TYPE_REPOSITORY,
	PHP_GIT2_TYPE_COMMIT,
	PHP_GIT2_TYPE_TREE,
	PHP_GIT2_TYPE_TREE_ENTRY,
	PHP_GIT2_TYPE_BLOB,
	PHP_GIT2_TYPE_REVWALK,
	PHP_GIT2_TYPE_TREEBUILDER,
	PHP_GIT2_TYPE_REFERENCE,
	PHP_GIT2_TYPE_REFERENCE_ITERATOR,
	PHP_GIT2_TYPE_CONFIG,
	PHP_GIT2_TYPE_CONFIG_ITERATOR,
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
	PHP_GIT2_TYPE_DIFF,
	PHP_GIT2_TYPE_MERGE_RESULT,
	PHP_GIT2_TYPE_MERGE_HEAD,
	PHP_GIT2_TYPE_PATHSPEC,
	PHP_GIT2_TYPE_PATHSPEC_MATCH_LIST,
	PHP_GIT2_TYPE_PATCH,
	PHP_GIT2_TYPE_DIFF_HUNK,
	PHP_GIT2_TYPE_BUF,
	PHP_GIT2_TYPE_FILTER_LIST,
	PHP_GIT2_TYPE_FILTER_SOURCE,
	PHP_GIT2_TYPE_DIFF_LINE,
	PHP_GIT2_TYPE_INDEX_CONFLICT_ITERATOR,
	PHP_GIT2_TYPE_SMART_SUBTRANSPORT,
	PHP_GIT2_TYPE_NOTE,
	PHP_GIT2_TYPE_NOTE_ITERATOR,
	PHP_GIT2_TYPE_ODB_STREAM,
	PHP_GIT2_TYPE_ODB_OBJECT,
	PHP_GIT2_TYPE_ODB_WRITEPACK,
	PHP_GIT2_TYPE_ODB_BACKEND,
	PHP_GIT2_TYPE_REFLOG,
	PHP_GIT2_TYPE_REFLOG_ENTRY,
	PHP_GIT2_TYPE_BLAME,
	PHP_GIT2_TYPE_PACKBUILDER,
	PHP_GIT2_TYPE_SUBMODULE,
	PHP_GIT2_TYPE_PUSH,
	PHP_GIT2_TYPE_REFSPEC,
	PHP_GIT2_TYPE_INDEXER,
	PHP_GIT2_TYPE_FILTER, /* for conventional reason */
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
		git_reference_iterator *reference_iterator;
		git_config *config;
		git_config_iterator *config_iterator;
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
		git_diff *diff;
		git_merge_result *merge_result;
		git_merge_head *merge_head;
		git_pathspec *pathspec;
		git_pathspec_match_list *pathspec_match_list;
		git_patch *patch;
		git_diff_hunk *diff_hunk;
		git_buf *buf;
		git_filter_list *filter_list;
		git_filter_source *filter_source;
		git_diff_line *diff_line;
		git_index_conflict_iterator *index_conflict_iterator;
		git_smart_subtransport *smart_subtransport;
		git_note *note;
		git_note_iterator *note_iterator;
		git_odb_stream *odb_stream;
		git_odb_object *odb_object;
		git_odb_writepack *odb_writepack;
		git_odb_backend *odb_backend;
		git_reflog *reflog;
		git_reflog_entry *reflog_entry;
		git_blame *blame;
		git_packbuilder *packbuilder;
		git_submodule *submodule;
		git_push *push;
		git_refspec *refspec;
		git_indexer *indexer;
		git_filter *filter;
	} v;
	int should_free_v;
	int resource_id;
	int mutable;
} php_git2_t;

typedef struct php_git2_cb_t {
	zval *payload;
	zend_fcall_info *fci;
	zend_fcall_info_cache *fcc;
	int is_copy;
	GIT2_TSRMLS_DECL
} php_git2_cb_t;

typedef struct php_git2_fcall_t {
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
	zval *value;
} php_git2_fcall_t;

typedef struct php_git2_multi_cb_t {
	int num_callbacks;
	php_git2_fcall_t *callbacks;
	zval *payload;
	GIT2_TSRMLS_DECL
} php_git2_multi_cb_t;

typedef struct php_git2_filter {
	git_filter super;
	php_git2_multi_cb_t *multi;
} php_git2_filter;

typedef struct php_git2_odb_backend {
	git_odb_backend parent;
	php_git2_multi_cb_t *multi;
} php_git2_odb_backend;

typedef struct php_git2_odb_backend_foreach_callback {
	zend_object zo;
	git_odb_foreach_cb callback;
	php_git2_cb_t *payload;
} php_git2_odb_backend_foreach_callback;

extern zend_class_entry *php_git2_odb_backend_foreach_callback_class_entry;

#endif /* PHP_GIT2_H */
