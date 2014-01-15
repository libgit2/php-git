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
#ifndef PHP_GIT2_PUSH_H
#define PHP_GIT2_PUSH_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_new, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_set_options, 0, 0, 2)
	ZEND_ARG_INFO(0, push)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_set_callbacks, 0, 0, 5)
	ZEND_ARG_INFO(0, push)
	ZEND_ARG_INFO(0, pack_progress_cb)
	ZEND_ARG_INFO(0, pack_progress_cb_payload)
	ZEND_ARG_INFO(0, transfer_progress_cb)
	ZEND_ARG_INFO(0, transfer_progress_cb_payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_add_refspec, 0, 0, 2)
	ZEND_ARG_INFO(0, push)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_update_tips, 0, 0, 1)
	ZEND_ARG_INFO(0, push)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_finish, 0, 0, 1)
	ZEND_ARG_INFO(0, push)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_unpack_ok, 0, 0, 1)
	ZEND_ARG_INFO(0, push)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_status_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, push)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_push_free, 0, 0, 1)
	ZEND_ARG_INFO(0, push)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_push_new(remote)
*/
PHP_FUNCTION(git_push_new);

/* {{{ proto long git_push_set_options(push, opts)
*/
PHP_FUNCTION(git_push_set_options);

/* {{{ proto long git_push_set_callbacks(push, pack_progress_cb, pack_progress_cb_payload, transfer_progress_cb, transfer_progress_cb_payload)
*/
PHP_FUNCTION(git_push_set_callbacks);

/* {{{ proto long git_push_add_refspec(push, refspec)
*/
PHP_FUNCTION(git_push_add_refspec);

/* {{{ proto long git_push_update_tips(push)
*/
PHP_FUNCTION(git_push_update_tips);

/* {{{ proto long git_push_finish(push)
*/
PHP_FUNCTION(git_push_finish);

/* {{{ proto long git_push_unpack_ok(push)
*/
PHP_FUNCTION(git_push_unpack_ok);

/* {{{ proto long git_push_status_foreach(push, ref, msg, data), data)
*/
PHP_FUNCTION(git_push_status_foreach);

/* {{{ proto void git_push_free(push)
*/
PHP_FUNCTION(git_push_free);

#endif
