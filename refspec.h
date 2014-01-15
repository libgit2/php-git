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
#ifndef PHP_GIT2_REFSPEC_H
#define PHP_GIT2_REFSPEC_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_src, 0, 0, 1)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_dst, 0, 0, 1)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_string, 0, 0, 1)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_force, 0, 0, 1)
	ZEND_ARG_INFO(0, refspec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_direction, 0, 0, 1)
	ZEND_ARG_INFO(0, spec)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_src_matches, 0, 0, 2)
	ZEND_ARG_INFO(0, refspec)
	ZEND_ARG_INFO(0, refname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_dst_matches, 0, 0, 2)
	ZEND_ARG_INFO(0, refspec)
	ZEND_ARG_INFO(0, refname)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_transform, 0, 0, 4)
	ZEND_ARG_INFO(0, out)
	ZEND_ARG_INFO(0, outlen)
	ZEND_ARG_INFO(0, spec)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_refspec_rtransform, 0, 0, 4)
	ZEND_ARG_INFO(0, out)
	ZEND_ARG_INFO(0, outlen)
	ZEND_ARG_INFO(0, spec)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

/* {{{ proto string git_refspec_src(resource $refspec)
 */
PHP_FUNCTION(git_refspec_src);

/* {{{ proto string git_refspec_dst(resource $refspec)
 */
PHP_FUNCTION(git_refspec_dst);

/* {{{ proto string git_refspec_string(resource $refspec)
 */
PHP_FUNCTION(git_refspec_string);

/* {{{ proto long git_refspec_force(resource $refspec)
 */
PHP_FUNCTION(git_refspec_force);

/* {{{ proto resource git_refspec_direction(resource $spec)
 */
PHP_FUNCTION(git_refspec_direction);

/* {{{ proto long git_refspec_src_matches(resource $refspec, string $refname)
 */
PHP_FUNCTION(git_refspec_src_matches);

/* {{{ proto long git_refspec_dst_matches(resource $refspec, string $refname)
 */
PHP_FUNCTION(git_refspec_dst_matches);

/* {{{ proto resource git_refspec_transform(long $outlen, resource $spec, string $name)
 */
PHP_FUNCTION(git_refspec_transform);

/* {{{ proto resource git_refspec_rtransform(long $outlen, resource $spec, string $name)
 */
PHP_FUNCTION(git_refspec_rtransform);

#endif
