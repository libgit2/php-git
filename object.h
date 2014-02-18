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
#ifndef PHP_GIT2_OBJECT_H
#define PHP_GIT2_OBJECT_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_lookup, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_lookup_prefix, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, len)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_lookup_bypath, 0, 0, 3)
	ZEND_ARG_INFO(0, treeish)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_id, 0, 0, 1)
	ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_type, 0, 0, 1)
	ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, obj)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_free, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_type2string, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_string2type, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_typeisloose, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object__size, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_peel, 0, 0, 2)
	ZEND_ARG_INFO(0, object)
	ZEND_ARG_INFO(0, target_type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_object_dup, 0, 0, 1)
	ZEND_ARG_INFO(0, source)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_object_lookup(repo, id, type)
*/
PHP_FUNCTION(git_object_lookup);

/* {{{ proto resource git_object_lookup_prefix(repo, id, len, type)
*/
PHP_FUNCTION(git_object_lookup_prefix);

/* {{{ proto resource git_object_lookup_bypath(treeish, path, type)
*/
PHP_FUNCTION(git_object_lookup_bypath);

/* {{{ proto resource git_object_id(obj)
*/
PHP_FUNCTION(git_object_id);

/* {{{ proto resource git_object_type(obj)
*/
PHP_FUNCTION(git_object_type);

/* {{{ proto resource git_object_owner(obj)
*/
PHP_FUNCTION(git_object_owner);

/* {{{ proto void git_object_free(object)
*/
PHP_FUNCTION(git_object_free);

/* {{{ proto resource git_object_type2string(type)
*/
PHP_FUNCTION(git_object_type2string);

/* {{{ proto resource git_object_string2type(str)
*/
PHP_FUNCTION(git_object_string2type);

/* {{{ proto long git_object_typeisloose(type)
*/
PHP_FUNCTION(git_object_typeisloose);

/* {{{ proto resource git_object__size(type)
*/
PHP_FUNCTION(git_object__size);

/* {{{ proto resource git_object_peel(object, target_type)
*/
PHP_FUNCTION(git_object_peel);

/* {{{ proto resource git_object_dup(source)
*/
PHP_FUNCTION(git_object_dup);

#endif