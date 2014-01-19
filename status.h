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
#ifndef PHP_GIT2_STATUS_H
#define PHP_GIT2_STATUS_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_foreach_ext, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, opts)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_file, 0, 0, 3)
	ZEND_ARG_INFO(0, status_flags)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_list_new, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_list_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, statuslist)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_byindex, 0, 0, 2)
	ZEND_ARG_INFO(0, statuslist)
	ZEND_ARG_INFO(0, idx)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_list_free, 0, 0, 1)
	ZEND_ARG_INFO(0, statuslist)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_status_should_ignore, 0, 0, 3)
	ZEND_ARG_INFO(0, ignored)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

/* {{{ proto long git_status_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_status_foreach);

/* {{{ proto long git_status_foreach_ext(repo, opts, callback, payload)
*/
PHP_FUNCTION(git_status_foreach_ext);

/* {{{ proto long git_status_file(status_flags, repo, path)
*/
PHP_FUNCTION(git_status_file);

/* {{{ proto resource git_status_list_new(repo, opts)
*/
PHP_FUNCTION(git_status_list_new);

/* {{{ proto resource git_status_list_entrycount(statuslist)
*/
PHP_FUNCTION(git_status_list_entrycount);

/* {{{ proto resource git_status_byindex(statuslist, idx)
*/
PHP_FUNCTION(git_status_byindex);

/* {{{ proto void git_status_list_free(statuslist)
*/
PHP_FUNCTION(git_status_list_free);

/* {{{ proto long git_status_should_ignore(ignored, repo, path)
*/
PHP_FUNCTION(git_status_should_ignore);

PHP_FUNCTION(git_status_options_new);

#endif