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
#ifndef PHP_GIT2_REMOTE_H
#define PHP_GIT2_REMOTE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_create, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_create_with_fetchspec, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, fetch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_create_inmemory, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, fetch)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_load, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_save, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_name, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_url, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_pushurl, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_url, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_pushurl, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_add_fetch, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_get_fetch_refspecs, 0, 0, 2)
	ZEND_ARG_INFO(0, array)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_fetch_refspecs, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_add_push, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_get_push_refspecs, 0, 0, 2)
	ZEND_ARG_INFO(0, array)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_push_refspecs, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_clear_refspecs, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_refspec_count, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_get_refspec, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_connect, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_ls, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_download, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_connected, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_stop, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_disconnect, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_free, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_update_tips, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_fetch, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_valid_url, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_supported_url, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_list, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_check_cert, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, check)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_transport, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, transport)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_callbacks, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, callbacks)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_stats, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_autotag, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_autotag, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_rename, 0, 0, 4)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, new_name)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_update_fetchhead, 0, 0, 1)
	ZEND_ARG_INFO(0, remote)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_set_update_fetchhead, 0, 0, 2)
	ZEND_ARG_INFO(0, remote)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_remote_is_valid_name, 0, 0, 1)
	ZEND_ARG_INFO(0, remote_name)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_remote_create(repo, name, url)
*/
PHP_FUNCTION(git_remote_create);

/* {{{ proto resource git_remote_create_with_fetchspec(repo, name, url, fetch)
*/
PHP_FUNCTION(git_remote_create_with_fetchspec);

/* {{{ proto resource git_remote_create_inmemory(repo, fetch, url)
*/
PHP_FUNCTION(git_remote_create_inmemory);

/* {{{ proto resource git_remote_load(repo, name)
*/
PHP_FUNCTION(git_remote_load);

/* {{{ proto long git_remote_save(remote)
*/
PHP_FUNCTION(git_remote_save);

/* {{{ proto resource git_remote_owner(remote)
*/
PHP_FUNCTION(git_remote_owner);

/* {{{ proto resource git_remote_name(remote)
*/
PHP_FUNCTION(git_remote_name);

/* {{{ proto resource git_remote_url(remote)
*/
PHP_FUNCTION(git_remote_url);

/* {{{ proto resource git_remote_pushurl(remote)
*/
PHP_FUNCTION(git_remote_pushurl);

/* {{{ proto long git_remote_set_url(remote, url)
*/
PHP_FUNCTION(git_remote_set_url);

/* {{{ proto long git_remote_set_pushurl(remote, url)
*/
PHP_FUNCTION(git_remote_set_pushurl);

/* {{{ proto long git_remote_add_fetch(remote, refspec)
*/
PHP_FUNCTION(git_remote_add_fetch);

/* {{{ proto long git_remote_get_fetch_refspecs(array, remote)
*/
PHP_FUNCTION(git_remote_get_fetch_refspecs);

/* {{{ proto long git_remote_set_fetch_refspecs(remote, array)
*/
PHP_FUNCTION(git_remote_set_fetch_refspecs);

/* {{{ proto long git_remote_add_push(remote, refspec)
*/
PHP_FUNCTION(git_remote_add_push);

/* {{{ proto long git_remote_get_push_refspecs(array, remote)
*/
PHP_FUNCTION(git_remote_get_push_refspecs);

/* {{{ proto long git_remote_set_push_refspecs(remote, array)
*/
PHP_FUNCTION(git_remote_set_push_refspecs);

/* {{{ proto void git_remote_clear_refspecs(remote)
*/
PHP_FUNCTION(git_remote_clear_refspecs);

/* {{{ proto resource git_remote_refspec_count(remote)
*/
PHP_FUNCTION(git_remote_refspec_count);

/* {{{ proto resource git_remote_get_refspec(remote, n)
*/
PHP_FUNCTION(git_remote_get_refspec);

/* {{{ proto long git_remote_connect(remote, direction)
*/
PHP_FUNCTION(git_remote_connect);

/* {{{ proto resource git_remote_ls(remote)
*/
PHP_FUNCTION(git_remote_ls);

/* {{{ proto long git_remote_download(remote)
*/
PHP_FUNCTION(git_remote_download);

/* {{{ proto long git_remote_connected(remote)
*/
PHP_FUNCTION(git_remote_connected);

/* {{{ proto void git_remote_stop(remote)
*/
PHP_FUNCTION(git_remote_stop);

/* {{{ proto void git_remote_disconnect(remote)
*/
PHP_FUNCTION(git_remote_disconnect);

/* {{{ proto void git_remote_free(remote)
*/
PHP_FUNCTION(git_remote_free);

/* {{{ proto long git_remote_update_tips(remote)
*/
PHP_FUNCTION(git_remote_update_tips);

/* {{{ proto long git_remote_fetch(remote)
*/
PHP_FUNCTION(git_remote_fetch);

/* {{{ proto long git_remote_valid_url(url)
*/
PHP_FUNCTION(git_remote_valid_url);

/* {{{ proto long git_remote_supported_url(url)
*/
PHP_FUNCTION(git_remote_supported_url);

/* {{{ proto resource git_remote_list(repo)
*/
PHP_FUNCTION(git_remote_list);

/* {{{ proto void git_remote_check_cert(remote, check)
*/
PHP_FUNCTION(git_remote_check_cert);

/* {{{ proto long git_remote_set_transport(remote, transport)
*/
PHP_FUNCTION(git_remote_set_transport);

/* {{{ proto long git_remote_set_callbacks(remote, callbacks)
*/
PHP_FUNCTION(git_remote_set_callbacks);

/* {{{ proto resource git_remote_stats(remote)
*/
PHP_FUNCTION(git_remote_stats);

/* {{{ proto resource git_remote_autotag(remote)
*/
PHP_FUNCTION(git_remote_autotag);

/* {{{ proto void git_remote_set_autotag(remote, value)
*/
PHP_FUNCTION(git_remote_set_autotag);

/* {{{ proto long git_remote_rename(remote, new_name, callback, payload)
*/
PHP_FUNCTION(git_remote_rename);

/* {{{ proto long git_remote_update_fetchhead(remote)
*/
PHP_FUNCTION(git_remote_update_fetchhead);

/* {{{ proto void git_remote_set_update_fetchhead(remote, value)
*/
PHP_FUNCTION(git_remote_set_update_fetchhead);

/* {{{ proto long git_remote_is_valid_name(remote_name)
*/
PHP_FUNCTION(git_remote_is_valid_name);

#endif