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
#ifndef PHP_GIT2_REPOSITORY_H
#define PHP_GIT2_REPOSITORY_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_new, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_init, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, is_bare)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_open_bare, 0, 0, 1)
	ZEND_ARG_INFO(0, bare_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_open, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_get_namespace, 0, 0, 1)
	ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_workdir, 0, 0, 1)
	ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_wrap_odb, 0, 0, 1)
	ZEND_ARG_INFO(0, odb)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_discover, 0, 0, 4)
	ZEND_ARG_INFO(0, path_size)
	ZEND_ARG_INFO(0, start_path)
	ZEND_ARG_INFO(0, across_fs)
	ZEND_ARG_INFO(0, ceiling_dirs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_open_ext, 0, 0, 3)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, ceiling_dirs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_free, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_init_ext, 0, 0, 2)
	ZEND_ARG_INFO(0, repo_path)
	ZEND_ARG_INFO(0, opts)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_head, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_head_detached, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_head_unborn, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_is_empty, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_path, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_set_workdir, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, workdir)
	ZEND_ARG_INFO(0, update_gitlink)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_is_bare, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_config, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_odb, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_refdb, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_index, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_message, 0, 0, 2)
	ZEND_ARG_INFO(0, len)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_message_remove, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_merge_cleanup, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_fetchhead_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_mergehead_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_hashfile, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, as_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_set_head, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, refname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_set_head_detached, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, commitish)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_detach_head, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_state, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_set_namespace, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, nmspace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_repository_is_shallow, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_repository_new()
*/
PHP_FUNCTION(git_repository_new);

/* {{{ proto resource git_repository_init(string $path, long is_bare = 0)
*/
PHP_FUNCTION(git_repository_init);

/* {{{ proto resource git_repository_open(string $path)
*/
PHP_FUNCTION(git_repository_open_bare);

/* {{{ proto resource git_repository_open(string $path)
*/
PHP_FUNCTION(git_repository_open);

/* {{{ proto string git_repository_get_namespace(resource $repository)
*/
PHP_FUNCTION(git_repository_get_namespace);

/* {{{ proto string git_repository_workdir(resource $repository)
*/
PHP_FUNCTION(git_repository_workdir);

/* {{{ proto resource git_repository_wrap_odb(odb)
*/
PHP_FUNCTION(git_repository_wrap_odb);

/* {{{ proto resource git_repository_discover(path_size, start_path, across_fs, ceiling_dirs)
*/
PHP_FUNCTION(git_repository_discover);

/* {{{ proto resource git_repository_open_ext(path, flags, ceiling_dirs)
*/
PHP_FUNCTION(git_repository_open_ext);

/* {{{ proto void git_repository_free(repo)
*/
PHP_FUNCTION(git_repository_free);

/* {{{ proto resource git_repository_init_ext(repo_path, opts)
*/
PHP_FUNCTION(git_repository_init_ext);

/* {{{ proto resource git_repository_head(repo)
*/
PHP_FUNCTION(git_repository_head);

/* {{{ proto long git_repository_head_detached(repo)
*/
PHP_FUNCTION(git_repository_head_detached);

/* {{{ proto long git_repository_head_unborn(repo)
*/
PHP_FUNCTION(git_repository_head_unborn);

/* {{{ proto long git_repository_is_empty(repo)
*/
PHP_FUNCTION(git_repository_is_empty);

/* {{{ proto resource git_repository_path(repo)
*/
PHP_FUNCTION(git_repository_path);

/* {{{ proto long git_repository_set_workdir(repo, workdir, update_gitlink)
*/
PHP_FUNCTION(git_repository_set_workdir);

/* {{{ proto long git_repository_is_bare(repo)
*/
PHP_FUNCTION(git_repository_is_bare);

/* {{{ proto resource git_repository_config(repo)
*/
PHP_FUNCTION(git_repository_config);

/* {{{ proto resource git_repository_odb(repo)
*/
PHP_FUNCTION(git_repository_odb);

/* {{{ proto resource git_repository_refdb(repo)
*/
PHP_FUNCTION(git_repository_refdb);

/* {{{ proto resource git_repository_index(repo)
*/
PHP_FUNCTION(git_repository_index);

/* {{{ proto resource git_repository_message(len, repo)
*/
PHP_FUNCTION(git_repository_message);

/* {{{ proto long git_repository_message_remove(repo)
*/
PHP_FUNCTION(git_repository_message_remove);

/* {{{ proto long git_repository_merge_cleanup(repo)
*/
PHP_FUNCTION(git_repository_merge_cleanup);

/* {{{ proto long git_repository_fetchhead_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_repository_fetchhead_foreach);

/* {{{ proto long git_repository_mergehead_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_repository_mergehead_foreach);

/* {{{ proto resource git_repository_hashfile(repo, path, type, as_path)
*/
PHP_FUNCTION(git_repository_hashfile);

/* {{{ proto long git_repository_set_head(repo, refname)
*/
PHP_FUNCTION(git_repository_set_head);

/* {{{ proto long git_repository_set_head_detached(repo, commitish)
*/
PHP_FUNCTION(git_repository_set_head_detached);

/* {{{ proto long git_repository_detach_head(repo)
*/
PHP_FUNCTION(git_repository_detach_head);

/* {{{ proto long git_repository_state(repo)
*/
PHP_FUNCTION(git_repository_state);

/* {{{ proto long git_repository_set_namespace(repo, nmspace)
*/
PHP_FUNCTION(git_repository_set_namespace);

/* {{{ proto long git_repository_is_shallow(repo)
*/
PHP_FUNCTION(git_repository_is_shallow);

/* {{{ proto array git_repository_init_options_new()
*/
PHP_FUNCTION(git_repository_init_options_new);

#endif