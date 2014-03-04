<?php
function git_repository_new(){}
function git_repository_init($path, $is_bare){}
function git_repository_open_bare($bare_path){}
function git_repository_open($path){}
function git_repository_get_namespace($repository){}
function git_repository_workdir($repository){}
function git_repository_wrap_odb($odb){}
function git_repository_discover($path_size, $start_path, $across_fs, $ceiling_dirs){}
function git_repository_open_ext($path, $flags, $ceiling_dirs){}
function git_repository_free($repo){}
function git_repository_init_ext($repo_path, $opts){}
function git_repository_head($repo){}
function git_repository_head_detached($repo){}
function git_repository_head_unborn($repo){}
function git_repository_is_empty($repo){}
function git_repository_path($repo){}
function git_repository_set_workdir($repo, $workdir, $update_gitlink){}
function git_repository_is_bare($repo){}
function git_repository_config($repo){}
function git_repository_odb($repo){}
function git_repository_refdb($repo){}
function git_repository_index($repo){}
function git_repository_message($len, $repo){}
function git_repository_message_remove($repo){}
function git_repository_merge_cleanup($repo){}
function git_repository_fetchhead_foreach($repo, $callback, $payload){}
function git_repository_mergehead_foreach($repo, $callback, $payload){}
function git_repository_hashfile($repo, $path, $type, $as_path){}
function git_repository_set_head($repo, $refname){}
function git_repository_set_head_detached($repo, $commitish){}
function git_repository_detach_head($repo){}
function git_repository_state($repo){}
function git_repository_set_namespace($repo, $nmspace){}
function git_repository_is_shallow($repo){}
function git_repository_init_options_new(){}
function git_index_open($index_path){}
function git_index_new(){}
function git_index_free($index){}
function git_index_owner($index){}
function git_index_caps($index){}
function git_index_set_caps($index, $caps){}
function git_index_read($index, $force){}
function git_index_write(){}
function git_index_path($index){}
function git_index_read_tree($index, $tree){}
function git_index_write_tree($index){}
function git_index_write_tree_to($index, $repo){}
function git_index_entrycount($index){}
function git_index_clear($index){}
function git_index_get_byindex($index, $n){}
function git_index_get_bypath($index, $path, $stage){}
function git_index_remove($index, $path, $stage){}
function git_index_remove_directory($index, $dir, $stage){}
function git_index_add($index, $source_entry){}
function git_index_entry_stage($entry){}
function git_index_add_bypath($index, $path){}
function git_index_remove_bypath($index, $path){}
function git_index_add_all($index, $pathspec, $flags, $callback, $payload){}
function git_index_remove_all($index, $pathspec, $callback, $payload){}
function git_index_update_all($index, $pathspec, $callback, $payload){}
function git_index_find($at_pos, $index, $path){}
function git_index_conflict_add($index, $ancestor_entry, $our_entry, $their_entry){}
function git_index_conflict_get($our_out, $their_out, $index, $path){}
function git_index_conflict_remove($index, $path){}
function git_index_conflict_cleanup($index){}
function git_index_has_conflicts($index){}
function git_index_conflict_iterator_new($index){}
function git_index_conflict_next($our_out, $their_out, $iterator){}
function git_index_conflict_iterator_free($iterator){}
function git_object_lookup($repo, $id, $type){}
function git_object_lookup_prefix($repo, $id, $len, $type){}
function git_object_lookup_bypath($treeish, $path, $type){}
function git_object_id($obj){}
function git_object_type($obj){}
function git_object_owner($obj){}
function git_object_free($object){}
function git_object_type2string($type){}
function git_object_string2type($str){}
function git_object_typeisloose($type){}
function git_object__size($type){}
function git_object_peel($object, $target_type){}
function git_object_dup($source){}
function git_clone($url, $localpath, $options){}
function git_reference_lookup($repo, $name){}
function git_reference_name_to_id($repo, $name){}
function git_reference_dwim($repo, $shorthand){}
function git_reference_symbolic_create($repo, $name, $target, $force){}
function git_reference_create($repo, $name, $id, $force){}
function git_reference_target($ref){}
function git_reference_target_peel($ref){}
function git_reference_symbolic_target($ref){}
function git_reference_type($ref){}
function git_reference_name($ref){}
function git_reference_resolve($ref){}
function git_reference_owner($ref){}
function git_reference_symbolic_set_target($ref, $target){}
function git_reference_set_target($ref, $id){}
function git_reference_rename($ref, $new_name, $force){}
function git_reference_delete($ref){}
function git_reference_list($array, $repo){}
function git_reference_foreach($repo, $callback, $payload){}
function git_reference_foreach_name($repo, $callback, $payload){}
function git_reference_free($ref){}
function git_reference_cmp($ref1, $ref2){}
function git_reference_iterator_new($repo){}
function git_reference_iterator_glob_new($repo, $glob){}
function git_reference_next($iter){}
function git_reference_next_name($iter){}
function git_reference_iterator_free($iter){}
function git_reference_foreach_glob($repo, $glob, $callback, $payload){}
function git_reference_has_log($ref){}
function git_reference_is_branch($ref){}
function git_reference_is_remote($ref){}
function git_reference_is_tag($ref){}
function git_reference_normalize_name($buffer_size, $name, $flags){}
function git_reference_peel($ref, $type){}
function git_reference_is_valid_name($refname){}
function git_reference_shorthand($ref){}
function git_commit_lookup($repository, $oid){}
function git_commit_author($commit){}
function git_commit_tree($commit){}
function git_commit_lookup_prefix($repo, $id, $len){}
function git_commit_id($commit){}
function git_commit_owner($commit){}
function git_commit_message_encoding($commit){}
function git_commit_message($commit){}
function git_commit_message_raw($commit){}
function git_commit_time($commit){}
function git_commit_time_offset($commit){}
function git_commit_committer($commit){}
function git_commit_raw_header($commit){}
function git_commit_tree_id($commit){}
function git_commit_parentcount($commit){}
function git_commit_parent($commit, $n){}
function git_commit_parent_id($commit, $n){}
function git_commit_nth_gen_ancestor($commit, $n){}
function git_commit_create($repo, $update_ref, $author, $committer, $message_encoding, $message, $tree, $parents){}
function git_tree_free($tree){}
function git_tree_id($tree){}
function git_tree_lookup($repository, $id){}
function git_tree_owner($tree){}
function git_tree_walk($tree, $mode, $callback, $payload){}
function git_tree_entry_byoid($tree, $oid){}
function git_tree_entry_byindex($tree, $index){}
function git_tree_entry_byname($tree, $name){}
function git_tree_entry_bypath($tree, $path){}
function git_tree_entry_id($tree_entry){}
function git_tree_entry_name($tree_entry){}
function git_tree_entry_type($tree_entry){}
function git_tree_entrycount($tree_entry){}
function git_tree_entry_filemode($tree_entry){}
function git_tree_entry_filemode_raw($tree_entry){}
function git_tree_entry_cmp($e1, $e2){}
function git_tree_entry_free($tree_entry){}
function git_tree_entry_dup($tree_entry){}
function git_treebuilder_create($source){}
function git_treebuilder_clear($bld){}
function git_treebuilder_entrycount($bld){}
function git_treebuilder_free($bld){}
function git_treebuilder_get($bld, $filename){}
function git_treebuilder_insert($bld, $filename, $id, $filemode){}
function git_treebuilder_remove($bld, $filename){}
function git_treebuilder_filter($bld, $filter, $payload){}
function git_treebuilder_write($repo, $bld){}
function git_blob_create_frombuffer($repository, $buffer){}
function git_blob_create_fromchunks($repository, $hintpath, $callback, $payload){}
function git_blob_create_fromdisk($repository, $path){}
function git_blob_create_fromworkdir($repository, $relative_path){}
function git_blob_filtered_content($blob, $as_path, $check_for_binary_data){}
function git_blob_free($blob){}
function git_blob_id($blob){}
function git_blob_is_binary($blob){}
function git_blob_lookup($repository, $id){}
function git_blob_lookup_prefix($repository, $id, $length){}
function git_blob_owner($blob){}
function git_blob_rawcontent($blob){}
function git_blob_rawsize($blob){}
function git_revwalk_new($repo){}
function git_revwalk_reset($walker){}
function git_revwalk_push($walk, $id){}
function git_revwalk_push_glob($walk, $glob){}
function git_revwalk_push_head($walk){}
function git_revwalk_hide($walk, $commit_id){}
function git_revwalk_hide_glob($walk, $glob){}
function git_revwalk_hide_head($walk){}
function git_revwalk_push_ref($walk, $refname){}
function git_revwalk_hide_ref($walk, $refname){}
function git_revwalk_next($walk){}
function git_revwalk_sorting($walk, $sort_mode){}
function git_revwalk_push_range($walk, $range){}
function git_revwalk_simplify_first_parent($walk){}
function git_revwalk_free($walk){}
function git_revwalk_repository($walk){}
function git_config_find_global(){}
function git_config_find_xdg($length){}
function git_config_find_system($length){}
function git_config_open_default(){}
function git_config_new(){}
function git_config_add_file_ondisk($cfg, $path, $level, $force){}
function git_config_open_ondisk($path){}
function git_config_open_level($parent, $level){}
function git_config_open_global($config){}
function git_config_refresh($cfg){}
function git_config_free($cfg){}
function git_config_get_entry($cfg, $name){}
function git_config_get_int32($cfg, $name){}
function git_config_get_int64($cfg, $name){}
function git_config_get_bool($cfg, $name){}
function git_config_get_string($cfg, $name){}
function git_config_get_multivar_foreach($cfg, $name, $regexp, $callback, $payload){}
function git_config_multivar_iterator_new($cfg, $name, $regexp){}
function git_config_next($iter){}
function git_config_iterator_free($iter){}
function git_config_set_int32($cfg, $name, $value){}
function git_config_set_int64($cfg, $name, $value){}
function git_config_set_bool($cfg, $name, $value){}
function git_config_set_string($cfg, $name, $value){}
function git_config_set_multivar($cfg, $name, $regexp, $value){}
function git_config_delete_entry($cfg, $name){}
function git_config_delete_multivar($cfg, $name, $regexp){}
function git_config_foreach($cfg, $callback, $payload){}
function git_config_iterator_new($cfg){}
function git_config_iterator_glob_new($cfg, $regexp){}
function git_config_foreach_match($cfg, $regexp, $callback, $payload){}
function git_config_get_mapped($cfg, $name, $maps, $map_n){}
function git_config_lookup_map_value($maps, $map_n, $value){}
function git_config_parse_bool($value){}
function git_config_parse_int32($value){}
function git_config_parse_int64($value){}
function git_config_backend_foreach_match($backend, $regexp){}
function git_revparse_single($repo, $spec){}
function git_revparse_ext($reference_out, $repo, $spec){}
function git_revparse($revspec, $repo, $spec){}
function git_remote_create($repo, $name, $url){}
function git_remote_create_with_fetchspec($repo, $name, $url, $fetch){}
function git_remote_create_inmemory($repo, $fetch, $url){}
function git_remote_load($repo, $name){}
function git_remote_save($remote){}
function git_remote_owner($remote){}
function git_remote_name($remote){}
function git_remote_url($remote){}
function git_remote_pushurl($remote){}
function git_remote_set_url($remote, $url){}
function git_remote_set_pushurl($remote, $url){}
function git_remote_add_fetch($remote, $refspec){}
function git_remote_get_fetch_refspecs($array, $remote){}
function git_remote_set_fetch_refspecs($remote, $array){}
function git_remote_add_push($remote, $refspec){}
function git_remote_get_push_refspecs($array, $remote){}
function git_remote_set_push_refspecs($remote, $array){}
function git_remote_clear_refspecs($remote){}
function git_remote_refspec_count($remote){}
function git_remote_get_refspec($remote, $n){}
function git_remote_connect($remote, $direction){}
function git_remote_ls($remote){}
function git_remote_download($remote){}
function git_remote_connected($remote){}
function git_remote_stop($remote){}
function git_remote_disconnect($remote){}
function git_remote_free($remote){}
function git_remote_update_tips($remote){}
function git_remote_fetch($remote){}
function git_remote_valid_url($url){}
function git_remote_supported_url($url){}
function git_remote_list($repo){}
function git_remote_check_cert($remote, $check){}
function git_remote_set_transport($remote, $transport){}
function git_remote_set_callbacks($remote, $callbacks){}
function git_remote_stats($remote){}
function git_remote_autotag($remote){}
function git_remote_set_autotag($remote, $value){}
function git_remote_rename($remote, $new_name, $callback, $payload){}
function git_remote_update_fetchhead($remote){}
function git_remote_set_update_fetchhead($remote, $value){}
function git_remote_is_valid_name($remote_name){}
function git_cred_has_username($cred){}
function git_cred_userpass_plaintext_new($username, $password){}
function git_cred_ssh_key_new($username, $publickey, $privatekey, $passphrase){}
function git_cred_ssh_custom_new($username, $publickey, $publickey_len, $sign_fn, $sign_data){}
function git_cred_default_new(){}
function git_cred_userpass($url, $user_from_url, $allowed_types, $payload){}
function git_status_foreach($repo, $callback, $payload){}
function git_status_foreach_ext($repo, $opts, $callback, $payload){}
function git_status_file($status_flags, $repo, $path){}
function git_status_list_new($repo, $opts){}
function git_status_list_entrycount($statuslist){}
function git_status_byindex($statuslist, $idx){}
function git_status_list_free($statuslist){}
function git_status_should_ignore($ignored, $repo, $path){}
function git_status_options_new(){}
function git_transport_new($owner, $url){}
function git_transport_register($prefix, $priority, $cb, $param){}
function git_transport_unregister($prefix, $priority){}
function git_transport_dummy($owner, $payload){}
function git_transport_local($owner, $payload){}
function git_transport_smart($owner, $payload){}
function git_smart_subtransport_http($owner){}
function git_smart_subtransport_git($owner){}
function git_smart_subtransport_ssh($owner){}
function git_diff_free($diff){}
function git_diff_tree_to_tree($repo, $old_tree, $new_tree, $opts){}
function git_diff_tree_to_index($repo, $old_tree, $index, $opts){}
function git_diff_index_to_workdir($repo, $index, $opts){}
function git_diff_tree_to_workdir($repo, $old_tree, $opts){}
function git_diff_tree_to_workdir_with_index($repo, $old_tree, $opts){}
function git_diff_merge($onto, $from){}
function git_diff_find_similar($diff, $options){}
function git_diff_options_init($options, $version){}
function git_diff_num_deltas($diff){}
function git_diff_num_deltas_of_type($diff, $type){}
function git_diff_get_delta($diff, $idx){}
function git_diff_is_sorted_icase($diff){}
function git_diff_foreach($diff, $file_cb, $hunk_cb, $line_cb, $payload){}
function git_diff_status_char($status){}
function git_diff_print($diff, $format, $print_cb, $payload){}
function git_diff_blobs($old_blob, $old_as_path, $new_blob, $new_as_path, $options, $file_cb, $hunk_cb, $line_cb, $payload){}
function git_diff_blob_to_buffer($old_blob, $old_as_path, $buffer, $buffer_len, $buffer_as_path, $options, $file_cb, $hunk_cb, $line_cb, $payload){}
function git_checkout_head($repo, $opts){}
function git_checkout_index($repo, $index, $opts){}
function git_checkout_tree($repo, $treeish, $opts){}
function git_checkout_opts_new(){}
function git_filter_list_load($repo, $blob, $path, $mode){}
function git_filter_list_apply_to_data($filters, $in){}
function git_filter_list_apply_to_file($filters, $repo, $path){}
function git_filter_list_apply_to_blob($filters, $blob){}
function git_filter_list_free($filters){}
function git_filter_lookup($name){}
function git_filter_list_new($repo, $mode){}
function git_filter_list_push($fl, $filter, $payload){}
function git_filter_list_length($fl){}
function git_filter_source_repo($src){}
function git_filter_source_path($src){}
function git_filter_source_filemode($src){}
function git_filter_source_id($src){}
function git_filter_source_mode($src){}
function git_filter_register($name, $filter, $priority){}
function git_filter_unregister($name){}
function git_filter_new($payload){}
function git_ignore_add_rule($repo, $rules){}
function git_ignore_clear_internal_rules($repo){}
function git_ignore_path_is_ignored($ignored, $repo, $path){}
function git_indexer_new($out, $path, $mode, $odb, $progress_cb, $progress_cb_payload){}
function git_indexer_append($idx, $data, $size, $stats){}
function git_indexer_commit($idx, $stats){}
function git_indexer_hash($idx){}
function git_indexer_free($idx){}
function git_pathspec_new($pathspec){}
function git_pathspec_free($ps){}
function git_pathspec_matches_path($ps, $flags, $path){}
function git_pathspec_match_workdir($repo, $flags, $ps){}
function git_pathspec_match_index($index, $flags, $ps){}
function git_pathspec_match_tree($tree, $flags, $ps){}
function git_pathspec_match_diff($diff, $flags, $ps){}
function git_pathspec_match_list_free($m){}
function git_pathspec_match_list_entrycount($m){}
function git_pathspec_match_list_entry($m, $pos){}
function git_pathspec_match_list_diff_entry($m, $pos){}
function git_pathspec_match_list_failed_entrycount($m){}
function git_pathspec_match_list_failed_entry($m, $pos){}
function git_patch_from_diff($diff, $idx){}
function git_patch_from_blobs($old_blob, $old_as_path, $new_blob, $new_as_path, $opts){}
function git_patch_from_blob_and_buffer($old_blob, $old_as_path, $buffer, $buffer_len, $buffer_as_path, $opts){}
function git_patch_free($patch){}
function git_patch_get_delta($patch){}
function git_patch_num_hunks($patch){}
function git_patch_line_stats($total_context, $total_additions, $total_deletions, $patch){}
function git_patch_get_hunk($lines_in_hunk, $patch, $hunk_idx){}
function git_patch_num_lines_in_hunk($patch, $hunk_idx){}
function git_patch_get_line_in_hunk($patch, $hunk_idx, $line_of_hunk){}
function git_patch_size($patch, $include_context, $include_hunk_headers, $include_file_headers){}
function git_patch_print($patch, $print_cb, $payload){}
function git_patch_to_str($patch){}
function git_merge_base($repo, $one, $two){}
function git_merge_base_many($repo, $length, $input_array[]){}
function git_merge_head_from_ref($repo, $ref){}
function git_merge_head_from_fetchhead($repo, $branch_name, $remote_url, $oid){}
function git_merge_head_from_oid($repo, $oid){}
function git_merge_head_free($head){}
function git_merge_trees($repo, $ancestor_tree, $our_tree, $their_tree, $opts){}
function git_merge($repo, $their_heads, $their_heads_len, $opts){}
function git_merge_result_is_uptodate($merge_result){}
function git_merge_result_is_fastforward($merge_result){}
function git_merge_result_fastforward_oid($merge_result){}
function git_merge_result_free($merge_result){}
function git_tag_lookup($repo, $id){}
function git_tag_lookup_prefix($repo, $id, $len){}
function git_tag_free($tag){}
function git_tag_id($tag){}
function git_tag_owner($tag){}
function git_tag_target($tag){}
function git_tag_target_id($tag){}
function git_tag_target_type($tag){}
function git_tag_name($tag){}
function git_tag_tagger($tag){}
function git_tag_message($tag){}
function git_tag_create($repo, $tag_name, $target, $tagger, $message, $force){}
function git_tag_annotation_create($repo, $tag_name, $target, $tagger, $message){}
function git_tag_create_frombuffer($repo, $buffer, $force){}
function git_tag_create_lightweight($repo, $tag_name, $target, $force){}
function git_tag_delete($repo, $tag_name){}
function git_tag_list($tag_names, $repo){}
function git_tag_list_match($tag_names, $pattern, $repo){}
function git_tag_foreach($repo, $callback, $payload){}
function git_tag_peel($tag){}
function git_note_iterator_new($repo, $notes_ref){}
function git_note_iterator_free($it){}
function git_note_next($note_id, $annotated_id, $it){}
function git_note_read($repo, $notes_ref, $oid){}
function git_note_message($note){}
function git_note_oid($note){}
function git_note_create($repo, $author, $committer, $notes_ref, $oid, $note, $force){}
function git_note_remove($repo, $notes_ref, $author, $committer, $oid){}
function git_note_free($note){}
function git_note_default_ref($repo){}
function git_note_foreach($repo, $notes_ref, $note_cb, $payload){}
function git_odb_new(){}
function git_odb_open($objects_dir){}
function git_odb_add_disk_alternate($odb, $path){}
function git_odb_free($db){}
function git_odb_read($db, $id){}
function git_odb_read_prefix($db, $short_id, $len){}
function git_odb_read_header($type_out, $db, $id){}
function git_odb_exists($db, $id){}
function git_odb_refresh($db){}
function git_odb_foreach($db, $cb, $payload){}
function git_odb_write($odb, $data, $len, $type){}
function git_odb_open_wstream($db, $size, $type){}
function git_odb_stream_write($buffer, $len){}
function git_odb_stream_finalize_write($stream){}
function git_odb_stream_read($stream, $buffer, $len){}
function git_odb_stream_free($stream){}
function git_odb_open_rstream($db, $oid){}
function git_odb_write_pack($db, $progress_cb, $progress_payload){}
function git_odb_hash($data, $len, $type){}
function git_odb_hashfile($path, $type){}
function git_odb_object_dup($source){}
function git_odb_object_free($object){}
function git_odb_object_id($object){}
function git_odb_object_data($object){}
function git_odb_object_size($object){}
function git_odb_object_type($object){}
function git_odb_add_backend($odb, $backend, $priority){}
function git_odb_add_alternate($odb, $backend, $priority){}
function git_odb_num_backends($odb){}
function git_odb_get_backend($odb, $pos){}
function git_odb_backend_new($callbacks){}
function git_reflog_read($repo, $name){}
function git_reflog_write(){}
function git_reflog_append($reflog, $id, $committer, $msg){}
function git_reflog_append_to($repo, $name, $id, $committer, $msg){}
function git_reflog_rename($repo, $old_name, $name){}
function git_reflog_delete($repo, $name){}
function git_reflog_entrycount($reflog){}
function git_reflog_entry_byindex($reflog, $idx){}
function git_reflog_drop($reflog, $idx, $rewrite_previous_entry){}
function git_reflog_entry_id_old($entry){}
function git_reflog_entry_id_new(){}
function git_reflog_entry_committer($entry){}
function git_reflog_entry_message($entry){}
function git_reflog_free($reflog){}
function git_packbuilder_new($repo){}
function git_packbuilder_set_threads($pb, $n){}
function git_packbuilder_insert($pb, $id, $name){}
function git_packbuilder_insert_tree($pb, $id){}
function git_packbuilder_insert_commit($pb, $id){}
function git_packbuilder_write($pb, $path, $mode, $progress_cb, $progress_cb_payload){}
function git_packbuilder_hash($pb){}
function git_packbuilder_foreach($pb, $cb, $payload){}
function git_packbuilder_object_count($pb){}
function git_packbuilder_written($pb){}
function git_packbuilder_set_callbacks($pb, $progress_cb, $progress_cb_payload){}
function git_packbuilder_free($pb){}
function git_stash_save($repo, $stasher, $message, $flags){}
function git_stash_foreach($repo, $callback, $payload){}
function git_stash_drop($repo, $index){}
function git_signature_new($name, $email, $time, $offset){}
function git_signature_now($name, $email){}
function git_signature_default($repo){}
function git_reset($repo, $target, $reset_type){}
function git_reset_default($repo, $target, $pathspecs){}
function git_message_prettify($out_size, $message, $strip_comments){}
function git_submodule_lookup($repo, $name){}
function git_submodule_foreach($repo, $callback, $payload){}
function git_submodule_add_setup($repo, $url, $path, $use_gitlink){}
function git_submodule_add_finalize($submodule){}
function git_submodule_add_to_index($submodule, $write_index){}
function git_submodule_save($submodule){}
function git_submodule_owner($submodule){}
function git_submodule_name($submodule){}
function git_submodule_path($submodule){}
function git_submodule_url($submodule){}
function git_submodule_set_url($submodule, $url){}
function git_submodule_index_id($submodule){}
function git_submodule_head_id($submodule){}
function git_submodule_wd_id($submodule){}
function git_submodule_ignore($submodule){}
function git_submodule_set_ignore($submodule, $ignore){}
function git_submodule_update($submodule){}
function git_submodule_set_update($submodule, $update){}
function git_submodule_fetch_recurse_submodules($submodule){}
function git_submodule_set_fetch_recurse_submodules($submodule, $fetch_recurse_submodules){}
function git_submodule_init($submodule, $overwrite){}
function git_submodule_sync($submodule){}
function git_submodule_open($submodule){}
function git_submodule_reload($submodule){}
function git_submodule_reload_all($repo){}
function git_submodule_status($status, $submodule){}
function git_submodule_location($location_status, $submodule){}
function git_attr_value($attr){}
function git_attr_get($repo, $flags, $path, $name){}
function git_attr_get_many($repo, $flags, $path, $num_attr, $names){}
function git_attr_foreach($repo, $flags, $path, $callback, $payload){}
function git_attr_cache_flush($repo){}
function git_attr_add_macro($repo, $name, $values){}
function giterr_last($void){}
function giterr_clear($void){}
function giterr_detach($cpy){}
function giterr_set_str($error_class, $string){}
function giterr_set_oom($void){}
function git_push_new($remote){}
function git_push_set_options($push, $opts){}
function git_push_set_callbacks($push, $pack_progress_cb, $pack_progress_cb_payload, $transfer_progress_cb, $transfer_progress_cb_payload){}
function git_push_add_refspec($push, $refspec){}
function git_push_update_tips($push){}
function git_push_finish($push){}
function git_push_unpack_ok($push){}
function git_push_status_foreach($push, $callback, $data){}
function git_push_free($push){}
function git_refspec_src($refspec){}
function git_refspec_dst($refspec){}
function git_refspec_string($refspec){}
function git_refspec_force($refspec){}
function git_refspec_direction($spec){}
function git_refspec_src_matches($refspec, $refname){}
function git_refspec_dst_matches($refspec, $refname){}
function git_refspec_transform($out, $outlen, $spec, $name){}
function git_refspec_rtransform($out, $outlen, $spec, $name){}
function git_graph_ahead_behind($repo, $local, $upstream){}
function git_blame_get_hunk_count($blame){}
function git_blame_get_hunk_byindex($blame, $index){}
function git_blame_get_hunk_byline($blame, $lineno){}
function git_blame_file($repo, $path, $options){}
function git_blame_buffer($reference, $buffer, $buffer_len){}
function git_blame_free($blame){}
function git_blame_options_new(){}
function git_resource_type($resource){}
function git_libgit2_capabilities(){}
function git_libgit2_version(){}
