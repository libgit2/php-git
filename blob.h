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
#ifndef PHP_GIT2_BLOB_H
#define PHP_GIT2_BLOB_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_create_frombuffer, 0, 0, 2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, buffer)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_create_fromchunks, 0, 0, 3)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, hintpath)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_create_fromdisk, 0, 0, 2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_create_fromworkdir, 0, 0, 2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, relative_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_filtered_content, 0, 0, 2)
	ZEND_ARG_INFO(0, blob)
	ZEND_ARG_INFO(0, as_path)
	ZEND_ARG_INFO(0, check_for_binary_data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_free, 0, 0, 1)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_id, 0, 0, 1)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_is_binary, 0, 0, 1)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_lookup_prefix, 0, 0, 3)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_rawcontent, 0, 0, 1)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_blob_rawsize, 0, 0, 1)
	ZEND_ARG_INFO(0, blob)
ZEND_END_ARG_INFO()


/* {{{ proto resource git_blob_create_frombuffer(resource $repository, string $buffer)
*/
PHP_FUNCTION(git_blob_create_frombuffer);

/* {{{ proto resource git_blob_create_fromchunks(resource $repository, string $hintpath, Callable $callback, mixed payload)
*/
PHP_FUNCTION(git_blob_create_fromchunks);

/* {{{ proto resource git_blob_create_fromdisk(resource $repository, string $path)
*/
PHP_FUNCTION(git_blob_create_fromdisk);

/* {{{ proto resource git_blob_create_fromworkdir(resource $repository, string $relative_path)
*/
PHP_FUNCTION(git_blob_create_fromworkdir);


/* {{{ proto resource git_blob_filtered_content($blob, $as_path, $check_for_binary_data)
*/
PHP_FUNCTION(git_blob_filtered_content);

/* {{{ proto resource git_blob_free(resource $blob)
*/
PHP_FUNCTION(git_blob_free);

/* {{{ proto resource git_blob_id(resource $blob)
*/
PHP_FUNCTION(git_blob_id);

/* {{{ proto resource git_blob_is_binary(resource $blob)
*/
PHP_FUNCTION(git_blob_is_binary);

/* {{{ proto resource git_blob_lookup(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_lookup);

/* {{{ proto resource git_blob_lookup_prefix(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_lookup_prefix);

/* {{{ proto resource git_blob_owner(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_owner);

/* {{{ proto resource git_blob_rawcontent(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_rawcontent);

/* {{{ proto resource git_blob_rawsize(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_rawsize);

#endif