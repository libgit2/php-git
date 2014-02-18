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
#ifndef PHP_GIT2_NOTE_H
#define PHP_GIT2_NOTE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_iterator_new, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, notes_ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_iterator_free, 0, 0, 1)
	ZEND_ARG_INFO(0, it)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_next, 0, 0, 3)
	ZEND_ARG_INFO(0, note_id)
	ZEND_ARG_INFO(0, annotated_id)
	ZEND_ARG_INFO(0, it)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_read, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, notes_ref)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_message, 0, 0, 1)
	ZEND_ARG_INFO(0, note)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_oid, 0, 0, 1)
	ZEND_ARG_INFO(0, note)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_create, 0, 0, 7)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, author)
	ZEND_ARG_INFO(0, committer)
	ZEND_ARG_INFO(0, notes_ref)
	ZEND_ARG_INFO(0, oid)
	ZEND_ARG_INFO(0, note)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_remove, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, notes_ref)
	ZEND_ARG_INFO(0, author)
	ZEND_ARG_INFO(0, committer)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_free, 0, 0, 1)
	ZEND_ARG_INFO(0, note)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_default_ref, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_note_foreach, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, notes_ref)
	ZEND_ARG_INFO(0, note_cb)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_note_iterator_new(repo, notes_ref)
*/
PHP_FUNCTION(git_note_iterator_new);

/* {{{ proto void git_note_iterator_free(it)
*/
PHP_FUNCTION(git_note_iterator_free);

/* {{{ proto long git_note_next(note_id, annotated_id, it)
*/
PHP_FUNCTION(git_note_next);

/* {{{ proto resource git_note_read(repo, notes_ref, oid)
*/
PHP_FUNCTION(git_note_read);

/* {{{ proto resource git_note_message(note)
*/
PHP_FUNCTION(git_note_message);

/* {{{ proto resource git_note_oid(note)
*/
PHP_FUNCTION(git_note_oid);

/* {{{ proto resource git_note_create(repo, author, committer, notes_ref, oid, note, force)
*/
PHP_FUNCTION(git_note_create);

/* {{{ proto long git_note_remove(repo, notes_ref, author, committer, oid)
*/
PHP_FUNCTION(git_note_remove);

/* {{{ proto void git_note_free(note)
*/
PHP_FUNCTION(git_note_free);

/* {{{ proto resource git_note_default_ref(repo)
*/
PHP_FUNCTION(git_note_default_ref);

/* {{{ proto long git_note_foreach(repo, notes_ref, note_cb, payload)
*/
PHP_FUNCTION(git_note_foreach);

#endif