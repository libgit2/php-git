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
#include "php_git2.h"
#include "php_git2_priv.h"
#include "repository.h"
#include "commit.h"
#include "tree.h"
#include "clone.h"
#include "blob.h"
#include "revwalk.h"
#include "treebuilder.h"
#include "reference.h"

int git2_resource_handle;

void static destruct_git2(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	php_git2_t *resource = (php_git2_t *)rsrc->ptr;
	if (resource->should_free_v) {
		switch (resource->type) {
			case PHP_GIT2_TYPE_REPOSITORY:
				git_repository_free(PHP_GIT2_V(resource, repository));
				break;
			case PHP_GIT2_TYPE_COMMIT:
				git_commit_free(PHP_GIT2_V(resource, commit));
				break;
			case PHP_GIT2_TYPE_TREE:
				git_tree_free(PHP_GIT2_V(resource, tree));
				break;
			case PHP_GIT2_TYPE_TREE_ENTRY:
				git_tree_entry_free(PHP_GIT2_V(resource, tree_entry));
				break;
			case PHP_GIT2_TYPE_BLOB:
				git_blob_free(PHP_GIT2_V(resource, blob));
			case PHP_GIT2_TYPE_REVWALK:
				git_revwalk_free(PHP_GIT2_V(resource, revwalk));
			case PHP_GIT2_TYPE_TREEBUILDER:
				git_treebuilder_free(PHP_GIT2_V(resource, treebuilder));
			case PHP_GIT2_TYPE_REFERENCE:
				git_reference_free(PHP_GIT2_V(resource, reference));
			default:
				break;
		}
	}

	efree(resource);
}

ZEND_DECLARE_MODULE_GLOBALS(git2);

static zend_class_entry *php_git2_get_exception_base(TSRMLS_D)
{
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 2)
	return zend_exception_get_default();
#else
	return zend_exception_get_default(TSRMLS_C);
#endif
}

