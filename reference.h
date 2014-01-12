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
#ifndef PHP_GIT2_REFERENCE_H
#define PHP_GIT2_REFERENCE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_name_to_id, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_dwim, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, shorthand)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_symbolic_create, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_create, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_target, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_target_peel, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_symbolic_target, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_type, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_name, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_resolve, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_symbolic_set_target, 0, 0, 2)
	ZEND_ARG_INFO(0, ref)
	ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_set_target, 0, 0, 2)
	ZEND_ARG_INFO(0, ref)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_rename, 0, 0, 3)
	ZEND_ARG_INFO(0, ref)
	ZEND_ARG_INFO(0, new_name)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_delete, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_list, 0, 0, 2)
	ZEND_ARG_INFO(0, array)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_foreach_name, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_free, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_cmp, 0, 0, 2)
	ZEND_ARG_INFO(0, ref1)
	ZEND_ARG_INFO(0, ref2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_iterator_new, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_iterator_glob_new, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, glob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_next, 0, 0, 1)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_next_name, 0, 0, 1)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_iterator_free, 0, 0, 1)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_foreach_glob, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, glob)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_has_log, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_is_branch, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_is_remote, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_is_tag, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_normalize_name, 0, 0, 4)
	ZEND_ARG_INFO(0, buffer_size)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_peel, 0, 0, 2)
	ZEND_ARG_INFO(0, ref)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_is_valid_name, 0, 0, 1)
	ZEND_ARG_INFO(0, refname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_shorthand, 0, 0, 1)
	ZEND_ARG_INFO(0, ref)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_reference_lookup(repo, name)
*/
PHP_FUNCTION(git_reference_lookup);

/* {{{ proto resource git_reference_name_to_id(repo, name)
*/
PHP_FUNCTION(git_reference_name_to_id);

/* {{{ proto resource git_reference_dwim(repo, shorthand)
*/
PHP_FUNCTION(git_reference_dwim);

/* {{{ proto resource git_reference_symbolic_create(repo, name, target, force)
*/
PHP_FUNCTION(git_reference_symbolic_create);

/* {{{ proto resource git_reference_create(repo, name, id, force)
*/
PHP_FUNCTION(git_reference_create);

/* {{{ proto resource git_reference_target(ref)
*/
PHP_FUNCTION(git_reference_target);

/* {{{ proto resource git_reference_target_peel(ref)
*/
PHP_FUNCTION(git_reference_target_peel);

/* {{{ proto resource git_reference_symbolic_target(ref)
*/
PHP_FUNCTION(git_reference_symbolic_target);

/* {{{ proto resource git_reference_type(ref)
*/
PHP_FUNCTION(git_reference_type);

/* {{{ proto resource git_reference_name(ref)
*/
PHP_FUNCTION(git_reference_name);

/* {{{ proto resource git_reference_resolve(ref)
*/
PHP_FUNCTION(git_reference_resolve);

/* {{{ proto resource git_reference_owner(ref)
*/
PHP_FUNCTION(git_reference_owner);

/* {{{ proto resource git_reference_symbolic_set_target(ref, target)
*/
PHP_FUNCTION(git_reference_symbolic_set_target);

/* {{{ proto resource git_reference_set_target(ref, id)
*/
PHP_FUNCTION(git_reference_set_target);

/* {{{ proto resource git_reference_rename(ref, new_name, force)
*/
PHP_FUNCTION(git_reference_rename);

/* {{{ proto long git_reference_delete(ref)
*/
PHP_FUNCTION(git_reference_delete);

/* {{{ proto long git_reference_list(array, repo)
*/
PHP_FUNCTION(git_reference_list);

/* {{{ proto long git_reference_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_reference_foreach);

/* {{{ proto long git_reference_foreach_name(repo, callback, payload)
*/
PHP_FUNCTION(git_reference_foreach_name);

/* {{{ proto void git_reference_free(ref)
*/
PHP_FUNCTION(git_reference_free);

/* {{{ proto long git_reference_cmp(ref1, ref2)
*/
PHP_FUNCTION(git_reference_cmp);

/* {{{ proto resource git_reference_iterator_new(repo)
*/
PHP_FUNCTION(git_reference_iterator_new);

/* {{{ proto resource git_reference_iterator_glob_new(repo, glob)
*/
PHP_FUNCTION(git_reference_iterator_glob_new);

/* {{{ proto resource git_reference_next(iter)
*/
PHP_FUNCTION(git_reference_next);

/* {{{ proto resource git_reference_next_name(iter)
*/
PHP_FUNCTION(git_reference_next_name);

/* {{{ proto void git_reference_iterator_free(iter)
*/
PHP_FUNCTION(git_reference_iterator_free);

/* {{{ proto long git_reference_foreach_glob(repo, glob, callback, payload)
*/
PHP_FUNCTION(git_reference_foreach_glob);

/* {{{ proto long git_reference_has_log(ref)
*/
PHP_FUNCTION(git_reference_has_log);

/* {{{ proto long git_reference_is_branch(ref)
*/
PHP_FUNCTION(git_reference_is_branch);

/* {{{ proto long git_reference_is_remote(ref)
*/
PHP_FUNCTION(git_reference_is_remote);

/* {{{ proto long git_reference_is_tag(ref)
*/
PHP_FUNCTION(git_reference_is_tag);

/* {{{ proto resource git_reference_normalize_name(buffer_size, name, flags)
*/
PHP_FUNCTION(git_reference_normalize_name);

/* {{{ proto resource git_reference_peel(ref, type)
*/
PHP_FUNCTION(git_reference_peel);

/* {{{ proto long git_reference_is_valid_name(refname)
*/
PHP_FUNCTION(git_reference_is_valid_name);

/* {{{ proto resource git_reference_shorthand(ref)
*/
PHP_FUNCTION(git_reference_shorthand);

#endif