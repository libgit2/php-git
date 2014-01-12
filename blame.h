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
#ifndef PHP_GIT2_BLAME_H
#define PHP_GIT2_BLAME_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blame_get_hunk_count, 0, 0, 1)
	ZEND_ARG_INFO(0, blame)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blame_get_hunk_byindex, 0, 0, 2)
	ZEND_ARG_INFO(0, blame)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blame_get_hunk_byline, 0, 0, 2)
	ZEND_ARG_INFO(0, blame)
	ZEND_ARG_INFO(0, lineno)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blame_file, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blame_buffer, 0, 0, 3)
	ZEND_ARG_INFO(0, reference)
	ZEND_ARG_INFO(0, buffer)
	ZEND_ARG_INFO(0, buffer_len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blame_free, 0, 0, 1)
	ZEND_ARG_INFO(0, blame)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_blame_get_hunk_count(blame)
*/
PHP_FUNCTION(git_blame_get_hunk_count);

/* {{{ proto resource git_blame_get_hunk_byindex(blame, index)
*/
PHP_FUNCTION(git_blame_get_hunk_byindex);

/* {{{ proto resource git_blame_get_hunk_byline(blame, lineno)
*/
PHP_FUNCTION(git_blame_get_hunk_byline);

/* {{{ proto resource git_blame_file(repo, path, options)
*/
PHP_FUNCTION(git_blame_file);

/* {{{ proto resource git_blame_buffer(reference, buffer, buffer_len)
*/
PHP_FUNCTION(git_blame_buffer);

/* {{{ proto void git_blame_free(blame)
*/
PHP_FUNCTION(git_blame_free);

#endif