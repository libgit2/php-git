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
#ifndef PHP_GIT2_PATCH_H
#define PHP_GIT2_PATCH_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_from_diff, 0, 0, 2)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, idx)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_from_blobs, 0, 0, 5)
	ZEND_ARG_INFO(0, old_blob)
	ZEND_ARG_INFO(0, old_as_path)
	ZEND_ARG_INFO(0, new_blob)
	ZEND_ARG_INFO(0, new_as_path)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_from_blob_and_buffer, 0, 0, 6)
	ZEND_ARG_INFO(0, old_blob)
	ZEND_ARG_INFO(0, old_as_path)
	ZEND_ARG_INFO(0, buffer)
	ZEND_ARG_INFO(0, buffer_len)
	ZEND_ARG_INFO(0, buffer_as_path)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_free, 0, 0, 1)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_get_delta, 0, 0, 1)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_num_hunks, 0, 0, 1)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_line_stats, 0, 0, 4)
	ZEND_ARG_INFO(0, total_context)
	ZEND_ARG_INFO(0, total_additions)
	ZEND_ARG_INFO(0, total_deletions)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_get_hunk, 0, 0, 3)
	ZEND_ARG_INFO(0, lines_in_hunk)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, hunk_idx)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_num_lines_in_hunk, 0, 0, 2)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, hunk_idx)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_get_line_in_hunk, 0, 0, 3)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, hunk_idx)
	ZEND_ARG_INFO(0, line_of_hunk)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_size, 0, 0, 4)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, include_context)
	ZEND_ARG_INFO(0, include_hunk_headers)
	ZEND_ARG_INFO(0, include_file_headers)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_print, 0, 0, 3)
	ZEND_ARG_INFO(0, patch)
	ZEND_ARG_INFO(0, print_cb)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_patch_to_str, 0, 0, 1)
	ZEND_ARG_INFO(0, patch)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_patch_from_diff(diff, idx)
*/
PHP_FUNCTION(git_patch_from_diff);

/* {{{ proto resource git_patch_from_blobs(old_blob, old_as_path, new_blob, new_as_path, opts)
*/
PHP_FUNCTION(git_patch_from_blobs);

/* {{{ proto resource git_patch_from_blob_and_buffer(old_blob, old_as_path, buffer, buffer_len, buffer_as_path, opts)
*/
PHP_FUNCTION(git_patch_from_blob_and_buffer);

/* {{{ proto void git_patch_free(patch)
*/
PHP_FUNCTION(git_patch_free);

/* {{{ proto resource git_patch_get_delta(patch)
*/
PHP_FUNCTION(git_patch_get_delta);

/* {{{ proto resource git_patch_num_hunks(patch)
*/
PHP_FUNCTION(git_patch_num_hunks);

/* {{{ proto long git_patch_line_stats(total_context, total_additions, total_deletions, patch)
*/
PHP_FUNCTION(git_patch_line_stats);

/* {{{ proto resource git_patch_get_hunk(lines_in_hunk, patch, hunk_idx)
*/
PHP_FUNCTION(git_patch_get_hunk);

/* {{{ proto long git_patch_num_lines_in_hunk(patch, hunk_idx)
*/
PHP_FUNCTION(git_patch_num_lines_in_hunk);

/* {{{ proto resource git_patch_get_line_in_hunk(patch, hunk_idx, line_of_hunk)
*/
PHP_FUNCTION(git_patch_get_line_in_hunk);

/* {{{ proto resource git_patch_size(patch, include_context, include_hunk_headers, include_file_headers)
*/
PHP_FUNCTION(git_patch_size);

/* {{{ proto long git_patch_print(patch, print_cb, payload)
*/
PHP_FUNCTION(git_patch_print);

/* {{{ proto resource git_patch_to_str(patch)
*/
PHP_FUNCTION(git_patch_to_str);

#endif