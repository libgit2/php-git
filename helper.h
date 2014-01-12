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

long php_git2_read_arrval_long(zval *array, char *name, size_t name_len TSRMLS_DC);

const char* php_git2_read_arrval_string(zval *array, char *name, size_t name_len TSRMLS_DC);

void php_git2_array_to_signature(git_signature *signature, zval *author TSRMLS_DC);

void php_git2_signature_to_array(const git_signature *signature, zval **out TSRMLS_DC);

void php_git2_strarray_to_array(git_strarray *array, zval **out TSRMLS_DC);

int php_git2_make_resource(php_git2_t **out, enum php_git2_resource_type type, void *resource, int should_free TSRMLS_DC);

int php_git2_call_function_v(
	zend_fcall_info *fci, zend_fcall_info_cache *fcc TSRMLS_DC, zval **retval_ptr_ptr, zend_uint param_count, ...);

#endif