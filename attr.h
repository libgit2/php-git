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
#ifndef PHP_GIT2_ATTR_H
#define PHP_GIT2_ATTR_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_attr_value, 0, 0, 1)
	ZEND_ARG_INFO(0, attr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_attr_get, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_attr_get_many, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, num_attr)
	ZEND_ARG_INFO(0, names)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_attr_foreach, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_attr_cache_flush, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_attr_add_macro, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, values)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_attr_value(attr)
*/
PHP_FUNCTION(git_attr_value);

/* {{{ proto resource git_attr_get(repo, flags, path, name)
*/
PHP_FUNCTION(git_attr_get);

/* {{{ proto resource git_attr_get_many(repo, flags, path, num_attr, names)
*/
PHP_FUNCTION(git_attr_get_many);

/* {{{ proto long git_attr_foreach(repo, flags, path, callback, payload)
*/
PHP_FUNCTION(git_attr_foreach);

/* {{{ proto void git_attr_cache_flush(repo)
*/
PHP_FUNCTION(git_attr_cache_flush);

/* {{{ proto long git_attr_add_macro(repo, name, values)
*/
PHP_FUNCTION(git_attr_add_macro);

#endif