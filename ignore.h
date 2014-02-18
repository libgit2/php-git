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
#ifndef PHP_GIT2_IGNORE_H
#define PHP_GIT2_IGNORE_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_ignore_add_rule, 0, 0, 2)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, rules)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_ignore_clear_internal_rules, 0, 0, 1)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_ignore_path_is_ignored, 0, 0, 3)
	ZEND_ARG_INFO(0, ignored)
	ZEND_ARG_INFO(0, repo)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

/* {{{ proto long git_ignore_add_rule(repo, rules)
*/
PHP_FUNCTION(git_ignore_add_rule);

/* {{{ proto long git_ignore_clear_internal_rules(repo)
*/
PHP_FUNCTION(git_ignore_clear_internal_rules);

/* {{{ proto long git_ignore_path_is_ignored(ignored, repo, path)
*/
PHP_FUNCTION(git_ignore_path_is_ignored);

#endif