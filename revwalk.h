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
#ifndef PHP_GIT2_REVWALK_H
#define PHP_GIT2_REVWALK_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_new, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_reset, 0, 0, 1)
	ZEND_ARG_INFO(0, walker)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_push, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_push_glob, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, glob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_push_head, 0, 0, 1)
	ZEND_ARG_INFO(0, walk)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_hide, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, commit_id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_hide_glob, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, glob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_hide_head, 0, 0, 1)
	ZEND_ARG_INFO(0, walk)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_push_ref, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, refname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_hide_ref, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, refname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_next, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_sorting, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, sort_mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_push_range, 0, 0, 2)
	ZEND_ARG_INFO(0, walk)
	ZEND_ARG_INFO(0, range)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_simplify_first_parent, 0, 0, 1)
	ZEND_ARG_INFO(0, walk)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_free, 0, 0, 1)
	ZEND_ARG_INFO(0, walk)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_revwalk_repository, 0, 0, 1)
	ZEND_ARG_INFO(0, walk)
ZEND_END_ARG_INFO()

/* {{{ proto long git_revwalk_new(repo)
*/
PHP_FUNCTION(git_revwalk_new);

/* {{{ proto void git_revwalk_reset(walker)
*/
PHP_FUNCTION(git_revwalk_reset);

/* {{{ proto long git_revwalk_push(walk, id)
*/
PHP_FUNCTION(git_revwalk_push);

/* {{{ proto long git_revwalk_push_glob(walk, glob)
*/
PHP_FUNCTION(git_revwalk_push_glob);

/* {{{ proto long git_revwalk_push_head(walk)
*/
PHP_FUNCTION(git_revwalk_push_head);

/* {{{ proto long git_revwalk_hide(walk, commit_id)
*/
PHP_FUNCTION(git_revwalk_hide);

/* {{{ proto long git_revwalk_hide_glob(walk, glob)
*/
PHP_FUNCTION(git_revwalk_hide_glob);

/* {{{ proto long git_revwalk_hide_head(walk)
*/
PHP_FUNCTION(git_revwalk_hide_head);

/* {{{ proto long git_revwalk_push_ref(walk, refname)
*/
PHP_FUNCTION(git_revwalk_push_ref);

/* {{{ proto long git_revwalk_hide_ref(walk, refname)
*/
PHP_FUNCTION(git_revwalk_hide_ref);

/* {{{ proto long git_revwalk_next(walk)
*/
PHP_FUNCTION(git_revwalk_next);

/* {{{ proto void git_revwalk_sorting(walk, sort_mode)
*/
PHP_FUNCTION(git_revwalk_sorting);

/* {{{ proto long git_revwalk_push_range(walk, range)
*/
PHP_FUNCTION(git_revwalk_push_range);

/* {{{ proto void git_revwalk_simplify_first_parent(walk)
*/
PHP_FUNCTION(git_revwalk_simplify_first_parent);

/* {{{ proto void git_revwalk_free(walk)
*/
PHP_FUNCTION(git_revwalk_free);

/* {{{ proto resource git_revwalk_repository(walk)
*/
PHP_FUNCTION(git_revwalk_repository);


#endif