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
#ifndef PHP_GIT2_ODB_H
#define PHP_GIT2_ODB_H

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_new, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_open, 0, 0, 1)
	ZEND_ARG_INFO(0, objects_dir)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_add_disk_alternate, 0, 0, 2)
	ZEND_ARG_INFO(0, odb)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_free, 0, 0, 1)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_read, 0, 0, 2)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_read_prefix, 0, 0, 3)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, short_id)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_read_header, 0, 0, 3)
	ZEND_ARG_INFO(0, type_out)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_exists, 0, 0, 2)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_refresh, 0, 0, 1)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_foreach, 0, 0, 3)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, cb)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_write, 0, 0, 4)
	ZEND_ARG_INFO(0, odb)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, len)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_open_wstream, 0, 0, 3)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, size)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_stream_write, 0, 0, 2)
	ZEND_ARG_INFO(0, buffer)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_stream_finalize_write, 0, 0, 1)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_stream_read, 0, 0, 3)
	ZEND_ARG_INFO(0, stream)
	ZEND_ARG_INFO(0, buffer)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_stream_free, 0, 0, 1)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_open_rstream, 0, 0, 2)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_write_pack, 0, 0, 3)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, progress_cb)
	ZEND_ARG_INFO(0, progress_payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_hash, 0, 0, 3)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, len)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_hashfile, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_object_dup, 0, 0, 1)
	ZEND_ARG_INFO(0, source)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_object_free, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_object_id, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_object_data, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_object_size, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_object_type, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_add_backend, 0, 0, 3)
	ZEND_ARG_INFO(0, odb)
	ZEND_ARG_INFO(0, backend)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_add_alternate, 0, 0, 3)
	ZEND_ARG_INFO(0, odb)
	ZEND_ARG_INFO(0, backend)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_num_backends, 0, 0, 1)
	ZEND_ARG_INFO(0, odb)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_odb_get_backend, 0, 0, 2)
	ZEND_ARG_INFO(0, odb)
	ZEND_ARG_INFO(0, pos)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_odb_new()
*/
PHP_FUNCTION(git_odb_new);

/* {{{ proto resource git_odb_open(objects_dir)
*/
PHP_FUNCTION(git_odb_open);

/* {{{ proto long git_odb_add_disk_alternate(odb, path)
*/
PHP_FUNCTION(git_odb_add_disk_alternate);

/* {{{ proto void git_odb_free(db)
*/
PHP_FUNCTION(git_odb_free);

/* {{{ proto resource git_odb_read(db, id)
*/
PHP_FUNCTION(git_odb_read);

/* {{{ proto resource git_odb_read_prefix(db, short_id, len)
*/
PHP_FUNCTION(git_odb_read_prefix);

/* {{{ proto resource git_odb_read_header(type_out, db, id)
*/
PHP_FUNCTION(git_odb_read_header);

/* {{{ proto long git_odb_exists(db, id)
*/
PHP_FUNCTION(git_odb_exists);

/* {{{ proto long git_odb_refresh(db)
*/
PHP_FUNCTION(git_odb_refresh);

/* {{{ proto long git_odb_foreach(db, cb, payload)
*/
PHP_FUNCTION(git_odb_foreach);

/* {{{ proto resource git_odb_write(odb, data, len, type)
*/
PHP_FUNCTION(git_odb_write);

/* {{{ proto resource git_odb_open_wstream(db, size, type)
*/
PHP_FUNCTION(git_odb_open_wstream);

/* {{{ proto resource git_odb_stream_write(buffer, len)
*/
PHP_FUNCTION(git_odb_stream_write);

/* {{{ proto resource git_odb_stream_finalize_write(stream)
*/
PHP_FUNCTION(git_odb_stream_finalize_write);

/* {{{ proto long git_odb_stream_read(stream, buffer, len)
*/
PHP_FUNCTION(git_odb_stream_read);

/* {{{ proto void git_odb_stream_free(stream)
*/
PHP_FUNCTION(git_odb_stream_free);

/* {{{ proto resource git_odb_open_rstream(db, oid)
*/
PHP_FUNCTION(git_odb_open_rstream);

/* {{{ proto resource git_odb_write_pack(db, progress_cb, progress_payload)
*/
PHP_FUNCTION(git_odb_write_pack);

/* {{{ proto resource git_odb_hash(data, len, type)
*/
PHP_FUNCTION(git_odb_hash);

/* {{{ proto resource git_odb_hashfile(path, type)
*/
PHP_FUNCTION(git_odb_hashfile);

/* {{{ proto resource git_odb_object_dup(source)
*/
PHP_FUNCTION(git_odb_object_dup);

/* {{{ proto void git_odb_object_free(object)
*/
PHP_FUNCTION(git_odb_object_free);

/* {{{ proto resource git_odb_object_id(object)
*/
PHP_FUNCTION(git_odb_object_id);

/* {{{ proto resource git_odb_object_data(object)
*/
PHP_FUNCTION(git_odb_object_data);

/* {{{ proto resource git_odb_object_size(object)
*/
PHP_FUNCTION(git_odb_object_size);

/* {{{ proto resource git_odb_object_type(object)
*/
PHP_FUNCTION(git_odb_object_type);

/* {{{ proto long git_odb_add_backend(odb, backend, priority)
*/
PHP_FUNCTION(git_odb_add_backend);

/* {{{ proto long git_odb_add_alternate(odb, backend, priority)
*/
PHP_FUNCTION(git_odb_add_alternate);

/* {{{ proto resource git_odb_num_backends(odb)
*/
PHP_FUNCTION(git_odb_num_backends);

/* {{{ proto resource git_odb_get_backend(odb, pos)
*/
PHP_FUNCTION(git_odb_get_backend);

#endif