#include "php_git2.h"
#include "php_git2_priv.h"
#include "diff.h"

/* {{{ proto void git_diff_free(diff)
*/
PHP_FUNCTION(git_diff_free)
{
}

/* {{{ proto resource git_diff_tree_to_tree(repo, old_tree, new_tree, opts)
*/
PHP_FUNCTION(git_diff_tree_to_tree)
{
}

/* {{{ proto resource git_diff_tree_to_index(repo, old_tree, index, opts)
*/
PHP_FUNCTION(git_diff_tree_to_index)
{
}

/* {{{ proto resource git_diff_index_to_workdir(repo, index, opts)
*/
PHP_FUNCTION(git_diff_index_to_workdir)
{
}

/* {{{ proto resource git_diff_tree_to_workdir(repo, old_tree, opts)
*/
PHP_FUNCTION(git_diff_tree_to_workdir)
{
}

/* {{{ proto resource git_diff_tree_to_workdir_with_index(repo, old_tree, opts)
*/
PHP_FUNCTION(git_diff_tree_to_workdir_with_index)
{
}

/* {{{ proto long git_diff_merge(onto, from)
*/
PHP_FUNCTION(git_diff_merge)
{
}

/* {{{ proto long git_diff_find_similar(diff, options)
*/
PHP_FUNCTION(git_diff_find_similar)
{
}

/* {{{ proto long git_diff_options_init(options, version)
*/
PHP_FUNCTION(git_diff_options_init)
{
}

/* {{{ proto resource git_diff_num_deltas(diff)
*/
PHP_FUNCTION(git_diff_num_deltas)
{
}

/* {{{ proto resource git_diff_num_deltas_of_type(diff, type)
*/
PHP_FUNCTION(git_diff_num_deltas_of_type)
{
}

/* {{{ proto resource git_diff_get_delta(diff, idx)
*/
PHP_FUNCTION(git_diff_get_delta)
{
}

/* {{{ proto long git_diff_is_sorted_icase(diff)
*/
PHP_FUNCTION(git_diff_is_sorted_icase)
{
}

/* {{{ proto long git_diff_foreach(diff, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_foreach)
{
}

/* {{{ proto resource git_diff_status_char(status)
*/
PHP_FUNCTION(git_diff_status_char)
{
}

/* {{{ proto long git_diff_print(diff, format, print_cb, payload)
*/
PHP_FUNCTION(git_diff_print)
{
}

/* {{{ proto long git_diff_blobs(old_blob, old_as_path, new_blob, new_as_path, options, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_blobs)
{
}

/* {{{ proto long git_diff_blob_to_buffer(old_blob, old_as_path, buffer, buffer_len, buffer_as_path, options, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_blob_to_buffer)
{
}

