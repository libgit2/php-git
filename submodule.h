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
#ifndef PHP_GIT2_SUBMODULE_H
#define PHP_GIT2_SUBMODULE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_foreach, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, sm)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_add_setup, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, use_gitlink)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_add_finalize, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_add_to_index, 0, 0, 2)
	ZEND_ARG_INFO(0, submodule)
	ZEND_ARG_INFO(0, write_index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_save, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_name, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_path, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_url, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_set_url, 0, 0, 2)
	ZEND_ARG_INFO(0, submodule)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_index_id, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_head_id, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_wd_id, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_ignore, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_set_ignore, 0, 0, 2)
	ZEND_ARG_INFO(0, submodule)
	ZEND_ARG_INFO(0, ignore)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_update, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_set_update, 0, 0, 2)
	ZEND_ARG_INFO(0, submodule)
	ZEND_ARG_INFO(0, update)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_fetch_recurse_submodules, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_set_fetch_recurse_submodules, 0, 0, 2)
	ZEND_ARG_INFO(0, submodule)
	ZEND_ARG_INFO(0, fetch_recurse_submodules)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_init, 0, 0, 2)
	ZEND_ARG_INFO(0, submodule)
	ZEND_ARG_INFO(0, overwrite)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_sync, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_open, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_reload, 0, 0, 1)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_reload_all, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_status, 0, 0, 2)
	ZEND_ARG_INFO(0, status)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_submodule_location, 0, 0, 2)
	ZEND_ARG_INFO(0, location_status)
	ZEND_ARG_INFO(0, submodule)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_submodule_lookup(repo, name)
*/
PHP_FUNCTION(git_submodule_lookup);

/* {{{ proto long git_submodule_foreach(repo, sm, name, payload), payload)
*/
PHP_FUNCTION(git_submodule_foreach);

/* {{{ proto resource git_submodule_add_setup(repo, url, path, use_gitlink)
*/
PHP_FUNCTION(git_submodule_add_setup);

/* {{{ proto long git_submodule_add_finalize(submodule)
*/
PHP_FUNCTION(git_submodule_add_finalize);

/* {{{ proto long git_submodule_add_to_index(submodule, write_index)
*/
PHP_FUNCTION(git_submodule_add_to_index);

/* {{{ proto long git_submodule_save(submodule)
*/
PHP_FUNCTION(git_submodule_save);

/* {{{ proto resource git_submodule_owner(submodule)
*/
PHP_FUNCTION(git_submodule_owner);

/* {{{ proto resource git_submodule_name(submodule)
*/
PHP_FUNCTION(git_submodule_name);

/* {{{ proto resource git_submodule_path(submodule)
*/
PHP_FUNCTION(git_submodule_path);

/* {{{ proto resource git_submodule_url(submodule)
*/
PHP_FUNCTION(git_submodule_url);

/* {{{ proto long git_submodule_set_url(submodule, url)
*/
PHP_FUNCTION(git_submodule_set_url);

/* {{{ proto resource git_submodule_index_id(submodule)
*/
PHP_FUNCTION(git_submodule_index_id);

/* {{{ proto resource git_submodule_head_id(submodule)
*/
PHP_FUNCTION(git_submodule_head_id);

/* {{{ proto resource git_submodule_wd_id(submodule)
*/
PHP_FUNCTION(git_submodule_wd_id);

/* {{{ proto resource git_submodule_ignore(submodule)
*/
PHP_FUNCTION(git_submodule_ignore);

/* {{{ proto resource git_submodule_set_ignore(submodule, ignore)
*/
PHP_FUNCTION(git_submodule_set_ignore);

/* {{{ proto resource git_submodule_update(submodule)
*/
PHP_FUNCTION(git_submodule_update);

/* {{{ proto resource git_submodule_set_update(submodule, update)
*/
PHP_FUNCTION(git_submodule_set_update);

/* {{{ proto long git_submodule_fetch_recurse_submodules(submodule)
*/
PHP_FUNCTION(git_submodule_fetch_recurse_submodules);

/* {{{ proto long git_submodule_set_fetch_recurse_submodules(submodule, fetch_recurse_submodules)
*/
PHP_FUNCTION(git_submodule_set_fetch_recurse_submodules);

/* {{{ proto long git_submodule_init(submodule, overwrite)
*/
PHP_FUNCTION(git_submodule_init);

/* {{{ proto long git_submodule_sync(submodule)
*/
PHP_FUNCTION(git_submodule_sync);

/* {{{ proto resource git_submodule_open(submodule)
*/
PHP_FUNCTION(git_submodule_open);

/* {{{ proto long git_submodule_reload(submodule)
*/
PHP_FUNCTION(git_submodule_reload);

/* {{{ proto long git_submodule_reload_all(repo)
*/
PHP_FUNCTION(git_submodule_reload_all);

/* {{{ proto long git_submodule_status(status, submodule)
*/
PHP_FUNCTION(git_submodule_status);

/* {{{ proto long git_submodule_location(location_status, submodule)
*/
PHP_FUNCTION(git_submodule_location);

#endif