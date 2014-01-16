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
#ifndef PHP_GIT2_PACKBUILDER_H
#define PHP_GIT2_PACKBUILDER_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_new, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_set_threads, 0, 0, 2)
	ZEND_ARG_INFO(0, pb)
	ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_insert, 0, 0, 3)
	ZEND_ARG_INFO(0, pb)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_insert_tree, 0, 0, 2)
	ZEND_ARG_INFO(0, pb)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_insert_commit, 0, 0, 2)
	ZEND_ARG_INFO(0, pb)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_write, 0, 0, 4)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, mode)
	ZEND_ARG_INFO(0, progress_cb)
	ZEND_ARG_INFO(0, progress_cb_payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_hash, 0, 0, 1)
	ZEND_ARG_INFO(0, pb)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, pb)
	ZEND_ARG_INFO(0, cb)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_object_count, 0, 0, 1)
	ZEND_ARG_INFO(0, pb)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_written, 0, 0, 1)
	ZEND_ARG_INFO(0, pb)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_set_callbacks, 0, 0, 3)
	ZEND_ARG_INFO(0, pb)
	ZEND_ARG_INFO(0, progress_cb)
	ZEND_ARG_INFO(0, progress_cb_payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_packbuilder_free, 0, 0, 1)
	ZEND_ARG_INFO(0, pb)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_packbuilder_new(repo)
*/
PHP_FUNCTION(git_packbuilder_new);

/* {{{ proto resource git_packbuilder_set_threads(pb, n)
*/
PHP_FUNCTION(git_packbuilder_set_threads);

/* {{{ proto long git_packbuilder_insert(pb, id, name)
*/
PHP_FUNCTION(git_packbuilder_insert);

/* {{{ proto long git_packbuilder_insert_tree(pb, id)
*/
PHP_FUNCTION(git_packbuilder_insert_tree);

/* {{{ proto long git_packbuilder_insert_commit(pb, id)
*/
PHP_FUNCTION(git_packbuilder_insert_commit);

/* {{{ proto resource git_packbuilder_write(path, mode, progress_cb, progress_cb_payload)
*/
PHP_FUNCTION(git_packbuilder_write);

/* {{{ proto resource git_packbuilder_hash(pb)
*/
PHP_FUNCTION(git_packbuilder_hash);

/* {{{ proto long git_packbuilder_foreach(pb, cb, payload)
*/
PHP_FUNCTION(git_packbuilder_foreach);

/* {{{ proto resource git_packbuilder_object_count(pb)
*/
PHP_FUNCTION(git_packbuilder_object_count);

/* {{{ proto resource git_packbuilder_written(pb)
*/
PHP_FUNCTION(git_packbuilder_written);

/* {{{ proto long git_packbuilder_set_callbacks(pb, progress_cb, progress_cb_payload)
*/
PHP_FUNCTION(git_packbuilder_set_callbacks);

/* {{{ proto void git_packbuilder_free(pb)
*/
PHP_FUNCTION(git_packbuilder_free);

#endif
