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
#ifndef PHP_GIT2_COMMIT_H
#define PHP_GIT2_COMMIT_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_author, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_tree, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_lookup_prefix, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_id, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_message_encoding, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_message, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_message_raw, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_time, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_time_offset, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_committer, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_raw_header, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_tree_id, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_parentcount, 0, 0, 1)
	ZEND_ARG_INFO(0, commit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_parent, 0, 0, 2)
	ZEND_ARG_INFO(0, commit)
	ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_parent_id, 0, 0, 2)
	ZEND_ARG_INFO(0, commit)
	ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_nth_gen_ancestor, 0, 0, 2)
	ZEND_ARG_INFO(0, commit)
	ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_commit_create, 0, 0, 8)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, update_ref)
	ZEND_ARG_INFO(0, author)
	ZEND_ARG_INFO(0, committer)
	ZEND_ARG_INFO(0, message_encoding)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, parents)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_commit_lookup(resource $repository, mixed $oid)
*/
PHP_FUNCTION(git_commit_lookup);

/* {{{ proto resource git_commit_author(resource $commit)
*/
PHP_FUNCTION(git_commit_author);

/* {{{ proto resource git_commit_tree(resource $commit)
*/
PHP_FUNCTION(git_commit_tree);

/* {{{ proto resource git_commit_lookup_prefix(repo, id, len)
*/
PHP_FUNCTION(git_commit_lookup_prefix);

/* {{{ proto resource git_commit_id(commit)
*/
PHP_FUNCTION(git_commit_id);

/* {{{ proto resource git_commit_owner(commit)
*/
PHP_FUNCTION(git_commit_owner);

/* {{{ proto resource git_commit_message_encoding(commit)
*/
PHP_FUNCTION(git_commit_message_encoding);

/* {{{ proto resource git_commit_message(commit)
*/
PHP_FUNCTION(git_commit_message);

/* {{{ proto resource git_commit_message_raw(commit)
*/
PHP_FUNCTION(git_commit_message_raw);

/* {{{ proto resource git_commit_time(commit)
*/
PHP_FUNCTION(git_commit_time);

/* {{{ proto long git_commit_time_offset(commit)
*/
PHP_FUNCTION(git_commit_time_offset);

/* {{{ proto resource git_commit_committer(commit)
*/
PHP_FUNCTION(git_commit_committer);

/* {{{ proto resource git_commit_raw_header(commit)
*/
PHP_FUNCTION(git_commit_raw_header);

/* {{{ proto resource git_commit_tree(commit)
*/
PHP_FUNCTION(git_commit_tree);

/* {{{ proto resource git_commit_tree_id(commit)
*/
PHP_FUNCTION(git_commit_tree_id);

/* {{{ proto resource git_commit_parentcount(commit)
*/
PHP_FUNCTION(git_commit_parentcount);

/* {{{ proto resource git_commit_parent(commit, n)
*/
PHP_FUNCTION(git_commit_parent);

/* {{{ proto resource git_commit_parent_id(commit, n)
*/
PHP_FUNCTION(git_commit_parent_id);

/* {{{ proto resource git_commit_nth_gen_ancestor(commit, n)
*/
PHP_FUNCTION(git_commit_nth_gen_ancestor);

/* {{{ proto resource git_commit_create(
	resource $repo, mixed $update_ref, array $author, array $committer,
	string $message_encoding, string $message, resource $tree, array $parents)
*/
PHP_FUNCTION(git_commit_create);

#endif