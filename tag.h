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
#ifndef PHP_GIT2_TAG_H
#define PHP_GIT2_TAG_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_lookup_prefix, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_free, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_id, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_target, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_target_id, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_target_type, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_name, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_tagger, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_message, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_create, 0, 0, 6)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, tag_name)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, tagger)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_annotation_create, 0, 0, 5)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, tag_name)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, tagger)
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_create_frombuffer, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, buffer)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_create_lightweight, 0, 0, 4)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, tag_name)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_delete, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, tag_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_list, 0, 0, 2)
	ZEND_ARG_INFO(0, tag_names)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_list_match, 0, 0, 3)
	ZEND_ARG_INFO(0, tag_names)
	ZEND_ARG_INFO(0, pattern)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_tag_peel, 0, 0, 1)
	ZEND_ARG_INFO(0, tag)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_tag_lookup(repo, id)
*/
PHP_FUNCTION(git_tag_lookup);

/* {{{ proto resource git_tag_lookup_prefix(repo, id, len)
*/
PHP_FUNCTION(git_tag_lookup_prefix);

/* {{{ proto void git_tag_free(tag)
*/
PHP_FUNCTION(git_tag_free);

/* {{{ proto resource git_tag_id(tag)
*/
PHP_FUNCTION(git_tag_id);

/* {{{ proto resource git_tag_owner(tag)
*/
PHP_FUNCTION(git_tag_owner);

/* {{{ proto resource git_tag_target(tag)
*/
PHP_FUNCTION(git_tag_target);

/* {{{ proto resource git_tag_target_id(tag)
*/
PHP_FUNCTION(git_tag_target_id);

/* {{{ proto resource git_tag_target_type(tag)
*/
PHP_FUNCTION(git_tag_target_type);

/* {{{ proto resource git_tag_name(tag)
*/
PHP_FUNCTION(git_tag_name);

/* {{{ proto resource git_tag_tagger(tag)
*/
PHP_FUNCTION(git_tag_tagger);

/* {{{ proto resource git_tag_message(tag)
*/
PHP_FUNCTION(git_tag_message);

/* {{{ proto resource git_tag_create(repo, tag_name, target, tagger, message, force)
*/
PHP_FUNCTION(git_tag_create);

/* {{{ proto resource git_tag_annotation_create(repo, tag_name, target, tagger, message)
*/
PHP_FUNCTION(git_tag_annotation_create);

/* {{{ proto resource git_tag_create_frombuffer(repo, buffer, force)
*/
PHP_FUNCTION(git_tag_create_frombuffer);

/* {{{ proto resource git_tag_create_lightweight(repo, tag_name, target, force)
*/
PHP_FUNCTION(git_tag_create_lightweight);

/* {{{ proto long git_tag_delete(repo, tag_name)
*/
PHP_FUNCTION(git_tag_delete);

/* {{{ proto long git_tag_list(tag_names, repo)
*/
PHP_FUNCTION(git_tag_list);

/* {{{ proto long git_tag_list_match(tag_names, pattern, repo)
*/
PHP_FUNCTION(git_tag_list_match);

/* {{{ proto long git_tag_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_tag_foreach);

/* {{{ proto resource git_tag_peel(tag)
*/
PHP_FUNCTION(git_tag_peel);

#endif