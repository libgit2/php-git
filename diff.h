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
#ifndef PHP_GIT2_DIFF_H
#define PHP_GIT2_DIFF_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_free, 0, 0, 1)
	ZEND_ARG_INFO(0, diff)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_tree_to_tree, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, old_tree)
	ZEND_ARG_INFO(0, new_tree)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_tree_to_index, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, old_tree)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_index_to_workdir, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_tree_to_workdir, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, old_tree)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_tree_to_workdir_with_index, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, old_tree)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_merge, 0, 0, 2)
	ZEND_ARG_INFO(0, onto)
	ZEND_ARG_INFO(0, from)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_find_similar, 0, 0, 2)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_options_init, 0, 0, 2)
	ZEND_ARG_INFO(0, options)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_num_deltas, 0, 0, 1)
	ZEND_ARG_INFO(0, diff)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_num_deltas_of_type, 0, 0, 2)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_get_delta, 0, 0, 2)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, idx)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_is_sorted_icase, 0, 0, 1)
	ZEND_ARG_INFO(0, diff)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_foreach, 0, 0, 5)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, file_cb)
	ZEND_ARG_INFO(0, hunk_cb)
	ZEND_ARG_INFO(0, line_cb)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_status_char, 0, 0, 1)
	ZEND_ARG_INFO(0, status)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_print, 0, 0, 4)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, print_cb)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_blobs, 0, 0, 9)
	ZEND_ARG_INFO(0, old_blob)
	ZEND_ARG_INFO(0, old_as_path)
	ZEND_ARG_INFO(0, new_blob)
	ZEND_ARG_INFO(0, new_as_path)
	ZEND_ARG_INFO(0, options)
	ZEND_ARG_INFO(0, file_cb)
	ZEND_ARG_INFO(0, hunk_cb)
	ZEND_ARG_INFO(0, line_cb)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_diff_blob_to_buffer, 0, 0, 10)
	ZEND_ARG_INFO(0, old_blob)
	ZEND_ARG_INFO(0, old_as_path)
	ZEND_ARG_INFO(0, buffer)
	ZEND_ARG_INFO(0, buffer_len)
	ZEND_ARG_INFO(0, buffer_as_path)
	ZEND_ARG_INFO(0, options)
	ZEND_ARG_INFO(0, file_cb)
	ZEND_ARG_INFO(0, hunk_cb)
	ZEND_ARG_INFO(0, line_cb)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

/* {{{ proto void git_diff_free(diff)
*/
PHP_FUNCTION(git_diff_free);

/* {{{ proto resource git_diff_tree_to_tree(repo, old_tree, new_tree, opts)
*/
PHP_FUNCTION(git_diff_tree_to_tree);

/* {{{ proto resource git_diff_tree_to_index(repo, old_tree, index, opts)
*/
PHP_FUNCTION(git_diff_tree_to_index);

/* {{{ proto resource git_diff_index_to_workdir(repo, index, opts)
*/
PHP_FUNCTION(git_diff_index_to_workdir);

/* {{{ proto resource git_diff_tree_to_workdir(repo, old_tree, opts)
*/
PHP_FUNCTION(git_diff_tree_to_workdir);

/* {{{ proto resource git_diff_tree_to_workdir_with_index(repo, old_tree, opts)
*/
PHP_FUNCTION(git_diff_tree_to_workdir_with_index);

/* {{{ proto long git_diff_merge(onto, from)
*/
PHP_FUNCTION(git_diff_merge);

/* {{{ proto long git_diff_find_similar(diff, options)
*/
PHP_FUNCTION(git_diff_find_similar);

/* {{{ proto long git_diff_options_init(options, version)
*/
PHP_FUNCTION(git_diff_options_init);

/* {{{ proto resource git_diff_num_deltas(diff)
*/
PHP_FUNCTION(git_diff_num_deltas);

/* {{{ proto resource git_diff_num_deltas_of_type(diff, type)
*/
PHP_FUNCTION(git_diff_num_deltas_of_type);

/* {{{ proto resource git_diff_get_delta(diff, idx)
*/
PHP_FUNCTION(git_diff_get_delta);

/* {{{ proto long git_diff_is_sorted_icase(diff)
*/
PHP_FUNCTION(git_diff_is_sorted_icase);

/* {{{ proto long git_diff_foreach(diff, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_foreach);

/* {{{ proto resource git_diff_status_char(status)
*/
PHP_FUNCTION(git_diff_status_char);

/* {{{ proto long git_diff_print(diff, format, print_cb, payload)
*/
PHP_FUNCTION(git_diff_print);

/* {{{ proto long git_diff_blobs(old_blob, old_as_path, new_blob, new_as_path, options, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_blobs);

/* {{{ proto long git_diff_blob_to_buffer(old_blob, old_as_path, buffer, buffer_len, buffer_as_path, options, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_blob_to_buffer);


#endif