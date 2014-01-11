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
#ifndef PHP_GIT2_G_CONFIG_H
#define PHP_GIT2_G_CONFIG_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_find_global, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_find_xdg, 0, 0, 2)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_find_system, 0, 0, 2)
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_open_default, 0, 0, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_new, 0, 0, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_add_file_ondisk, 0, 0, 4)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, level)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_open_ondisk, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_open_level, 0, 0, 3)
	ZEND_ARG_INFO(0, parent)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_open_global, 0, 0, 2)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_refresh, 0, 0, 1)
	ZEND_ARG_INFO(0, cfg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_free, 0, 0, 1)
	ZEND_ARG_INFO(0, cfg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_entry, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_int32, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_int64, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_bool, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_string, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_multivar_foreach, 0, 0, 5)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, regexp)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_multivar_iterator_new, 0, 0, 4)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, regexp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_next, 0, 0, 2)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_iterator_free, 0, 0, 1)
	ZEND_ARG_INFO(0, iter)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_set_int32, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_set_int64, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_set_bool, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_set_string, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_set_multivar, 0, 0, 4)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, regexp)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_delete_entry, 0, 0, 2)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_delete_multivar, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, regexp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_iterator_new, 0, 0, 2)
	ZEND_ARG_INFO(0, cfg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_iterator_glob_new, 0, 0, 3)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, regexp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_foreach_match, 0, 0, 4)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, regexp)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_get_mapped, 0, 0, 5)
	ZEND_ARG_INFO(0, cfg)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, maps)
	ZEND_ARG_INFO(0, map_n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_lookup_map_value, 0, 0, 4)
	ZEND_ARG_INFO(0, maps)
	ZEND_ARG_INFO(0, map_n)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_parse_bool, 0, 0, 2)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_parse_int32, 0, 0, 2)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_parse_int64, 0, 0, 2)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_backend_foreach_match, 0, 0, 5)
	ZEND_ARG_INFO(0, backend)
	ZEND_ARG_INFO(0, regexp)
//	ZEND_ARG_INFO(0, )
//	ZEND_ARG_INFO(0, ))
//	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_config_find_global(length)
*/
PHP_FUNCTION(git_config_find_global);

/* {{{ proto resource git_config_find_xdg(length)
*/
PHP_FUNCTION(git_config_find_xdg);

/* {{{ proto resource git_config_find_system(length)
*/
PHP_FUNCTION(git_config_find_system);

/* {{{ proto resource git_config_open_default()
*/
PHP_FUNCTION(git_config_open_default);

/* {{{ proto resource git_config_new()
*/
PHP_FUNCTION(git_config_new);

/* {{{ proto long git_config_add_file_ondisk(cfg, path, level, force)
*/
PHP_FUNCTION(git_config_add_file_ondisk);

/* {{{ proto resource git_config_open_ondisk(path)
*/
PHP_FUNCTION(git_config_open_ondisk);

/* {{{ proto resource git_config_open_level(parent, level)
*/
PHP_FUNCTION(git_config_open_level);

/* {{{ proto resource git_config_open_global(config)
*/
PHP_FUNCTION(git_config_open_global);

/* {{{ proto long git_config_refresh(cfg)
*/
PHP_FUNCTION(git_config_refresh);

/* {{{ proto void git_config_free(cfg)
*/
PHP_FUNCTION(git_config_free);

/* {{{ proto resource git_config_get_entry(cfg, name)
*/
PHP_FUNCTION(git_config_get_entry);

/* {{{ proto resource git_config_get_int32(cfg, name)
*/
PHP_FUNCTION(git_config_get_int32);

/* {{{ proto resource git_config_get_int64(cfg, name)
*/
PHP_FUNCTION(git_config_get_int64);

/* {{{ proto resource git_config_get_bool(cfg, name)
*/
PHP_FUNCTION(git_config_get_bool);

/* {{{ proto resource git_config_get_string(cfg, name)
*/
PHP_FUNCTION(git_config_get_string);

/* {{{ proto long git_config_get_multivar_foreach(cfg, name, regexp, callback, payload)
*/
PHP_FUNCTION(git_config_get_multivar_foreach);

/* {{{ proto resource git_config_multivar_iterator_new(cfg, name, regexp)
*/
PHP_FUNCTION(git_config_multivar_iterator_new);

/* {{{ proto resource git_config_next(iter)
*/
PHP_FUNCTION(git_config_next);

/* {{{ proto void git_config_iterator_free(iter)
*/
PHP_FUNCTION(git_config_iterator_free);

/* {{{ proto long git_config_set_int32(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_int32);

/* {{{ proto long git_config_set_int64(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_int64);

/* {{{ proto long git_config_set_bool(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_bool);

/* {{{ proto long git_config_set_string(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_string);

/* {{{ proto long git_config_set_multivar(cfg, name, regexp, value)
*/
PHP_FUNCTION(git_config_set_multivar);

/* {{{ proto long git_config_delete_entry(cfg, name)
*/
PHP_FUNCTION(git_config_delete_entry);

/* {{{ proto long git_config_delete_multivar(cfg, name, regexp)
*/
PHP_FUNCTION(git_config_delete_multivar);

/* {{{ proto long git_config_foreach(cfg, callback, payload)
*/
PHP_FUNCTION(git_config_foreach);

/* {{{ proto resource git_config_iterator_new(cfg)
*/
PHP_FUNCTION(git_config_iterator_new);

/* {{{ proto resource git_config_iterator_glob_new(cfg, regexp)
*/
PHP_FUNCTION(git_config_iterator_glob_new);

/* {{{ proto long git_config_foreach_match(cfg, regexp, callback, payload)
*/
PHP_FUNCTION(git_config_foreach_match);

/* {{{ proto resource git_config_get_mapped(cfg, name, maps, map_n)
*/
PHP_FUNCTION(git_config_get_mapped);

/* {{{ proto resource git_config_lookup_map_value(maps, map_n, value)
*/
PHP_FUNCTION(git_config_lookup_map_value);

/* {{{ proto resource git_config_parse_bool(value)
*/
PHP_FUNCTION(git_config_parse_bool);

/* {{{ proto resource git_config_parse_int32(value)
*/
PHP_FUNCTION(git_config_parse_int32);

/* {{{ proto resource git_config_parse_int64(value)
*/
PHP_FUNCTION(git_config_parse_int64);

/* {{{ proto long git_config_backend_foreach_match(backend, regexp, , ), data)
*/
PHP_FUNCTION(git_config_backend_foreach_match);

#endif