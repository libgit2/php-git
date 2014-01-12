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
#include "g_config.h"
#include "object.h"
#include "index.h"
#include "revparse.h"
#include "branch.h"
#include "tag.h"
#include "status.h"
#include "cred.h"
#include "remote.h"
#include "transport.h"
#include "diff.h"
#include "checkout.h"
#include "filter.h"
#include "ignore.h"
#include "indexer.h"
#include "pathspec.h"
#include "patch.h"
#include "merge.h"

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
			case PHP_GIT2_TYPE_CONFIG:
				git_config_free(PHP_GIT2_V(resource, config));
			case PHP_GIT2_TYPE_OBJECT:
				git_object_free(PHP_GIT2_V(resource, object));
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_resource_type, 0, 0, 1)
	ZEND_ARG_INFO(0, resource)
ZEND_END_ARG_INFO()

/* {{{ proto long git_resource_type(resource $git)
 */
PHP_FUNCTION(git_resource_type)
{
	int result = 0;
	zval *resource = NULL;
	php_git2_t *_resource= NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &resource) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_resource, php_git2_t*, &resource, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	RETURN_LONG(_resource->type);
}
/* }}} */

static zend_function_entry php_git2_functions[] = {
	/* repository */
	PHP_FE(git_repository_new, arginfo_git_repository_new)
	PHP_FE(git_repository_init, arginfo_git_repository_init)
	PHP_FE(git_repository_open_bare, arginfo_git_repository_open_bare)
	PHP_FE(git_repository_open, arginfo_git_repository_open)
	PHP_FE(git_repository_get_namespace, arginfo_git_repository_get_namespace)
	PHP_FE(git_repository_workdir, arginfo_git_repository_workdir)
	PHP_FE(git_repository_wrap_odb, arginfo_git_repository_wrap_odb)
	PHP_FE(git_repository_discover, arginfo_git_repository_discover)
	PHP_FE(git_repository_open_ext, arginfo_git_repository_open_ext)
	PHP_FE(git_repository_free, arginfo_git_repository_free)
	PHP_FE(git_repository_init_ext, arginfo_git_repository_init_ext)
	PHP_FE(git_repository_head, arginfo_git_repository_head)
	PHP_FE(git_repository_head_detached, arginfo_git_repository_head_detached)
	PHP_FE(git_repository_head_unborn, arginfo_git_repository_head_unborn)
	PHP_FE(git_repository_is_empty, arginfo_git_repository_is_empty)
	PHP_FE(git_repository_path, arginfo_git_repository_path)
	PHP_FE(git_repository_set_workdir, arginfo_git_repository_set_workdir)
	PHP_FE(git_repository_is_bare, arginfo_git_repository_is_bare)
	PHP_FE(git_repository_config, arginfo_git_repository_config)
	PHP_FE(git_repository_odb, arginfo_git_repository_odb)
	PHP_FE(git_repository_refdb, arginfo_git_repository_refdb)
	PHP_FE(git_repository_index, arginfo_git_repository_index)
	PHP_FE(git_repository_message, arginfo_git_repository_message)
	PHP_FE(git_repository_message_remove, arginfo_git_repository_message_remove)
	PHP_FE(git_repository_merge_cleanup, arginfo_git_repository_merge_cleanup)
	PHP_FE(git_repository_fetchhead_foreach, arginfo_git_repository_fetchhead_foreach)
	PHP_FE(git_repository_mergehead_foreach, arginfo_git_repository_mergehead_foreach)
	PHP_FE(git_repository_hashfile, arginfo_git_repository_hashfile)
	PHP_FE(git_repository_set_head, arginfo_git_repository_set_head)
	PHP_FE(git_repository_set_head_detached, arginfo_git_repository_set_head_detached)
	PHP_FE(git_repository_detach_head, arginfo_git_repository_detach_head)
	PHP_FE(git_repository_state, arginfo_git_repository_state)
	PHP_FE(git_repository_set_namespace, arginfo_git_repository_set_namespace)
	PHP_FE(git_repository_is_shallow, arginfo_git_repository_is_shallow)

	/* index */
	PHP_FE(git_index_open, arginfo_git_index_open)
	PHP_FE(git_index_new, arginfo_git_index_new)
	PHP_FE(git_index_free, arginfo_git_index_free)
	PHP_FE(git_index_owner, arginfo_git_index_owner)
	PHP_FE(git_index_caps, arginfo_git_index_caps)
	PHP_FE(git_index_set_caps, arginfo_git_index_set_caps)
	PHP_FE(git_index_read, arginfo_git_index_read)
	PHP_FE(git_index_write, arginfo_git_index_write)
	PHP_FE(git_index_path, arginfo_git_index_path)
	PHP_FE(git_index_read_tree, arginfo_git_index_read_tree)
	PHP_FE(git_index_write_tree, arginfo_git_index_write_tree)
	PHP_FE(git_index_write_tree_to, arginfo_git_index_write_tree_to)
	PHP_FE(git_index_entrycount, arginfo_git_index_entrycount)
	PHP_FE(git_index_clear, arginfo_git_index_clear)
	PHP_FE(git_index_get_byindex, arginfo_git_index_get_byindex)
	PHP_FE(git_index_get_bypath, arginfo_git_index_get_bypath)
	PHP_FE(git_index_remove, arginfo_git_index_remove)
	PHP_FE(git_index_remove_directory, arginfo_git_index_remove_directory)
	PHP_FE(git_index_add, arginfo_git_index_add)
	PHP_FE(git_index_entry_stage, arginfo_git_index_entry_stage)
	PHP_FE(git_index_add_bypath, arginfo_git_index_add_bypath)
	PHP_FE(git_index_remove_bypath, arginfo_git_index_remove_bypath)
	PHP_FE(git_index_add_all, arginfo_git_index_add_all)
	PHP_FE(git_index_remove_all, arginfo_git_index_remove_all)
	PHP_FE(git_index_update_all, arginfo_git_index_update_all)
	PHP_FE(git_index_find, arginfo_git_index_find)
	PHP_FE(git_index_conflict_add, arginfo_git_index_conflict_add)
	PHP_FE(git_index_conflict_get, arginfo_git_index_conflict_get)
	PHP_FE(git_index_conflict_remove, arginfo_git_index_conflict_remove)
	PHP_FE(git_index_conflict_cleanup, arginfo_git_index_conflict_cleanup)
	PHP_FE(git_index_has_conflicts, arginfo_git_index_has_conflicts)
	PHP_FE(git_index_conflict_iterator_new, arginfo_git_index_conflict_iterator_new)
	PHP_FE(git_index_conflict_next, arginfo_git_index_conflict_next)
	PHP_FE(git_index_conflict_iterator_free, arginfo_git_index_conflict_iterator_free)

	/* object */
	PHP_FE(git_object_lookup, arginfo_git_object_lookup)
	PHP_FE(git_object_lookup_prefix, arginfo_git_object_lookup_prefix)
	PHP_FE(git_object_lookup_bypath, arginfo_git_object_lookup_bypath)
	PHP_FE(git_object_id, arginfo_git_object_id)
	PHP_FE(git_object_type, arginfo_git_object_type)
	PHP_FE(git_object_owner, arginfo_git_object_owner)
	PHP_FE(git_object_free, arginfo_git_object_free)
	PHP_FE(git_object_type2string, arginfo_git_object_type2string)
	PHP_FE(git_object_string2type, arginfo_git_object_string2type)
	PHP_FE(git_object_typeisloose, arginfo_git_object_typeisloose)
	PHP_FE(git_object__size, arginfo_git_object__size)
	PHP_FE(git_object_peel, arginfo_git_object_peel)
	PHP_FE(git_object_dup, arginfo_git_object_dup)

	/* clone */
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

	/* config */
	PHP_FE(git_config_find_global, arginfo_git_config_find_global)
	PHP_FE(git_config_find_xdg, arginfo_git_config_find_xdg)
	PHP_FE(git_config_find_system, arginfo_git_config_find_system)
	PHP_FE(git_config_open_default, arginfo_git_config_open_default)
	PHP_FE(git_config_new, arginfo_git_config_new)
	PHP_FE(git_config_add_file_ondisk, arginfo_git_config_add_file_ondisk)
	PHP_FE(git_config_open_ondisk, arginfo_git_config_open_ondisk)
	PHP_FE(git_config_open_level, arginfo_git_config_open_level)
	PHP_FE(git_config_open_global, arginfo_git_config_open_global)
	PHP_FE(git_config_refresh, arginfo_git_config_refresh)
	PHP_FE(git_config_free, arginfo_git_config_free)
	PHP_FE(git_config_get_entry, arginfo_git_config_get_entry)
	PHP_FE(git_config_get_int32, arginfo_git_config_get_int32)
	PHP_FE(git_config_get_int64, arginfo_git_config_get_int64)
	PHP_FE(git_config_get_bool, arginfo_git_config_get_bool)
	PHP_FE(git_config_get_string, arginfo_git_config_get_string)
	PHP_FE(git_config_get_multivar_foreach, arginfo_git_config_get_multivar_foreach)
	PHP_FE(git_config_multivar_iterator_new, arginfo_git_config_multivar_iterator_new)
	PHP_FE(git_config_next, arginfo_git_config_next)
	PHP_FE(git_config_iterator_free, arginfo_git_config_iterator_free)
	PHP_FE(git_config_set_int32, arginfo_git_config_set_int32)
	PHP_FE(git_config_set_int64, arginfo_git_config_set_int64)
	PHP_FE(git_config_set_bool, arginfo_git_config_set_bool)
	PHP_FE(git_config_set_string, arginfo_git_config_set_string)
	PHP_FE(git_config_set_multivar, arginfo_git_config_set_multivar)
	PHP_FE(git_config_delete_entry, arginfo_git_config_delete_entry)
	PHP_FE(git_config_delete_multivar, arginfo_git_config_delete_multivar)
	PHP_FE(git_config_foreach, arginfo_git_config_foreach)
	PHP_FE(git_config_iterator_new, arginfo_git_config_iterator_new)
	PHP_FE(git_config_iterator_glob_new, arginfo_git_config_iterator_glob_new)
	PHP_FE(git_config_foreach_match, arginfo_git_config_foreach_match)
	PHP_FE(git_config_get_mapped, arginfo_git_config_get_mapped)
	PHP_FE(git_config_lookup_map_value, arginfo_git_config_lookup_map_value)
	PHP_FE(git_config_parse_bool, arginfo_git_config_parse_bool)
	PHP_FE(git_config_parse_int32, arginfo_git_config_parse_int32)
	PHP_FE(git_config_parse_int64, arginfo_git_config_parse_int64)
	PHP_FE(git_config_backend_foreach_match, arginfo_git_config_backend_foreach_match)

	/* revparse */
	PHP_FE(git_revparse_single, arginfo_git_revparse_single)
	PHP_FE(git_revparse_ext, arginfo_git_revparse_ext)
	PHP_FE(git_revparse, arginfo_git_revparse)

	/* remote */
	PHP_FE(git_remote_create, arginfo_git_remote_create)
	PHP_FE(git_remote_create_with_fetchspec, arginfo_git_remote_create_with_fetchspec)
	PHP_FE(git_remote_create_inmemory, arginfo_git_remote_create_inmemory)
	PHP_FE(git_remote_load, arginfo_git_remote_load)
	PHP_FE(git_remote_save, arginfo_git_remote_save)
	PHP_FE(git_remote_owner, arginfo_git_remote_owner)
	PHP_FE(git_remote_name, arginfo_git_remote_name)
	PHP_FE(git_remote_url, arginfo_git_remote_url)
	PHP_FE(git_remote_pushurl, arginfo_git_remote_pushurl)
	PHP_FE(git_remote_set_url, arginfo_git_remote_set_url)
	PHP_FE(git_remote_set_pushurl, arginfo_git_remote_set_pushurl)
	PHP_FE(git_remote_add_fetch, arginfo_git_remote_add_fetch)
	PHP_FE(git_remote_get_fetch_refspecs, arginfo_git_remote_get_fetch_refspecs)
	PHP_FE(git_remote_set_fetch_refspecs, arginfo_git_remote_set_fetch_refspecs)
	PHP_FE(git_remote_add_push, arginfo_git_remote_add_push)
	PHP_FE(git_remote_get_push_refspecs, arginfo_git_remote_get_push_refspecs)
	PHP_FE(git_remote_set_push_refspecs, arginfo_git_remote_set_push_refspecs)
	PHP_FE(git_remote_clear_refspecs, arginfo_git_remote_clear_refspecs)
	PHP_FE(git_remote_refspec_count, arginfo_git_remote_refspec_count)
	PHP_FE(git_remote_get_refspec, arginfo_git_remote_get_refspec)
	PHP_FE(git_remote_connect, arginfo_git_remote_connect)
	PHP_FE(git_remote_ls, arginfo_git_remote_ls)
	PHP_FE(git_remote_download, arginfo_git_remote_download)
	PHP_FE(git_remote_connected, arginfo_git_remote_connected)
	PHP_FE(git_remote_stop, arginfo_git_remote_stop)
	PHP_FE(git_remote_disconnect, arginfo_git_remote_disconnect)
	PHP_FE(git_remote_free, arginfo_git_remote_free)
	PHP_FE(git_remote_update_tips, arginfo_git_remote_update_tips)
	PHP_FE(git_remote_fetch, arginfo_git_remote_fetch)
	PHP_FE(git_remote_valid_url, arginfo_git_remote_valid_url)
	PHP_FE(git_remote_supported_url, arginfo_git_remote_supported_url)
	PHP_FE(git_remote_list, arginfo_git_remote_list)
	PHP_FE(git_remote_check_cert, arginfo_git_remote_check_cert)
	PHP_FE(git_remote_set_transport, arginfo_git_remote_set_transport)
	PHP_FE(git_remote_set_callbacks, arginfo_git_remote_set_callbacks)
	PHP_FE(git_remote_stats, arginfo_git_remote_stats)
	PHP_FE(git_remote_autotag, arginfo_git_remote_autotag)
	PHP_FE(git_remote_set_autotag, arginfo_git_remote_set_autotag)
	PHP_FE(git_remote_rename, arginfo_git_remote_rename)
	PHP_FE(git_remote_update_fetchhead, arginfo_git_remote_update_fetchhead)
	PHP_FE(git_remote_set_update_fetchhead, arginfo_git_remote_set_update_fetchhead)
	PHP_FE(git_remote_is_valid_name, arginfo_git_remote_is_valid_name)

	/* cred */
	PHP_FE(git_cred_has_username, arginfo_git_cred_has_username)
	PHP_FE(git_cred_userpass_plaintext_new, arginfo_git_cred_userpass_plaintext_new)
	PHP_FE(git_cred_ssh_key_new, arginfo_git_cred_ssh_key_new)
	PHP_FE(git_cred_ssh_custom_new, arginfo_git_cred_ssh_custom_new)
	PHP_FE(git_cred_default_new, arginfo_git_cred_default_new)
	PHP_FE(git_cred_userpass, arginfo_git_cred_userpass)

	/* status */
	PHP_FE(git_status_foreach, arginfo_git_status_foreach)
	PHP_FE(git_status_foreach_ext, arginfo_git_status_foreach_ext)
	PHP_FE(git_status_file, arginfo_git_status_file)
	PHP_FE(git_status_list_new, arginfo_git_status_list_new)
	PHP_FE(git_status_list_entrycount, arginfo_git_status_list_entrycount)
	PHP_FE(git_status_byindex, arginfo_git_status_byindex)
	PHP_FE(git_status_list_free, arginfo_git_status_list_free)
	PHP_FE(git_status_should_ignore, arginfo_git_status_should_ignore)

	/* transport */
	PHP_FE(git_transport_new, arginfo_git_transport_new)
	PHP_FE(git_transport_register, arginfo_git_transport_register)
	PHP_FE(git_transport_unregister, arginfo_git_transport_unregister)
	PHP_FE(git_transport_dummy, arginfo_git_transport_dummy)
	PHP_FE(git_transport_local, arginfo_git_transport_local)
	PHP_FE(git_transport_smart, arginfo_git_transport_smart)
	PHP_FE(git_smart_subtransport_http, arginfo_git_smart_subtransport_http)
	PHP_FE(git_smart_subtransport_git, arginfo_git_smart_subtransport_git)
	PHP_FE(git_smart_subtransport_ssh, arginfo_git_smart_subtransport_ssh)

	/* diff */
	PHP_FE(git_diff_free, arginfo_git_diff_free)
	PHP_FE(git_diff_tree_to_tree, arginfo_git_diff_tree_to_tree)
	PHP_FE(git_diff_tree_to_index, arginfo_git_diff_tree_to_index)
	PHP_FE(git_diff_index_to_workdir, arginfo_git_diff_index_to_workdir)
	PHP_FE(git_diff_tree_to_workdir, arginfo_git_diff_tree_to_workdir)
	PHP_FE(git_diff_tree_to_workdir_with_index, arginfo_git_diff_tree_to_workdir_with_index)
	PHP_FE(git_diff_merge, arginfo_git_diff_merge)
	PHP_FE(git_diff_find_similar, arginfo_git_diff_find_similar)
	PHP_FE(git_diff_options_init, arginfo_git_diff_options_init)
	PHP_FE(git_diff_num_deltas, arginfo_git_diff_num_deltas)
	PHP_FE(git_diff_num_deltas_of_type, arginfo_git_diff_num_deltas_of_type)
	PHP_FE(git_diff_get_delta, arginfo_git_diff_get_delta)
	PHP_FE(git_diff_is_sorted_icase, arginfo_git_diff_is_sorted_icase)
	PHP_FE(git_diff_foreach, arginfo_git_diff_foreach)
	PHP_FE(git_diff_status_char, arginfo_git_diff_status_char)
	PHP_FE(git_diff_print, arginfo_git_diff_print)
	PHP_FE(git_diff_blobs, arginfo_git_diff_blobs)
	PHP_FE(git_diff_blob_to_buffer, arginfo_git_diff_blob_to_buffer)

	/* checkout */
	PHP_FE(git_checkout_head, arginfo_git_checkout_head)
	PHP_FE(git_checkout_index, arginfo_git_checkout_index)
	PHP_FE(git_checkout_tree, arginfo_git_checkout_tree)

	/* filter */
	PHP_FE(git_filter_list_load, arginfo_git_filter_list_load)
	PHP_FE(git_filter_list_apply_to_data, arginfo_git_filter_list_apply_to_data)
	PHP_FE(git_filter_list_apply_to_file, arginfo_git_filter_list_apply_to_file)
	PHP_FE(git_filter_list_apply_to_blob, arginfo_git_filter_list_apply_to_blob)
	PHP_FE(git_filter_list_free, arginfo_git_filter_list_free)
	PHP_FE(git_filter_lookup, arginfo_git_filter_lookup)
	PHP_FE(git_filter_list_new, arginfo_git_filter_list_new)
	PHP_FE(git_filter_list_push, arginfo_git_filter_list_push)
	PHP_FE(git_filter_list_length, arginfo_git_filter_list_length)
	PHP_FE(git_filter_source_repo, arginfo_git_filter_source_repo)
	PHP_FE(git_filter_source_path, arginfo_git_filter_source_path)
	PHP_FE(git_filter_source_filemode, arginfo_git_filter_source_filemode)
	PHP_FE(git_filter_source_id, arginfo_git_filter_source_id)
	PHP_FE(git_filter_source_mode, arginfo_git_filter_source_mode)
	PHP_FE(git_filter_register, arginfo_git_filter_register)
	PHP_FE(git_filter_unregister, arginfo_git_filter_unregister)

	/* ignore */
	PHP_FE(git_ignore_add_rule, arginfo_git_ignore_add_rule)
	PHP_FE(git_ignore_clear_internal_rules, arginfo_git_ignore_clear_internal_rules)
	PHP_FE(git_ignore_path_is_ignored, arginfo_git_ignore_path_is_ignored)

	/* indexer */
	PHP_FE(git_indexer_new, arginfo_git_indexer_new)
	PHP_FE(git_indexer_append, arginfo_git_indexer_append)
	PHP_FE(git_indexer_commit, arginfo_git_indexer_commit)
	PHP_FE(git_indexer_hash, arginfo_git_indexer_hash)
	PHP_FE(git_indexer_free, arginfo_git_indexer_free)

	/* pathspec */
	PHP_FE(git_pathspec_new, arginfo_git_pathspec_new)
	PHP_FE(git_pathspec_free, arginfo_git_pathspec_free)
	PHP_FE(git_pathspec_matches_path, arginfo_git_pathspec_matches_path)
	PHP_FE(git_pathspec_match_workdir, arginfo_git_pathspec_match_workdir)
	PHP_FE(git_pathspec_match_index, arginfo_git_pathspec_match_index)
	PHP_FE(git_pathspec_match_tree, arginfo_git_pathspec_match_tree)
	PHP_FE(git_pathspec_match_diff, arginfo_git_pathspec_match_diff)
	PHP_FE(git_pathspec_match_list_free, arginfo_git_pathspec_match_list_free)
	PHP_FE(git_pathspec_match_list_entrycount, arginfo_git_pathspec_match_list_entrycount)
	PHP_FE(git_pathspec_match_list_entry, arginfo_git_pathspec_match_list_entry)
	PHP_FE(git_pathspec_match_list_diff_entry, arginfo_git_pathspec_match_list_diff_entry)
	PHP_FE(git_pathspec_match_list_failed_entrycount, arginfo_git_pathspec_match_list_failed_entrycount)
	PHP_FE(git_pathspec_match_list_failed_entry, arginfo_git_pathspec_match_list_failed_entry)

	/* patch */
	PHP_FE(git_patch_from_diff, arginfo_git_patch_from_diff)
	PHP_FE(git_patch_from_blobs, arginfo_git_patch_from_blobs)
	PHP_FE(git_patch_from_blob_and_buffer, arginfo_git_patch_from_blob_and_buffer)
	PHP_FE(git_patch_free, arginfo_git_patch_free)
	PHP_FE(git_patch_get_delta, arginfo_git_patch_get_delta)
	PHP_FE(git_patch_num_hunks, arginfo_git_patch_num_hunks)
	PHP_FE(git_patch_line_stats, arginfo_git_patch_line_stats)
	PHP_FE(git_patch_get_hunk, arginfo_git_patch_get_hunk)
	PHP_FE(git_patch_num_lines_in_hunk, arginfo_git_patch_num_lines_in_hunk)
	PHP_FE(git_patch_get_line_in_hunk, arginfo_git_patch_get_line_in_hunk)
	PHP_FE(git_patch_size, arginfo_git_patch_size)
	PHP_FE(git_patch_print, arginfo_git_patch_print)
	PHP_FE(git_patch_to_str, arginfo_git_patch_to_str)

	/* merge */
	PHP_FE(git_merge_base, arginfo_git_merge_base)
	PHP_FE(git_merge_base_many, arginfo_git_merge_base_many)
	PHP_FE(git_merge_head_from_ref, arginfo_git_merge_head_from_ref)
	PHP_FE(git_merge_head_from_fetchhead, arginfo_git_merge_head_from_fetchhead)
	PHP_FE(git_merge_head_from_oid, arginfo_git_merge_head_from_oid)
	PHP_FE(git_merge_head_free, arginfo_git_merge_head_free)
	PHP_FE(git_merge_trees, arginfo_git_merge_trees)
	PHP_FE(git_merge, arginfo_git_merge)
	PHP_FE(git_merge_result_is_uptodate, arginfo_git_merge_result_is_uptodate)
	PHP_FE(git_merge_result_is_fastforward, arginfo_git_merge_result_is_fastforward)
	PHP_FE(git_merge_result_fastforward_oid, arginfo_git_merge_result_fastforward_oid)
	PHP_FE(git_merge_result_free, arginfo_git_merge_result_free)

	/* misc */
	PHP_FE(git_resource_type, arginfo_git_resource_type)
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
	php_info_print_table_header(2, "libgit2 version", buf);
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

	REGISTER_LONG_CONSTANT("GIT_TYPE_REPOSITORY", PHP_GIT2_TYPE_REPOSITORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_COMMIT", PHP_GIT2_TYPE_COMMIT,CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_TREE", PHP_GIT2_TYPE_TREE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_TREE_ENTRY", PHP_GIT2_TYPE_TREE_ENTRY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_BLOB", PHP_GIT2_TYPE_BLOB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_REVWALK", PHP_GIT2_TYPE_REVWALK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_TREEBUILDER", PHP_GIT2_TYPE_TREEBUILDER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_REFERENCE", PHP_GIT2_TYPE_REFERENCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_CONFIG", PHP_GIT2_TYPE_CONFIG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_OBJECT", PHP_GIT2_TYPE_OBJECT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_INDEX", PHP_GIT2_TYPE_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_ODB", PHP_GIT2_TYPE_ODB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_REFDB", PHP_GIT2_TYPE_REFDB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_BRANCH_ITERATOR", PHP_GIT2_TYPE_BRANCH_ITERATOR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_TAG", PHP_GIT2_TYPE_TAG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_CRED", PHP_GIT2_TYPE_CRED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_TRANSPORT", PHP_GIT2_TYPE_TRANSPORT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_REMOTE", PHP_GIT2_TYPE_REMOTE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_DIFF", PHP_GIT2_TYPE_DIFF, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_MERGE_RESULT", PHP_GIT2_TYPE_MERGE_RESULT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_MERGE_HEAD", PHP_GIT2_TYPE_MERGE_HEAD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_PATHSPEC", PHP_GIT2_TYPE_PATHSPEC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_PATHSPEC_MATCH_LIST", PHP_GIT2_TYPE_PATHSPEC_MATCH_LIST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_PATCH", PHP_GIT2_TYPE_PATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_DIFF_HUNK", PHP_GIT2_TYPE_DIFF_HUNK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_STATUS_LIST", PHP_GIT2_TYPE_STATUS_LIST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_BUF", PHP_GIT2_TYPE_BUF, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_FILTER_LIST", PHP_GIT2_TYPE_FILTER_LIST, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_FILTER_SOURCE", PHP_GIT2_TYPE_FILTER_SOURCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TYPE_DIFF_LINE", PHP_GIT2_TYPE_DIFF_LINE, CONST_CS | CONST_PERSISTENT);

	/* git_ref_t */
	REGISTER_LONG_CONSTANT("GIT_REF_INVALID", GIT_REF_INVALID, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REF_OID", GIT_REF_OID, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REF_SYMBOLIC", GIT_REF_SYMBOLIC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REF_LISTALL", GIT_REF_LISTALL, CONST_CS | CONST_PERSISTENT);
	/* git_branch_t */
	REGISTER_LONG_CONSTANT("GIT_BRANCH_LOCAL", GIT_BRANCH_LOCAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_BRANCH_REMOTE", GIT_BRANCH_REMOTE, CONST_CS | CONST_PERSISTENT);
	/* git_filemode_t */
	REGISTER_LONG_CONSTANT("GIT_FILEMODE_NEW", GIT_FILEMODE_NEW, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILEMODE_TREE", GIT_FILEMODE_TREE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILEMODE_BLOB", GIT_FILEMODE_BLOB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILEMODE_BLOB_EXECUTABLE", GIT_FILEMODE_BLOB_EXECUTABLE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILEMODE_LINK", GIT_FILEMODE_LINK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILEMODE_COMMIT", GIT_FILEMODE_COMMIT, CONST_CS | CONST_PERSISTENT);
	/* git_submodule_update_t */
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_UPDATE_RESET", GIT_SUBMODULE_UPDATE_RESET, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_UPDATE_CHECKOUT", GIT_SUBMODULE_UPDATE_CHECKOUT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_UPDATE_REBASE", GIT_SUBMODULE_UPDATE_REBASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_UPDATE_MERGE", GIT_SUBMODULE_UPDATE_MERGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_UPDATE_NONE", GIT_SUBMODULE_UPDATE_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_UPDATE_DEFAULT", GIT_SUBMODULE_UPDATE_DEFAULT, CONST_CS | CONST_PERSISTENT);
	/* git_submodule_ignore_t */
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_IGNORE_RESET", GIT_SUBMODULE_IGNORE_RESET, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_IGNORE_NONE", GIT_SUBMODULE_IGNORE_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_IGNORE_UNTRACKED", GIT_SUBMODULE_IGNORE_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_IGNORE_DIRTY", GIT_SUBMODULE_IGNORE_DIRTY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_IGNORE_ALL", GIT_SUBMODULE_IGNORE_ALL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_IGNORE_DEFAULT", GIT_SUBMODULE_IGNORE_DEFAULT, CONST_CS | CONST_PERSISTENT);

	/* git_attr_t */
	REGISTER_LONG_CONSTANT("GIT_ATTR_UNSPECIFIED_T", GIT_ATTR_UNSPECIFIED_T, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ATTR_TRUE_T", GIT_ATTR_TRUE_T, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ATTR_FALSE_T", GIT_ATTR_FALSE_T, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ATTR_VALUE_T", GIT_ATTR_VALUE_T, CONST_CS | CONST_PERSISTENT);

	/* git_blame_flag_t */
	REGISTER_LONG_CONSTANT("GIT_BLAME_NORMAL", GIT_BLAME_NORMAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_BLAME_TRACK_COPIES_SAME_FILE", GIT_BLAME_TRACK_COPIES_SAME_FILE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_BLAME_TRACK_COPIES_SAME_COMMIT_MOVES", GIT_BLAME_TRACK_COPIES_SAME_COMMIT_MOVES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES", GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_BLAME_TRACK_COPIES_ANY_COMMIT_COPIES", GIT_BLAME_TRACK_COPIES_ANY_COMMIT_COPIES, CONST_CS | CONST_PERSISTENT);

	/* git_checkout_strategy_t */
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NONE", GIT_CHECKOUT_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_SAFE", GIT_CHECKOUT_SAFE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_SAFE_CREATE", GIT_CHECKOUT_SAFE_CREATE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_FORCE", GIT_CHECKOUT_FORCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_ALLOW_CONFLICTS", GIT_CHECKOUT_ALLOW_CONFLICTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_REMOVE_UNTRACKED", GIT_CHECKOUT_REMOVE_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_REMOVE_IGNORED", GIT_CHECKOUT_REMOVE_IGNORED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_UPDATE_ONLY", GIT_CHECKOUT_UPDATE_ONLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_DONT_UPDATE_INDEX", GIT_CHECKOUT_DONT_UPDATE_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NO_REFRESH", GIT_CHECKOUT_NO_REFRESH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_SKIP_UNMERGED", GIT_CHECKOUT_SKIP_UNMERGED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_USE_OURS", GIT_CHECKOUT_USE_OURS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_USE_THEIRS", GIT_CHECKOUT_USE_THEIRS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_DISABLE_PATHSPEC_MATCH", GIT_CHECKOUT_DISABLE_PATHSPEC_MATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_SKIP_LOCKED_DIRECTORIES", GIT_CHECKOUT_SKIP_LOCKED_DIRECTORIES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_UPDATE_SUBMODULES", GIT_CHECKOUT_UPDATE_SUBMODULES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_UPDATE_SUBMODULES_IF_CHANGED", GIT_CHECKOUT_UPDATE_SUBMODULES_IF_CHANGED, CONST_CS | CONST_PERSISTENT);

	/* git_checkout_notify_t */
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_NONE", GIT_CHECKOUT_NOTIFY_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_CONFLICT", GIT_CHECKOUT_NOTIFY_CONFLICT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_DIRTY", GIT_CHECKOUT_NOTIFY_DIRTY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_UPDATED", GIT_CHECKOUT_NOTIFY_UPDATED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_UNTRACKED", GIT_CHECKOUT_NOTIFY_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_IGNORED", GIT_CHECKOUT_NOTIFY_IGNORED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CHECKOUT_NOTIFY_ALL", GIT_CHECKOUT_NOTIFY_ALL, CONST_CS | CONST_PERSISTENT);

	/* git_cap_t */
	REGISTER_LONG_CONSTANT("GIT_CAP_THREADS", GIT_CAP_THREADS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CAP_HTTPS", GIT_CAP_HTTPS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CAP_SSH", GIT_CAP_SSH, CONST_CS | CONST_PERSISTENT);

	/* git_libgit2_opt_t */
	REGISTER_LONG_CONSTANT("GIT_OPT_GET_MWINDOW_SIZE", GIT_OPT_GET_MWINDOW_SIZE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_SET_MWINDOW_SIZE", GIT_OPT_SET_MWINDOW_SIZE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_GET_MWINDOW_MAPPED_LIMIT", GIT_OPT_GET_MWINDOW_MAPPED_LIMIT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_SET_MWINDOW_MAPPED_LIMIT", GIT_OPT_SET_MWINDOW_MAPPED_LIMIT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_GET_SEARCH_PATH", GIT_OPT_GET_SEARCH_PATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_SET_SEARCH_PATH", GIT_OPT_SET_SEARCH_PATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_SET_CACHE_OBJECT_LIMIT", GIT_OPT_SET_CACHE_OBJECT_LIMIT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_SET_CACHE_MAX_SIZE", GIT_OPT_SET_CACHE_MAX_SIZE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_ENABLE_CACHING", GIT_OPT_ENABLE_CACHING, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_GET_CACHED_MEMORY", GIT_OPT_GET_CACHED_MEMORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_GET_TEMPLATE_PATH", GIT_OPT_GET_TEMPLATE_PATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OPT_SET_TEMPLATE_PATH", GIT_OPT_SET_TEMPLATE_PATH, CONST_CS | CONST_PERSISTENT);

	/* git_config_level_t */
	REGISTER_LONG_CONSTANT("GIT_CONFIG_LEVEL_SYSTEM", GIT_CONFIG_LEVEL_SYSTEM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CONFIG_LEVEL_XDG", GIT_CONFIG_LEVEL_XDG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CONFIG_LEVEL_GLOBAL", GIT_CONFIG_LEVEL_GLOBAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CONFIG_LEVEL_LOCAL", GIT_CONFIG_LEVEL_LOCAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CONFIG_LEVEL_APP", GIT_CONFIG_LEVEL_APP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CONFIG_HIGHEST_LEVEL", GIT_CONFIG_HIGHEST_LEVEL, CONST_CS | CONST_PERSISTENT);

	/* git_cvar_t */
	REGISTER_LONG_CONSTANT("GIT_CVAR_FALSE", GIT_CVAR_FALSE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CVAR_TRUE", GIT_CVAR_TRUE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CVAR_INT32", GIT_CVAR_INT32, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CVAR_STRING", GIT_CVAR_STRING, CONST_CS | CONST_PERSISTENT);

	/* git_diff_option_t */
	REGISTER_LONG_CONSTANT("GIT_DIFF_NORMAL", GIT_DIFF_NORMAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_REVERSE", GIT_DIFF_REVERSE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_INCLUDE_IGNORED", GIT_DIFF_INCLUDE_IGNORED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_RECURSE_IGNORED_DIRS", GIT_DIFF_RECURSE_IGNORED_DIRS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_INCLUDE_UNTRACKED", GIT_DIFF_INCLUDE_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_RECURSE_UNTRACKED_DIRS", GIT_DIFF_RECURSE_UNTRACKED_DIRS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_INCLUDE_UNMODIFIED", GIT_DIFF_INCLUDE_UNMODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_INCLUDE_TYPECHANGE", GIT_DIFF_INCLUDE_TYPECHANGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_INCLUDE_TYPECHANGE_TREES", GIT_DIFF_INCLUDE_TYPECHANGE_TREES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_IGNORE_FILEMODE", GIT_DIFF_IGNORE_FILEMODE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_IGNORE_SUBMODULES", GIT_DIFF_IGNORE_SUBMODULES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_IGNORE_CASE", GIT_DIFF_IGNORE_CASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_DISABLE_PATHSPEC_MATCH", GIT_DIFF_DISABLE_PATHSPEC_MATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_SKIP_BINARY_CHECK", GIT_DIFF_SKIP_BINARY_CHECK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_ENABLE_FAST_UNTRACKED_DIRS", GIT_DIFF_ENABLE_FAST_UNTRACKED_DIRS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORCE_TEXT", GIT_DIFF_FORCE_TEXT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORCE_BINARY", GIT_DIFF_FORCE_BINARY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_IGNORE_WHITESPACE", GIT_DIFF_IGNORE_WHITESPACE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_IGNORE_WHITESPACE_CHANGE", GIT_DIFF_IGNORE_WHITESPACE_CHANGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_IGNORE_WHITESPACE_EOL", GIT_DIFF_IGNORE_WHITESPACE_EOL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_SHOW_UNTRACKED_CONTENT", GIT_DIFF_SHOW_UNTRACKED_CONTENT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_SHOW_UNMODIFIED", GIT_DIFF_SHOW_UNMODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_PATIENCE", GIT_DIFF_PATIENCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_MINIMAL", GIT_DIFF_MINIMAL, CONST_CS | CONST_PERSISTENT);
	/* git_diff_flag_t */
	REGISTER_LONG_CONSTANT("GIT_DIFF_FLAG_BINARY", GIT_DIFF_FLAG_BINARY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FLAG_NOT_BINARY", GIT_DIFF_FLAG_NOT_BINARY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FLAG_VALID_OID", GIT_DIFF_FLAG_VALID_OID, CONST_CS | CONST_PERSISTENT);
	/* git_delta_t */
	REGISTER_LONG_CONSTANT("GIT_DELTA_UNMODIFIED", GIT_DELTA_UNMODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_ADDED", GIT_DELTA_ADDED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_DELETED", GIT_DELTA_DELETED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_MODIFIED", GIT_DELTA_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_RENAMED", GIT_DELTA_RENAMED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_COPIED", GIT_DELTA_COPIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_IGNORED", GIT_DELTA_IGNORED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_UNTRACKED", GIT_DELTA_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DELTA_TYPECHANGE", GIT_DELTA_TYPECHANGE, CONST_CS | CONST_PERSISTENT);
	/* git_diff_line_t */
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_CONTEXT", GIT_DIFF_LINE_CONTEXT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_ADDITION", GIT_DIFF_LINE_ADDITION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_DELETION", GIT_DIFF_LINE_DELETION, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_CONTEXT_EOFNL", GIT_DIFF_LINE_CONTEXT_EOFNL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_ADD_EOFNL", GIT_DIFF_LINE_ADD_EOFNL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_DEL_EOFNL", GIT_DIFF_LINE_DEL_EOFNL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_FILE_HDR", GIT_DIFF_LINE_FILE_HDR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_HUNK_HDR", GIT_DIFF_LINE_HUNK_HDR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_LINE_BINARY", GIT_DIFF_LINE_BINARY, CONST_CS | CONST_PERSISTENT);
	/* git_diff_find_t */
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_RENAMES", GIT_DIFF_FIND_RENAMES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_RENAMES_FROM_REWRITES", GIT_DIFF_FIND_RENAMES_FROM_REWRITES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_COPIES", GIT_DIFF_FIND_COPIES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED", GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_REWRITES", GIT_DIFF_FIND_REWRITES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_BREAK_REWRITES", GIT_DIFF_BREAK_REWRITES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_AND_BREAK_REWRITES", GIT_DIFF_FIND_AND_BREAK_REWRITES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("(GIT_DIFF_FIND_REWRITES | GIT_DIFF_BREAK_REWRITES)", (GIT_DIFF_FIND_REWRITES | GIT_DIFF_BREAK_REWRITES), CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_FOR_UNTRACKED", GIT_DIFF_FIND_FOR_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_ALL", GIT_DIFF_FIND_ALL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_IGNORE_LEADING_WHITESPACE", GIT_DIFF_FIND_IGNORE_LEADING_WHITESPACE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_IGNORE_WHITESPACE", GIT_DIFF_FIND_IGNORE_WHITESPACE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_DONT_IGNORE_WHITESPACE", GIT_DIFF_FIND_DONT_IGNORE_WHITESPACE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FIND_EXACT_MATCH_ONLY", GIT_DIFF_FIND_EXACT_MATCH_ONLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_BREAK_REWRITES_FOR_RENAMES_ONLY", GIT_DIFF_BREAK_REWRITES_FOR_RENAMES_ONLY, CONST_CS | CONST_PERSISTENT);
	/* git_diff_format_t */
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORMAT_PATCH", GIT_DIFF_FORMAT_PATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORMAT_PATCH_HEADER", GIT_DIFF_FORMAT_PATCH_HEADER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORMAT_RAW", GIT_DIFF_FORMAT_RAW, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORMAT_NAME_ONLY", GIT_DIFF_FORMAT_NAME_ONLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIFF_FORMAT_NAME_STATUS", GIT_DIFF_FORMAT_NAME_STATUS, CONST_CS | CONST_PERSISTENT);

	/* git_error_code */
	REGISTER_LONG_CONSTANT("GIT_OK", GIT_OK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ERROR", GIT_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ENOTFOUND", GIT_ENOTFOUND, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EEXISTS", GIT_EEXISTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EAMBIGUOUS", GIT_EAMBIGUOUS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EBUFS", GIT_EBUFS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EUSER", GIT_EUSER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EBAREREPO", GIT_EBAREREPO, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EUNBORNBRANCH", GIT_EUNBORNBRANCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EUNMERGED", GIT_EUNMERGED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ENONFASTFORWARD", GIT_ENONFASTFORWARD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EINVALIDSPEC", GIT_EINVALIDSPEC, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_EMERGECONFLICT", GIT_EMERGECONFLICT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ELOCKED", GIT_ELOCKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PASSTHROUGH", GIT_PASSTHROUGH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_ITEROVER", GIT_ITEROVER, CONST_CS | CONST_PERSISTENT);

	/* git_error_t */
	REGISTER_LONG_CONSTANT("GITERR_NONE", GITERR_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_NOMEMORY", GITERR_NOMEMORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_OS", GITERR_OS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_INVALID", GITERR_INVALID, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_REFERENCE", GITERR_REFERENCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_ZLIB", GITERR_ZLIB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_REPOSITORY", GITERR_REPOSITORY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_CONFIG", GITERR_CONFIG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_REGEX", GITERR_REGEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_ODB", GITERR_ODB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_INDEX", GITERR_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_OBJECT", GITERR_OBJECT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_NET", GITERR_NET, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_TAG", GITERR_TAG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_TREE", GITERR_TREE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_INDEXER", GITERR_INDEXER, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_SSL", GITERR_SSL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_SUBMODULE", GITERR_SUBMODULE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_THREAD", GITERR_THREAD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_STASH", GITERR_STASH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_CHECKOUT", GITERR_CHECKOUT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_FETCHHEAD", GITERR_FETCHHEAD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_MERGE", GITERR_MERGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_SSH", GITERR_SSH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GITERR_FILTER", GITERR_FILTER, CONST_CS | CONST_PERSISTENT);

	/* git_filter_mode_t */
	REGISTER_LONG_CONSTANT("GIT_FILTER_TO_WORKTREE", GIT_FILTER_TO_WORKTREE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILTER_SMUDGE", GIT_FILTER_SMUDGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILTER_TO_ODB", GIT_FILTER_TO_ODB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_FILTER_CLEAN", GIT_FILTER_CLEAN, CONST_CS | CONST_PERSISTENT);

	/* git_indexcap_t */
	REGISTER_LONG_CONSTANT("GIT_INDEXCAP_IGNORE_CASE", GIT_INDEXCAP_IGNORE_CASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_INDEXCAP_NO_FILEMODE", GIT_INDEXCAP_NO_FILEMODE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_INDEXCAP_NO_SYMLINKS", GIT_INDEXCAP_NO_SYMLINKS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_INDEXCAP_FROM_OWNER", GIT_INDEXCAP_FROM_OWNER, CONST_CS | CONST_PERSISTENT);
	/* git_index_add_option_t */
	REGISTER_LONG_CONSTANT("GIT_INDEX_ADD_DEFAULT", GIT_INDEX_ADD_DEFAULT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_INDEX_ADD_FORCE", GIT_INDEX_ADD_FORCE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_INDEX_ADD_DISABLE_PATHSPEC_MATCH", GIT_INDEX_ADD_DISABLE_PATHSPEC_MATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_INDEX_ADD_CHECK_PATHSPEC", GIT_INDEX_ADD_CHECK_PATHSPEC, CONST_CS | CONST_PERSISTENT);

	/* git_merge_tree_flag_t */
	REGISTER_LONG_CONSTANT("GIT_MERGE_TREE_FIND_RENAMES", GIT_MERGE_TREE_FIND_RENAMES, CONST_CS | CONST_PERSISTENT);
	/* git_merge_automerge_flags */
	REGISTER_LONG_CONSTANT("GIT_MERGE_AUTOMERGE_NORMAL", GIT_MERGE_AUTOMERGE_NORMAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_MERGE_AUTOMERGE_NONE", GIT_MERGE_AUTOMERGE_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_MERGE_AUTOMERGE_FAVOR_OURS", GIT_MERGE_AUTOMERGE_FAVOR_OURS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_MERGE_AUTOMERGE_FAVOR_THEIRS", GIT_MERGE_AUTOMERGE_FAVOR_THEIRS, CONST_CS | CONST_PERSISTENT);
	/* git_merge_flags_t */
	REGISTER_LONG_CONSTANT("GIT_MERGE_NO_FASTFORWARD", GIT_MERGE_NO_FASTFORWARD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_MERGE_FASTFORWARD_ONLY", GIT_MERGE_FASTFORWARD_ONLY, CONST_CS | CONST_PERSISTENT);

	/* git_direction */
	REGISTER_LONG_CONSTANT("GIT_DIRECTION_FETCH", GIT_DIRECTION_FETCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_DIRECTION_PUSH", GIT_DIRECTION_PUSH, CONST_CS | CONST_PERSISTENT);

	/* git_odb_stream_t */
	REGISTER_LONG_CONSTANT("GIT_STREAM_RDONLY", GIT_STREAM_RDONLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STREAM_WRONLY", GIT_STREAM_WRONLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STREAM_RW", GIT_STREAM_RW, CONST_CS | CONST_PERSISTENT);

	/* git_packbuilder_stage_t */
	REGISTER_LONG_CONSTANT("GIT_PACKBUILDER_ADDING_OBJECTS", GIT_PACKBUILDER_ADDING_OBJECTS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PACKBUILDER_DELTAFICATION", GIT_PACKBUILDER_DELTAFICATION, CONST_CS | CONST_PERSISTENT);

	/* git_pathspec_flag_t */
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_DEFAULT", GIT_PATHSPEC_DEFAULT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_IGNORE_CASE", GIT_PATHSPEC_IGNORE_CASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_USE_CASE", GIT_PATHSPEC_USE_CASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_NO_GLOB", GIT_PATHSPEC_NO_GLOB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_NO_MATCH_ERROR", GIT_PATHSPEC_NO_MATCH_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_FIND_FAILURES", GIT_PATHSPEC_FIND_FAILURES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_PATHSPEC_FAILURES_ONLY", GIT_PATHSPEC_FAILURES_ONLY, CONST_CS | CONST_PERSISTENT);

	/* git_reference_normalize_t */
	REGISTER_LONG_CONSTANT("GIT_REF_FORMAT_NORMAL", GIT_REF_FORMAT_NORMAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REF_FORMAT_ALLOW_ONELEVEL", GIT_REF_FORMAT_ALLOW_ONELEVEL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REF_FORMAT_REFSPEC_PATTERN", GIT_REF_FORMAT_REFSPEC_PATTERN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REF_FORMAT_REFSPEC_SHORTHAND", GIT_REF_FORMAT_REFSPEC_SHORTHAND, CONST_CS | CONST_PERSISTENT);

	/* git_remote_autotag_option_t */
	REGISTER_LONG_CONSTANT("GIT_REMOTE_DOWNLOAD_TAGS_AUTO", GIT_REMOTE_DOWNLOAD_TAGS_AUTO, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REMOTE_DOWNLOAD_TAGS_NONE", GIT_REMOTE_DOWNLOAD_TAGS_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REMOTE_DOWNLOAD_TAGS_ALL", GIT_REMOTE_DOWNLOAD_TAGS_ALL, CONST_CS | CONST_PERSISTENT);

	/* git_repository_open_flag_t */
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_OPEN_NO_SEARCH", GIT_REPOSITORY_OPEN_NO_SEARCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_OPEN_CROSS_FS", GIT_REPOSITORY_OPEN_CROSS_FS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_OPEN_BARE", GIT_REPOSITORY_OPEN_BARE, CONST_CS | CONST_PERSISTENT);
	/* git_repository_init_flag_t */
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_BARE", GIT_REPOSITORY_INIT_BARE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_NO_REINIT", GIT_REPOSITORY_INIT_NO_REINIT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_NO_DOTGIT_DIR", GIT_REPOSITORY_INIT_NO_DOTGIT_DIR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_MKDIR", GIT_REPOSITORY_INIT_MKDIR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_MKPATH", GIT_REPOSITORY_INIT_MKPATH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE", GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE, CONST_CS | CONST_PERSISTENT);
	/* git_repository_init_mode_t */
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_SHARED_UMASK", GIT_REPOSITORY_INIT_SHARED_UMASK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_SHARED_GROUP", GIT_REPOSITORY_INIT_SHARED_GROUP, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_INIT_SHARED_ALL", GIT_REPOSITORY_INIT_SHARED_ALL, CONST_CS | CONST_PERSISTENT);
	/* git_repository_state_t */
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_NONE", GIT_REPOSITORY_STATE_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_MERGE", GIT_REPOSITORY_STATE_MERGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_REVERT", GIT_REPOSITORY_STATE_REVERT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_CHERRY_PICK", GIT_REPOSITORY_STATE_CHERRY_PICK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_BISECT", GIT_REPOSITORY_STATE_BISECT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_REBASE", GIT_REPOSITORY_STATE_REBASE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_REBASE_INTERACTIVE", GIT_REPOSITORY_STATE_REBASE_INTERACTIVE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_REBASE_MERGE", GIT_REPOSITORY_STATE_REBASE_MERGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_APPLY_MAILBOX", GIT_REPOSITORY_STATE_APPLY_MAILBOX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REPOSITORY_STATE_APPLY_MAILBOX_OR_REBASE", GIT_REPOSITORY_STATE_APPLY_MAILBOX_OR_REBASE, CONST_CS | CONST_PERSISTENT);

	/* git_reset_t */
	REGISTER_LONG_CONSTANT("GIT_RESET_SOFT", GIT_RESET_SOFT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_RESET_MIXED", GIT_RESET_MIXED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_RESET_HARD", GIT_RESET_HARD, CONST_CS | CONST_PERSISTENT);

	/* git_revparse_mode_t */
	REGISTER_LONG_CONSTANT("GIT_REVPARSE_SINGLE", GIT_REVPARSE_SINGLE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REVPARSE_RANGE", GIT_REVPARSE_RANGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_REVPARSE_MERGE_BASE", GIT_REVPARSE_MERGE_BASE, CONST_CS | CONST_PERSISTENT);

	/* git_stash_flags */
	REGISTER_LONG_CONSTANT("GIT_STASH_DEFAULT", GIT_STASH_DEFAULT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STASH_KEEP_INDEX", GIT_STASH_KEEP_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STASH_INCLUDE_UNTRACKED", GIT_STASH_INCLUDE_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STASH_INCLUDE_IGNORED", GIT_STASH_INCLUDE_IGNORED, CONST_CS | CONST_PERSISTENT);

	/* git_status_t */
	REGISTER_LONG_CONSTANT("GIT_STATUS_CURRENT", GIT_STATUS_CURRENT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_INDEX_NEW", GIT_STATUS_INDEX_NEW, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_INDEX_MODIFIED", GIT_STATUS_INDEX_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_INDEX_DELETED", GIT_STATUS_INDEX_DELETED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_INDEX_RENAMED", GIT_STATUS_INDEX_RENAMED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_INDEX_TYPECHANGE", GIT_STATUS_INDEX_TYPECHANGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_WT_NEW", GIT_STATUS_WT_NEW, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_WT_MODIFIED", GIT_STATUS_WT_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_WT_DELETED", GIT_STATUS_WT_DELETED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_WT_TYPECHANGE", GIT_STATUS_WT_TYPECHANGE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_WT_RENAMED", GIT_STATUS_WT_RENAMED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_IGNORED", GIT_STATUS_IGNORED, CONST_CS | CONST_PERSISTENT);
	/* git_status_show_t */
	REGISTER_LONG_CONSTANT("GIT_STATUS_SHOW_INDEX_AND_WORKDIR", GIT_STATUS_SHOW_INDEX_AND_WORKDIR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_SHOW_INDEX_ONLY", GIT_STATUS_SHOW_INDEX_ONLY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_SHOW_WORKDIR_ONLY", GIT_STATUS_SHOW_WORKDIR_ONLY, CONST_CS | CONST_PERSISTENT);
	/* git_status_opt_t */
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_INCLUDE_UNTRACKED", GIT_STATUS_OPT_INCLUDE_UNTRACKED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_INCLUDE_IGNORED", GIT_STATUS_OPT_INCLUDE_IGNORED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_INCLUDE_UNMODIFIED", GIT_STATUS_OPT_INCLUDE_UNMODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_EXCLUDE_SUBMODULES", GIT_STATUS_OPT_EXCLUDE_SUBMODULES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS", GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH", GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_RECURSE_IGNORED_DIRS", GIT_STATUS_OPT_RECURSE_IGNORED_DIRS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX", GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR", GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_SORT_CASE_SENSITIVELY", GIT_STATUS_OPT_SORT_CASE_SENSITIVELY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_SORT_CASE_INSENSITIVELY", GIT_STATUS_OPT_SORT_CASE_INSENSITIVELY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_RENAMES_FROM_REWRITES", GIT_STATUS_OPT_RENAMES_FROM_REWRITES, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_STATUS_OPT_NO_REFRESH", GIT_STATUS_OPT_NO_REFRESH, CONST_CS | CONST_PERSISTENT);

	/* git_submodule_status_t */
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_IN_HEAD", GIT_SUBMODULE_STATUS_IN_HEAD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_IN_INDEX", GIT_SUBMODULE_STATUS_IN_INDEX, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_IN_CONFIG", GIT_SUBMODULE_STATUS_IN_CONFIG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_IN_WD", GIT_SUBMODULE_STATUS_IN_WD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_INDEX_ADDED", GIT_SUBMODULE_STATUS_INDEX_ADDED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_INDEX_DELETED", GIT_SUBMODULE_STATUS_INDEX_DELETED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_INDEX_MODIFIED", GIT_SUBMODULE_STATUS_INDEX_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_UNINITIALIZED", GIT_SUBMODULE_STATUS_WD_UNINITIALIZED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_ADDED", GIT_SUBMODULE_STATUS_WD_ADDED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_DELETED", GIT_SUBMODULE_STATUS_WD_DELETED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_MODIFIED", GIT_SUBMODULE_STATUS_WD_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_INDEX_MODIFIED", GIT_SUBMODULE_STATUS_WD_INDEX_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_WD_MODIFIED", GIT_SUBMODULE_STATUS_WD_WD_MODIFIED, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SUBMODULE_STATUS_WD_UNTRACKED", GIT_SUBMODULE_STATUS_WD_UNTRACKED, CONST_CS | CONST_PERSISTENT);

	/* git_trace_level_t */
	REGISTER_LONG_CONSTANT("GIT_TRACE_NONE", GIT_TRACE_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRACE_FATAL", GIT_TRACE_FATAL, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRACE_ERROR", GIT_TRACE_ERROR, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRACE_WARN", GIT_TRACE_WARN, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRACE_INFO", GIT_TRACE_INFO, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRACE_DEBUG", GIT_TRACE_DEBUG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRACE_TRACE", GIT_TRACE_TRACE, CONST_CS | CONST_PERSISTENT);

	/* git_credtype_t */
	REGISTER_LONG_CONSTANT("GIT_CREDTYPE_USERPASS_PLAINTEXT", GIT_CREDTYPE_USERPASS_PLAINTEXT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CREDTYPE_SSH_KEY", GIT_CREDTYPE_SSH_KEY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CREDTYPE_SSH_CUSTOM", GIT_CREDTYPE_SSH_CUSTOM, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_CREDTYPE_DEFAULT", GIT_CREDTYPE_DEFAULT, CONST_CS | CONST_PERSISTENT);
	/* git_transport_flags_t */
	REGISTER_LONG_CONSTANT("GIT_TRANSPORTFLAGS_NONE", GIT_TRANSPORTFLAGS_NONE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TRANSPORTFLAGS_NO_CHECK_CERT", GIT_TRANSPORTFLAGS_NO_CHECK_CERT, CONST_CS | CONST_PERSISTENT);
	/* git_smart_service_t */
	REGISTER_LONG_CONSTANT("GIT_SERVICE_UPLOADPACK_LS", GIT_SERVICE_UPLOADPACK_LS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SERVICE_UPLOADPACK", GIT_SERVICE_UPLOADPACK, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SERVICE_RECEIVEPACK_LS", GIT_SERVICE_RECEIVEPACK_LS, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_SERVICE_RECEIVEPACK", GIT_SERVICE_RECEIVEPACK, CONST_CS | CONST_PERSISTENT);

	/* git_treewalk_mode */
	REGISTER_LONG_CONSTANT("GIT_TREEWALK_PRE", GIT_TREEWALK_PRE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_TREEWALK_POST", GIT_TREEWALK_POST, CONST_CS | CONST_PERSISTENT);

	/* git_otype */
	REGISTER_LONG_CONSTANT("GIT_OBJ_ANY", GIT_OBJ_ANY, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_BAD", GIT_OBJ_BAD, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ__EXT1", GIT_OBJ__EXT1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_COMMIT", GIT_OBJ_COMMIT, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_TREE", GIT_OBJ_TREE, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_BLOB", GIT_OBJ_BLOB, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_TAG", GIT_OBJ_TAG, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ__EXT2", GIT_OBJ__EXT2, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_OFS_DELTA", GIT_OBJ_OFS_DELTA, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GIT_OBJ_REF_DELTA", GIT_OBJ_REF_DELTA, CONST_CS | CONST_PERSISTENT);

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