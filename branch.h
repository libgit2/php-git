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
#ifndef PHP_GIT2_BRANCH_H
#define PHP_GIT2_BRANCH_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_create, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, branch_name)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, branch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_iterator_new, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, list_flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_next, 0, 0, 2)
	ZEND_ARG_INFO(0, out_type)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_iterator_free, 0, 0, 1)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_move, 0, 0, 3)
	ZEND_ARG_INFO(0, branch)
	ZEND_ARG_INFO(0, new_branch_name)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_lookup, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, branch_name)
	ZEND_ARG_INFO(0, branch_type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_name, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_upstream, 0, 0, 1)
	ZEND_ARG_INFO(0, branch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_set_upstream, 0, 0, 2)
	ZEND_ARG_INFO(0, branch)
	ZEND_ARG_INFO(0, upstream_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_upstream_name, 0, 0, 3)
	ZEND_ARG_INFO(0, buffer_size)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, canonical_branch_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_is_head, 0, 0, 1)
	ZEND_ARG_INFO(0, branch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_branch_remote_name, 0, 0, 3)
	ZEND_ARG_INFO(0, buffer_size)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, canonical_branch_name)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_branch_create(repo, branch_name, target, force)
*/
PHP_FUNCTION(git_branch_create);

/* {{{ proto long git_branch_delete(branch)
*/
PHP_FUNCTION(git_branch_delete);

/* {{{ proto resource git_branch_iterator_new(repo, list_flags)
*/
PHP_FUNCTION(git_branch_iterator_new);

/* {{{ proto resource git_branch_next(out_type, iter)
*/
PHP_FUNCTION(git_branch_next);

/* {{{ proto void git_branch_iterator_free(iter)
*/
PHP_FUNCTION(git_branch_iterator_free);

/* {{{ proto resource git_branch_move(branch, new_branch_name, force)
*/
PHP_FUNCTION(git_branch_move);

/* {{{ proto resource git_branch_lookup(repo, branch_name, branch_type)
*/
PHP_FUNCTION(git_branch_lookup);

/* {{{ proto resource git_branch_name(ref)
*/
PHP_FUNCTION(git_branch_name);

/* {{{ proto resource git_branch_upstream(branch)
*/
PHP_FUNCTION(git_branch_upstream);

/* {{{ proto long git_branch_set_upstream(branch, upstream_name)
*/
PHP_FUNCTION(git_branch_set_upstream);

/* {{{ proto resource git_branch_upstream_name(buffer_size, repo, canonical_branch_name)
*/
PHP_FUNCTION(git_branch_upstream_name);

/* {{{ proto long git_branch_is_head(branch)
*/
PHP_FUNCTION(git_branch_is_head);

/* {{{ proto resource git_branch_remote_name(buffer_size, repo, canonical_branch_name)
*/
PHP_FUNCTION(git_branch_remote_name);

#endif