static zend_function_entry php_git2_functions[] = {
	PHP_FE(git_repository_new, arginfo_git_repository_new)
	PHP_FE(git_repository_init, arginfo_git_repository_init)
	PHP_FE(git_repository_open_bare, arginfo_git_repository_open_bare)
	PHP_FE(git_repository_open, arginfo_git_repository_open)
	PHP_FE(git_repository_get_namespace, arginfo_git_repository_get_namespace)
	PHP_FE(git_repository_workdir, arginfo_git_repository_workdir)

	PHP_FE(git_clone, arginfo_git_clone)

	/* reference */
	PHP_FE(git_reference_lookup, arginfo_git_reference_lookup)
	PHP_FE(git_reference_name_to_id, arginfo_git_reference_name_to_id)
	PHP_FE(git_reference_dwim, arginfo_git_reference_dwim)
	PHP_FE(git_reference_symbolic_create, arginfo_git_reference_symbolic_create)
	PHP_FE(git_reference_create, arginfo_git_reference_create)
	PHP_FE(git_reference_target, arginfo_git_reference_target)
	PHP_FE(git_reference_target_peel, arginfo_git_reference_target_peel)
	PHP_FE(git_reference_symbolic_target, arginfo_git_reference_symbolic_target)
	PHP_FE(git_reference_type, arginfo_git_reference_type)
	PHP_FE(git_reference_name, arginfo_git_reference_name)
	PHP_FE(git_reference_resolve, arginfo_git_reference_resolve)
	PHP_FE(git_reference_owner, arginfo_git_reference_owner)
	PHP_FE(git_reference_symbolic_set_target, arginfo_git_reference_symbolic_set_target)
	PHP_FE(git_reference_set_target, arginfo_git_reference_set_target)
	PHP_FE(git_reference_rename, arginfo_git_reference_rename)
	PHP_FE(git_reference_delete, arginfo_git_reference_delete)
	PHP_FE(git_reference_list, arginfo_git_reference_list)
	PHP_FE(git_reference_foreach, arginfo_git_reference_foreach)
	PHP_FE(git_reference_foreach_name, arginfo_git_reference_foreach_name)
	PHP_FE(git_reference_free, arginfo_git_reference_free)
	PHP_FE(git_reference_cmp, arginfo_git_reference_cmp)
	PHP_FE(git_reference_iterator_new, arginfo_git_reference_iterator_new)
	PHP_FE(git_reference_iterator_glob_new, arginfo_git_reference_iterator_glob_new)
	PHP_FE(git_reference_next, arginfo_git_reference_next)
	PHP_FE(git_reference_next_name, arginfo_git_reference_next_name)
	PHP_FE(git_reference_iterator_free, arginfo_git_reference_iterator_free)
	PHP_FE(git_reference_foreach_glob, arginfo_git_reference_foreach_glob)
	PHP_FE(git_reference_has_log, arginfo_git_reference_has_log)
	PHP_FE(git_reference_is_branch, arginfo_git_reference_is_branch)
	PHP_FE(git_reference_is_remote, arginfo_git_reference_is_remote)
	PHP_FE(git_reference_is_tag, arginfo_git_reference_is_tag)
	PHP_FE(git_reference_normalize_name, arginfo_git_reference_normalize_name)
	PHP_FE(git_reference_peel, arginfo_git_reference_peel)
	PHP_FE(git_reference_is_valid_name, arginfo_git_reference_is_valid_name)
	PHP_FE(git_reference_shorthand, arginfo_git_reference_shorthand)

	/* commit */
	PHP_FE(git_commit_lookup, arginfo_git_commit_lookup)
	PHP_FE(git_commit_author, arginfo_git_commit_author)
	PHP_FE(git_commit_tree, arginfo_git_commit_tree)
	PHP_FE(git_commit_lookup_prefix, arginfo_git_commit_lookup_prefix)
	PHP_FE(git_commit_id, arginfo_git_commit_id)
	PHP_FE(git_commit_owner, arginfo_git_commit_owner)
	PHP_FE(git_commit_message_encoding, arginfo_git_commit_message_encoding)
	PHP_FE(git_commit_message, arginfo_git_commit_message)
	PHP_FE(git_commit_message_raw, arginfo_git_commit_message_raw)
	PHP_FE(git_commit_time, arginfo_git_commit_time)
	PHP_FE(git_commit_time_offset, arginfo_git_commit_time_offset)
	PHP_FE(git_commit_committer, arginfo_git_commit_committer)
	PHP_FE(git_commit_raw_header, arginfo_git_commit_raw_header)
	PHP_FE(git_commit_tree_id, arginfo_git_commit_tree_id)
	PHP_FE(git_commit_parentcount, arginfo_git_commit_parentcount)
	PHP_FE(git_commit_parent, arginfo_git_commit_parent)
	PHP_FE(git_commit_parent_id, arginfo_git_commit_parent_id)
	PHP_FE(git_commit_nth_gen_ancestor, arginfo_git_commit_nth_gen_ancestor)
	PHP_FE(git_commit_create, arginfo_git_commit_create)

	/* tree */
	PHP_FE(git_tree_free, arginfo_git_tree_free)
	PHP_FE(git_tree_id, arginfo_git_tree_id)
	PHP_FE(git_tree_lookup, arginfo_git_tree_lookup)
	PHP_FE(git_tree_owner, arginfo_git_tree_owner)
	PHP_FE(git_tree_walk, arginfo_git_tree_walk)

	PHP_FE(git_tree_entry_byoid, arginfo_git_tree_entry_byoid)
	PHP_FE(git_tree_entry_byindex, arginfo_git_tree_entry_byindex)
	PHP_FE(git_tree_entry_byname, arginfo_git_tree_entry_byname)
	PHP_FE(git_tree_entry_bypath, arginfo_git_tree_entry_bypath)
	PHP_FE(git_tree_entry_id, arginfo_git_tree_entry_id)
	PHP_FE(git_tree_entry_name, arginfo_git_tree_entry_name)
	PHP_FE(git_tree_entry_type, arginfo_git_tree_entry_type)
	PHP_FE(git_tree_entrycount, arginfo_git_tree_entrycount)
	PHP_FE(git_tree_entry_filemode, arginfo_git_tree_entry_filemode)
	PHP_FE(git_tree_entry_filemode_raw, arginfo_git_tree_entry_filemode_raw)
	PHP_FE(git_tree_entry_cmp, arginfo_git_tree_entry_cmp)
	PHP_FE(git_tree_entry_free, arginfo_git_tree_entry_free)
	PHP_FE(git_tree_entry_dup, arginfo_git_tree_entry_dup)

	/* treebuilder */
	PHP_FE(git_treebuilder_create, arginfo_git_treebuilder_create)
	PHP_FE(git_treebuilder_clear, arginfo_git_treebuilder_clear)
	PHP_FE(git_treebuilder_entrycount, arginfo_git_treebuilder_entrycount)
	PHP_FE(git_treebuilder_free, arginfo_git_treebuilder_free)
	PHP_FE(git_treebuilder_get, arginfo_git_treebuilder_get)
	PHP_FE(git_treebuilder_insert, arginfo_git_treebuilder_insert)
	PHP_FE(git_treebuilder_remove, arginfo_git_treebuilder_remove)
	PHP_FE(git_treebuilder_filter, arginfo_git_treebuilder_filter)
	PHP_FE(git_treebuilder_write, arginfo_git_treebuilder_write)

	/* blob */
	PHP_FE(git_blob_create_frombuffer, arginfo_git_blob_create_frombuffer)
	PHP_FE(git_blob_create_fromchunks, arginfo_git_blob_create_fromchunks)
	PHP_FE(git_blob_create_fromdisk, arginfo_git_blob_create_fromdisk)
	PHP_FE(git_blob_create_fromworkdir, arginfo_git_blob_create_fromworkdir)
	PHP_FE(git_blob_filtered_content, arginfo_git_blob_filtered_content)
	PHP_FE(git_blob_free, arginfo_git_blob_free)
	PHP_FE(git_blob_id, arginfo_git_blob_id)
	PHP_FE(git_blob_is_binary, arginfo_git_blob_is_binary)
	PHP_FE(git_blob_lookup, arginfo_git_blob_lookup)
	PHP_FE(git_blob_lookup_prefix, arginfo_git_blob_lookup_prefix)
	PHP_FE(git_blob_owner, arginfo_git_blob_owner)
	PHP_FE(git_blob_rawcontent, arginfo_git_blob_rawcontent)
	PHP_FE(git_blob_rawsize, arginfo_git_blob_rawsize)

	/* revwalk */
	PHP_FE(git_revwalk_new, arginfo_git_revwalk_new)
	PHP_FE(git_revwalk_reset, arginfo_git_revwalk_reset)
	PHP_FE(git_revwalk_push, arginfo_git_revwalk_push)
	PHP_FE(git_revwalk_push_glob, arginfo_git_revwalk_push_glob)
	PHP_FE(git_revwalk_push_head, arginfo_git_revwalk_push_head)
	PHP_FE(git_revwalk_hide, arginfo_git_revwalk_hide)
	PHP_FE(git_revwalk_hide_glob, arginfo_git_revwalk_hide_glob)
	PHP_FE(git_revwalk_hide_head, arginfo_git_revwalk_hide_head)
	PHP_FE(git_revwalk_push_ref, arginfo_git_revwalk_push_ref)
	PHP_FE(git_revwalk_hide_ref, arginfo_git_revwalk_hide_ref)
	PHP_FE(git_revwalk_next, arginfo_git_revwalk_next)
	PHP_FE(git_revwalk_sorting, arginfo_git_revwalk_sorting)
	PHP_FE(git_revwalk_push_range, arginfo_git_revwalk_push_range)
	PHP_FE(git_revwalk_simplify_first_parent, arginfo_git_revwalk_simplify_first_parent)
	PHP_FE(git_revwalk_free, arginfo_git_revwalk_free)
	PHP_FE(git_revwalk_repository, arginfo_git_revwalk_repository)

	PHP_FE_END
};

