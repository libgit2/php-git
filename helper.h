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
#ifndef PHP_GIT2_HELPER_H
#define PHP_GIT2_HELPER_H

/* NOTE(chobie): all functions should have `php_git2_` prefix */

int php_git2_check_error(int error_code, const char *action TSRMLS_DC);

zval* php_git2_read_arrval(zval *array, char *name, size_t name_len TSRMLS_DC);

long php_git2_read_arrval_long2(zval *array, char *name, size_t name_len, long value TSRMLS_DC);

long php_git2_read_arrval_long(zval *array, char *name, size_t name_len TSRMLS_DC);

const char* php_git2_read_arrval_string(zval *array, char *name, size_t name_len TSRMLS_DC);

void php_git2_array_to_signature(git_signature *signature, zval *author TSRMLS_DC);

void php_git2_signature_to_array(const git_signature *signature, zval **out TSRMLS_DC);

void php_git2_strarray_to_array(git_strarray *array, zval **out TSRMLS_DC);

int php_git2_call_function_v(
	zend_fcall_info *fci, zend_fcall_info_cache *fcc TSRMLS_DC, zval **retval_ptr_ptr, zend_uint param_count, ...);

int php_git2_cb_init(php_git2_cb_t **out, zend_fcall_info *fci, zend_fcall_info_cache *fcc, void *payload TSRMLS_DC);

void php_git2_cb_free(php_git2_cb_t *target);

void php_git2_array_to_strarray(git_strarray *out, zval *array TSRMLS_DC);

void php_git2_strarray_free(git_strarray *out);

void php_git2_git_checkout_opts_to_array(git_checkout_opts *opts, zval **out TSRMLS_DC);

void php_git_git_checkout_opts_free(git_checkout_opts *target TSRMLS_DC);

int php_git2_array_to_git_checkout_opts(git_checkout_opts **out, zval *array TSRMLS_DC);

int php_git2_multi_cb_init(php_git2_multi_cb_t **out, void *payload TSRMLS_DC, int num_callbacks, ...);

void php_git2_multi_cb_free(php_git2_multi_cb_t *target);

void php_git2_diff_line_to_array(git_diff_line *line, zval **out TSRMLS_DC);

void php_git2_diff_hunk_to_array(git_diff_hunk *hunk, zval **out TSRMLS_DC);

void php_git2_diff_file_to_array(git_diff_file *file, zval **out TSRMLS_DC);

void php_git2_diff_delta_to_array(git_diff_delta *delta, zval **out TSRMLS_DC);

void php_git2_array_to_git_diff_options(git_diff_options *options, zval *array TSRMLS_DC);

void php_git2_git_diff_options_free(git_diff_options *options);

void php_git2_git_diff_options_to_array(git_diff_options *options, zval **out TSRMLS_DC);

int php_git2_git_diff_file_cb(
	const git_diff_delta *delta,
	float progress,
	void *payload);

int php_git2_git_diff_hunk_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	void *payload);
int php_git2_git_diff_line_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *payload);

void php_git2_git_transfer_progress_to_array(git_transfer_progress *progress, zval **out TSRMLS_DC);

void php_git2_fcall_info_wrapper(zval *target, zend_fcall_info **out_fci, zend_fcall_info_cache **out_fcc TSRMLS_DC);

void php_git2_fcall_info_wrapper2(zval *target, zend_fcall_info *fci, zend_fcall_info_cache *fcc TSRMLS_DC);

#endif