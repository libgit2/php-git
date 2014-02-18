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
#ifndef PHP_GIT2_PATHSPEC_H
#define PHP_GIT2_PATHSPEC_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_new, 0, 0, 1)
	ZEND_ARG_INFO(0, pathspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_free, 0, 0, 1)
	ZEND_ARG_INFO(0, ps)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_matches_path, 0, 0, 3)
	ZEND_ARG_INFO(0, ps)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_workdir, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, ps)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_index, 0, 0, 3)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, ps)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_tree, 0, 0, 3)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, ps)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_diff, 0, 0, 3)
	ZEND_ARG_INFO(0, diff)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, ps)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_list_free, 0, 0, 1)
	ZEND_ARG_INFO(0, m)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_list_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, m)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_list_entry, 0, 0, 2)
	ZEND_ARG_INFO(0, m)
	ZEND_ARG_INFO(0, pos)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_list_diff_entry, 0, 0, 2)
	ZEND_ARG_INFO(0, m)
	ZEND_ARG_INFO(0, pos)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_list_failed_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, m)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_pathspec_match_list_failed_entry, 0, 0, 2)
	ZEND_ARG_INFO(0, m)
	ZEND_ARG_INFO(0, pos)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_pathspec_new(pathspec)
*/
PHP_FUNCTION(git_pathspec_new);

/* {{{ proto void git_pathspec_free(ps)
*/
PHP_FUNCTION(git_pathspec_free);

/* {{{ proto long git_pathspec_matches_path(ps, flags, path)
*/
PHP_FUNCTION(git_pathspec_matches_path);

/* {{{ proto resource git_pathspec_match_workdir(repo, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_workdir);

/* {{{ proto resource git_pathspec_match_index(index, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_index);

/* {{{ proto resource git_pathspec_match_tree(tree, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_tree);

/* {{{ proto resource git_pathspec_match_diff(diff, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_diff);

/* {{{ proto void git_pathspec_match_list_free(m)
*/
PHP_FUNCTION(git_pathspec_match_list_free);

/* {{{ proto resource git_pathspec_match_list_entrycount(m)
*/
PHP_FUNCTION(git_pathspec_match_list_entrycount);

/* {{{ proto resource git_pathspec_match_list_entry(m, pos)
*/
PHP_FUNCTION(git_pathspec_match_list_entry);

/* {{{ proto resource git_pathspec_match_list_diff_entry(m, pos)
*/
PHP_FUNCTION(git_pathspec_match_list_diff_entry);

/* {{{ proto resource git_pathspec_match_list_failed_entrycount(m)
*/
PHP_FUNCTION(git_pathspec_match_list_failed_entrycount);

/* {{{ proto resource git_pathspec_match_list_failed_entry(m, pos)
*/
PHP_FUNCTION(git_pathspec_match_list_failed_entry);

#endif