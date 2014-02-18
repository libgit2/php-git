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
#ifndef PHP_GIT2_SIGNATURE_H
#define PHP_GIT2_SIGNATURE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature_new, 0, 0, 4)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, email)
	ZEND_ARG_INFO(0, time)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature_now, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, email)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature_default, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature_dup, 0, 0, 1)
	ZEND_ARG_INFO(0, sig)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_signature_free, 0, 0, 1)
	ZEND_ARG_INFO(0, sig)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_signature_new(name, email, time, offset)
*/
PHP_FUNCTION(git_signature_new);

/* {{{ proto resource git_signature_now(name, email)
*/
PHP_FUNCTION(git_signature_now);

/* {{{ proto resource git_signature_default(repo)
*/
PHP_FUNCTION(git_signature_default);

/* {{{ proto resource git_signature_dup(sig)
*/
PHP_FUNCTION(git_signature_dup);

/* {{{ proto void git_signature_free(sig)
*/
PHP_FUNCTION(git_signature_free);

#endif