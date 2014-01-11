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
#ifndef PHP_GIT2_CRED_H
#define PHP_GIT2_CRED_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_cred_has_username, 0, 0, 1)
	ZEND_ARG_INFO(0, cred)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_cred_userpass_plaintext_new, 0, 0, 2)
	ZEND_ARG_INFO(0, username)
	ZEND_ARG_INFO(0, password)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_cred_ssh_key_new, 0, 0, 4)
	ZEND_ARG_INFO(0, username)
	ZEND_ARG_INFO(0, publickey)
	ZEND_ARG_INFO(0, privatekey)
	ZEND_ARG_INFO(0, passphrase)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_cred_ssh_custom_new, 0, 0, 5)
	ZEND_ARG_INFO(0, username)
	ZEND_ARG_INFO(0, publickey)
	ZEND_ARG_INFO(0, publickey_len)
	ZEND_ARG_INFO(0, sign_fn)
	ZEND_ARG_INFO(0, sign_data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_cred_default_new, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_cred_userpass, 0, 0, 4)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, user_from_url)
	ZEND_ARG_INFO(0, allowed_types)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

/* {{{ proto long git_cred_has_username(cred)
*/
PHP_FUNCTION(git_cred_has_username);

/* {{{ proto resource git_cred_userpass_plaintext_new(username, password)
*/
PHP_FUNCTION(git_cred_userpass_plaintext_new);

/* {{{ proto resource git_cred_ssh_key_new(username, publickey, privatekey, passphrase)
*/
PHP_FUNCTION(git_cred_ssh_key_new);

/* {{{ proto resource git_cred_ssh_custom_new(username, publickey, publickey_len, sign_fn, sign_data)
*/
PHP_FUNCTION(git_cred_ssh_custom_new);

/* {{{ proto resource git_cred_default_new()
*/
PHP_FUNCTION(git_cred_default_new);

/* {{{ proto resource git_cred_userpass(url, user_from_url, allowed_types, payload)
*/
PHP_FUNCTION(git_cred_userpass);

#endif