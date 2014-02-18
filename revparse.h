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
#ifndef PHP_GIT2_REVPARSE_H
#define PHP_GIT2_REVPARSE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revparse_single, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revparse_ext, 0, 0, 3)
	ZEND_ARG_INFO(0, reference_out)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revparse, 0, 0, 3)
	ZEND_ARG_INFO(0, revspec)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, spec)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_revparse_single(repo, spec)
*/
PHP_FUNCTION(git_revparse_single);

/* {{{ proto resource git_revparse_ext(reference_out, repo, spec)
*/
PHP_FUNCTION(git_revparse_ext);

/* {{{ proto long git_revparse(revspec, repo, spec)
*/
PHP_FUNCTION(git_revparse);

#endif