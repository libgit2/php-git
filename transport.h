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
#ifndef PHP_GIT2_TRANSPORT_H
#define PHP_GIT2_TRANSPORT_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_transport_new, 0, 0, 2)
	ZEND_ARG_INFO(0, owner)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_transport_register, 0, 0, 4)
	ZEND_ARG_INFO(0, prefix)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, cb)
	ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_transport_unregister, 0, 0, 2)
	ZEND_ARG_INFO(0, prefix)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_transport_dummy, 0, 0, 2)
	ZEND_ARG_INFO(0, owner)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_transport_local, 0, 0, 2)
	ZEND_ARG_INFO(0, owner)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_transport_smart, 0, 0, 2)
	ZEND_ARG_INFO(0, owner)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_smart_subtransport_http, 0, 0, 1)
	ZEND_ARG_INFO(0, owner)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_smart_subtransport_git, 0, 0, 1)
	ZEND_ARG_INFO(0, owner)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_smart_subtransport_ssh, 0, 0, 1)
	ZEND_ARG_INFO(0, owner)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_transport_new(owner, url)
*/
PHP_FUNCTION(git_transport_new);

/* {{{ proto long git_transport_register(prefix, priority, cb, param)
*/
PHP_FUNCTION(git_transport_register);

/* {{{ proto long git_transport_unregister(prefix, priority)
*/
PHP_FUNCTION(git_transport_unregister);

/* {{{ proto resource git_transport_dummy(owner, payload)
*/
PHP_FUNCTION(git_transport_dummy);

/* {{{ proto resource git_transport_local(owner, payload)
*/
PHP_FUNCTION(git_transport_local);

/* {{{ proto resource git_transport_smart(owner, payload)
*/
PHP_FUNCTION(git_transport_smart);

/* {{{ proto resource git_smart_subtransport_http(owner)
*/
PHP_FUNCTION(git_smart_subtransport_http);

/* {{{ proto resource git_smart_subtransport_git(owner)
*/
PHP_FUNCTION(git_smart_subtransport_git);

/* {{{ proto resource git_smart_subtransport_ssh(owner)
*/
PHP_FUNCTION(git_smart_subtransport_ssh);

#endif