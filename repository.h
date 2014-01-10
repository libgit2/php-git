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
#ifndef PHP_GIT2_REPOSITORY_H
#define PHP_GIT2_REPOSITORY_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_new, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_init, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, is_bare)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_open_bare, 0, 0, 1)
	ZEND_ARG_INFO(0, bare_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_open, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_get_namespace, 0, 0, 1)
	ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_workdir, 0, 0, 1)
	ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_repository_new()
*/
PHP_FUNCTION(git_repository_new);

/* {{{ proto resource git_repository_init(string $path, long is_bare = 0)
*/
PHP_FUNCTION(git_repository_init);

/* {{{ proto resource git_repository_open(string $path)
*/
PHP_FUNCTION(git_repository_open_bare);

/* {{{ proto resource git_repository_open(string $path)
*/
PHP_FUNCTION(git_repository_open);

/* {{{ proto string git_repository_get_namespace(resource $repository)
*/
PHP_FUNCTION(git_repository_get_namespace);

/* {{{ proto string git_repository_workdir(resource $repository)
*/
PHP_FUNCTION(git_repository_workdir);

#endif