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
#ifndef PHP_GIT2_TREE_H
#define PHP_GIT2_TREE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_byoid, 0, 0, 2)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_byindex, 0, 0, 2)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_byname, 0, 0, 2)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_bypath, 0, 0, 2)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_id, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_name, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_type, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_filemode, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_filemode_raw, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_cmp, 0, 0, 2)
	ZEND_ARG_INFO(0, e1)
	ZEND_ARG_INFO(0, e2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_free, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_free, 0, 0, 1)
	ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_entry_dup, 0, 0, 1)
	ZEND_ARG_INFO(0, tree_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_id, 0, 0, 1)
	ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tree_walk, 0, 0, 4)
	ZEND_ARG_INFO(0, tree)
	ZEND_ARG_INFO(0, mode)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()


/* {{{ proto array git_tree_entry_byoid(resource $tree, string $oid)
*/
PHP_FUNCTION(git_tree_entry_byoid);

/* {{{ proto array git_tree_entry_byindex(resource $tree, long $index)
*/
PHP_FUNCTION(git_tree_entry_byindex);

/* {{{ proto array git_tree_entry_byname(resource $tree, string $name)
*/
PHP_FUNCTION(git_tree_entry_byname);

/* {{{ proto array git_tree_entry_bypath(resource $tree, string $path)
*/
PHP_FUNCTION(git_tree_entry_bypath);

/* {{{ proto string git_tree_entry_id(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_id);

/* {{{ proto string git_tree_entry_name(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_name);

/* {{{ proto long git_tree_entrycount(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entrycount);

/* {{{ proto long git_tree_entry_type(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_type);

/* {{{ proto long git_tree_entry_filemode(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_filemode);

/* {{{ proto long git_tree_entry_filemode_raw(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_filemode_raw);

/* {{{ proto long git_tree_entry_cmp(resource $e1, resource $e2)
*/
PHP_FUNCTION(git_tree_entry_cmp);

/* {{{ proto void git_tree_entry_free(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_free);

/* {{{ proto void git_tree_free(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_free);

/* {{{ proto resource git_tree_entry_dup(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_dup);

/* {{{ proto string git_tree_id(resource $tree)
*/
PHP_FUNCTION(git_tree_id);

/* {{{ proto resource git_tree_lookup(resource $repository, string id)
*/
PHP_FUNCTION(git_tree_lookup);

/* {{{ proto resource git_tree_owner(resource $tree)
*/
PHP_FUNCTION(git_tree_owner);

/* {{{ proto resource git_tree_walk(resource $tree, long $mode, Callable $callback, mixed $payload)
*/
PHP_FUNCTION(git_tree_walk);

#endif