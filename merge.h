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
#ifndef PHP_GIT2_MERGE_H
#define PHP_GIT2_MERGE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_base, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, one)
	ZEND_ARG_INFO(0, two)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_base_many, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, length)
	ZEND_ARG_INFO(0, input_array[])
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_head_from_ref, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_head_from_fetchhead, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, branch_name)
	ZEND_ARG_INFO(0, remote_url)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_head_from_oid, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_head_free, 0, 0, 1)
	ZEND_ARG_INFO(0, head)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_trees, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, ancestor_tree)
	ZEND_ARG_INFO(0, our_tree)
	ZEND_ARG_INFO(0, their_tree)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, their_heads)
	ZEND_ARG_INFO(0, their_heads_len)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_result_is_uptodate, 0, 0, 1)
	ZEND_ARG_INFO(0, merge_result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_result_is_fastforward, 0, 0, 1)
	ZEND_ARG_INFO(0, merge_result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_result_fastforward_oid, 0, 0, 1)
	ZEND_ARG_INFO(0, merge_result)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_merge_result_free, 0, 0, 1)
	ZEND_ARG_INFO(0, merge_result)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_merge_base(repo, one, two)
*/
PHP_FUNCTION(git_merge_base);

/* {{{ proto resource git_merge_base_many(repo, length, input_array[])
*/
PHP_FUNCTION(git_merge_base_many);

/* {{{ proto resource git_merge_head_from_ref(repo, ref)
*/
PHP_FUNCTION(git_merge_head_from_ref);

/* {{{ proto resource git_merge_head_from_fetchhead(repo, branch_name, remote_url, oid)
*/
PHP_FUNCTION(git_merge_head_from_fetchhead);

/* {{{ proto resource git_merge_head_from_oid(repo, oid)
*/
PHP_FUNCTION(git_merge_head_from_oid);

/* {{{ proto void git_merge_head_free(head)
*/
PHP_FUNCTION(git_merge_head_free);

/* {{{ proto resource git_merge_trees(repo, ancestor_tree, our_tree, their_tree, opts)
*/
PHP_FUNCTION(git_merge_trees);

/* {{{ proto resource git_merge(repo, their_heads, their_heads_len, opts)
*/
PHP_FUNCTION(git_merge);

/* {{{ proto long git_merge_result_is_uptodate(merge_result)
*/
PHP_FUNCTION(git_merge_result_is_uptodate);

/* {{{ proto long git_merge_result_is_fastforward(merge_result)
*/
PHP_FUNCTION(git_merge_result_is_fastforward);

/* {{{ proto resource git_merge_result_fastforward_oid(merge_result)
*/
PHP_FUNCTION(git_merge_result_fastforward_oid);

/* {{{ proto void git_merge_result_free(merge_result)
*/
PHP_FUNCTION(git_merge_result_free);

#endif