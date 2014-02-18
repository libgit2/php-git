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
#ifndef PHP_GIT2_REFLOG_H
#define PHP_GIT2_REFLOG_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_read, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_write, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_append, 0, 0, 4)
	ZEND_ARG_INFO(0, reflog)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, committer)
	ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_append_to, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, committer)
	ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_rename, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, old_name)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_delete, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, reflog)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_entry_byindex, 0, 0, 2)
	ZEND_ARG_INFO(0, reflog)
	ZEND_ARG_INFO(0, idx)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_drop, 0, 0, 3)
	ZEND_ARG_INFO(0, reflog)
	ZEND_ARG_INFO(0, idx)
	ZEND_ARG_INFO(0, rewrite_previous_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_entry_id_old, 0, 0, 1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_entry_id_new, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_entry_committer, 0, 0, 1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_entry_message, 0, 0, 1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reflog_free, 0, 0, 1)
	ZEND_ARG_INFO(0, reflog)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_reflog_read(repo, name)
*/
PHP_FUNCTION(git_reflog_read);

/* {{{ proto resource git_reflog_write()
*/
PHP_FUNCTION(git_reflog_write);

/* {{{ proto long git_reflog_append(reflog, id, committer, msg)
*/
PHP_FUNCTION(git_reflog_append);

/* {{{ proto long git_reflog_append_to(repo, name, id, committer, msg)
*/
PHP_FUNCTION(git_reflog_append_to);

/* {{{ proto long git_reflog_rename(repo, old_name, name)
*/
PHP_FUNCTION(git_reflog_rename);

/* {{{ proto long git_reflog_delete(repo, name)
*/
PHP_FUNCTION(git_reflog_delete);

/* {{{ proto resource git_reflog_entrycount(reflog)
*/
PHP_FUNCTION(git_reflog_entrycount);

/* {{{ proto resource git_reflog_entry_byindex(reflog, idx)
*/
PHP_FUNCTION(git_reflog_entry_byindex);

/* {{{ proto long git_reflog_drop(reflog, idx, rewrite_previous_entry)
*/
PHP_FUNCTION(git_reflog_drop);

/* {{{ proto resource git_reflog_entry_id_old(entry)
*/
PHP_FUNCTION(git_reflog_entry_id_old);

/* {{{ proto resource git_reflog_entry_id_new()
*/
PHP_FUNCTION(git_reflog_entry_id_new);

/* {{{ proto resource git_reflog_entry_committer(entry)
*/
PHP_FUNCTION(git_reflog_entry_committer);

/* {{{ proto resource git_reflog_entry_message(entry)
*/
PHP_FUNCTION(git_reflog_entry_message);

/* {{{ proto void git_reflog_free(reflog)
*/
PHP_FUNCTION(git_reflog_free);

#endif