PHP_MINFO_FUNCTION(git2)
{
	char buf[32] = {0};
	int major, minor, rev;

	php_printf("PHP Git2 Extension\n");

	git_libgit2_version(&major, &minor, &rev);
	snprintf(buf, 32, "%d.%d.%d", major, minor, rev);

	php_info_print_table_start();
	php_info_print_table_header(2, "Git2 Support", "enabled");
	php_info_print_table_end();
}

PHP_INI_BEGIN()
	STD_PHP_INI_BOOLEAN("git2.dummy", "1", PHP_INI_ALL, OnUpdateLong, dummy, zend_git2_globals, git2_globals)
PHP_INI_END()

static PHP_GINIT_FUNCTION(git2)
{
}

static PHP_GSHUTDOWN_FUNCTION(git2)
{
}

PHP_MINIT_FUNCTION(git2)
{
	REGISTER_INI_ENTRIES();

	git2_resource_handle = zend_register_list_destructors_ex(destruct_git2, NULL, PHP_GIT2_RESOURCE_NAME, module_number);
	return SUCCESS;
}

PHP_RINIT_FUNCTION(git2)
{
	git_threads_init();
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(git2)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(git2)
{
	git_threads_shutdown();
	return SUCCESS;
}

zend_module_entry git2_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_GIT2_EXTNAME,
	php_git2_functions,					/* Functions */
	PHP_MINIT(git2),	/* MINIT */
	PHP_MSHUTDOWN(git2),	/* MSHUTDOWN */
	PHP_RINIT(git2),	/* RINIT */
	PHP_RSHUTDOWN(git2),		/* RSHUTDOWN */
	PHP_MINFO(git2),	/* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GIT2_EXTVER,
#endif
	PHP_MODULE_GLOBALS(git2),
	PHP_GINIT(git2),
	PHP_GSHUTDOWN(git2),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_GIT2
ZEND_GET_MODULE(git2)
#endif