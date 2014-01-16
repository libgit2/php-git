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
#ifndef PHP_GIT2_FILTER_H
#define PHP_GIT2_FILTER_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_load, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, blob)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_apply_to_data, 0, 0, 2)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_INFO(0, in)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_apply_to_file, 0, 0, 3)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_apply_to_blob, 0, 0, 2)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_free, 0, 0, 1)
	ZEND_ARG_INFO(0, filters)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_lookup, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_new, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_push, 0, 0, 3)
	ZEND_ARG_INFO(0, fl)
	ZEND_ARG_INFO(0, filter)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_list_length, 0, 0, 1)
	ZEND_ARG_INFO(0, fl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_source_repo, 0, 0, 1)
	ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_source_path, 0, 0, 1)
	ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_source_filemode, 0, 0, 1)
	ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_source_id, 0, 0, 1)
	ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_source_mode, 0, 0, 1)
	ZEND_ARG_INFO(0, src)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_register, 0, 0, 3)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, filter)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_filter_unregister, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_filter_list_load(repo, blob, path, mode)
*/
PHP_FUNCTION(git_filter_list_load);

/* {{{ proto resource git_filter_list_apply_to_data(filters, in)
*/
PHP_FUNCTION(git_filter_list_apply_to_data);

/* {{{ proto resource git_filter_list_apply_to_file(filters, repo, path)
*/
PHP_FUNCTION(git_filter_list_apply_to_file);

/* {{{ proto resource git_filter_list_apply_to_blob(filters, blob)
*/
PHP_FUNCTION(git_filter_list_apply_to_blob);

/* {{{ proto void git_filter_list_free(filters)
*/
PHP_FUNCTION(git_filter_list_free);

/* {{{ proto resource git_filter_lookup(name)
*/
PHP_FUNCTION(git_filter_lookup);

/* {{{ proto resource git_filter_list_new(repo, mode)
*/
PHP_FUNCTION(git_filter_list_new);

/* {{{ proto long git_filter_list_push(fl, filter, payload)
*/
PHP_FUNCTION(git_filter_list_push);

/* {{{ proto resource git_filter_list_length(fl)
*/
PHP_FUNCTION(git_filter_list_length);

/* {{{ proto resource git_filter_source_repo(src)
*/
PHP_FUNCTION(git_filter_source_repo);

/* {{{ proto resource git_filter_source_path(src)
*/
PHP_FUNCTION(git_filter_source_path);

/* {{{ proto resource git_filter_source_filemode(src)
*/
PHP_FUNCTION(git_filter_source_filemode);

/* {{{ proto resource git_filter_source_id(src)
*/
PHP_FUNCTION(git_filter_source_id);

/* {{{ proto resource git_filter_source_mode(src)
*/
PHP_FUNCTION(git_filter_source_mode);

/* {{{ proto long git_filter_register(name, filter, priority)
*/
PHP_FUNCTION(git_filter_register);

/* {{{ proto long git_filter_unregister(name)
*/
PHP_FUNCTION(git_filter_unregister);

#endif
