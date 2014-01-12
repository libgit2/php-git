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
#ifndef PHP_GIT2_TREEBUILDER_H
#define PHP_GIT2_TREEBUILDER_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_create, 0, 0, 1)
	ZEND_ARG_INFO(0, source)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_clear, 0, 0, 1)
	ZEND_ARG_INFO(0, bld)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, bld)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_free, 0, 0, 1)
	ZEND_ARG_INFO(0, bld)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_get, 0, 0, 2)
	ZEND_ARG_INFO(0, bld)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_insert, 0, 0, 4)
	ZEND_ARG_INFO(0, bld)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, filemode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_remove, 0, 0, 2)
	ZEND_ARG_INFO(0, bld)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_filter, 0, 0, 3)
	ZEND_ARG_INFO(0, bld)
	ZEND_ARG_INFO(0, filter)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_treebuilder_write, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, bld)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_treebuilder_create(source)
*/
PHP_FUNCTION(git_treebuilder_create);

/* {{{ proto void git_treebuilder_clear(bld)
*/
PHP_FUNCTION(git_treebuilder_clear);

/* {{{ proto resource git_treebuilder_entrycount(bld)
*/
PHP_FUNCTION(git_treebuilder_entrycount);

/* {{{ proto void git_treebuilder_free(bld)
*/
PHP_FUNCTION(git_treebuilder_free);

/* {{{ proto resource git_treebuilder_get(bld, filename)
*/
PHP_FUNCTION(git_treebuilder_get);

/* {{{ proto resource git_treebuilder_insert(bld, filename, id, filemode)
*/
PHP_FUNCTION(git_treebuilder_insert);

/* {{{ proto long git_treebuilder_remove(bld, filename)
*/
PHP_FUNCTION(git_treebuilder_remove);

/* {{{ proto void git_treebuilder_filter(bld, filter, payload)
*/
PHP_FUNCTION(git_treebuilder_filter);

/* {{{ proto long git_treebuilder_write(repo, bld)
*/
PHP_FUNCTION(git_treebuilder_write);

#endif