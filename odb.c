/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2012 Shuhei Tanuma
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

#include "php_git2.h"

PHPAPI zend_class_entry *git2_odb_class_entry;
static zend_object_handlers git2_odb_object_handlers;

static void php_git2_odb_free_storage(php_git2_odb *object TSRMLS_DC)
{
	if (object->odb != NULL) {
		git_odb_free(object->odb);
		object->odb = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_odb_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_odb);
	retval.handlers = &git2_odb_object_handlers;
	return retval;
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_odb_hash, 0,0,2)
	ZEND_ARG_INFO(0, contents)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_odb_write, 0,0,2)
	ZEND_ARG_INFO(0, contents)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_odb_exists, 0,0,1)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_odb_read, 0,0,1)
	ZEND_ARG_INFO(0, oid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_odb_add_alternate, 0,0,2)
	ZEND_ARG_INFO(0, backend)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_odb_add_backend, 0,0,2)
	ZEND_ARG_INFO(0, backend)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\ODB::hash(string $contents, int $type)
*/
PHP_METHOD(git2_odb, hash)
{
	char *contents;
	int contents_len = 0;
	long type = 0;
	git_odb *odb;
	git_oid oid;
	char *oid_out[GIT_OID_HEXSZ+1];
	int error = 0;
	php_git2_odb *m_odb;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &contents, &contents_len, &type) == FAILURE) {
		return;
	}
	m_odb = PHP_GIT2_GET_OBJECT(php_git2_odb, getThis());
	
	error = git_odb_hash(&oid, contents,contents_len, type);
	PHP_GIT2_EXCEPTION_CHECK(error);
	
	git_oid_fmt(oid_out, &oid);
	RETURN_STRINGL(oid_out,GIT_OID_HEXSZ,1);
}
/* }}} */

/*
{{{ proto: Git2\ODB::write(string $contents, int $type)
*/
PHP_METHOD(git2_odb, write)
{
	char *contents;
	int contents_len = 0;
	long type = 0;
	git_odb_stream *stream;
	git_odb *odb;
	git_oid oid;
	char *oid_out[GIT_OID_HEXSZ+1];
	int error = 0;
	php_git2_odb *m_odb;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &contents, &contents_len, &type) == FAILURE) {
		return;
	}
	m_odb = PHP_GIT2_GET_OBJECT(php_git2_odb, getThis());
		
	error = git_odb_open_wstream(&stream, m_odb->odb, contents_len, (git_otype)type);
	PHP_GIT2_EXCEPTION_CHECK(error);
		
	error = stream->write(stream, contents, contents_len);
	PHP_GIT2_EXCEPTION_CHECK(error);

	error = stream->finalize_write(&oid, stream);
	PHP_GIT2_EXCEPTION_CHECK(error);
	
	git_oid_fmt(oid_out, &oid);
	RETURN_STRINGL(oid_out,GIT_OID_HEXSZ,1);
}
/* }}} */

/*
{{{ proto: Git2\ODB::exists($oid)
*/
PHP_METHOD(git2_odb, exists)
{
	char *hash;
	int error, hash_len = 0;
	git_odb *odb;
	git_oid id;
	php_git2_odb *m_odb;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &hash, &hash_len) == FAILURE) {
		return;
	}
	
	m_odb = PHP_GIT2_GET_OBJECT(php_git2_odb, getThis());

	if (git_oid_fromstr(&id, hash) != GIT_SUCCESS) {
		RETURN_FALSE;
	}
	
	if (git_odb_exists(m_odb->odb, &id) == 1) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\ODB::read($oid)
*/
PHP_METHOD(git2_odb, read)
{
	char *hash;
	int error, hash_len = 0;
	git_odb *odb;
	git_oid id;
	git_odb_object *object;
	zval *raw;
	php_git2_odb *m_odb;
	php_git2_odb_object *m_odb_object;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &hash, &hash_len) == FAILURE) {
		return;
	}
	
	m_odb = PHP_GIT2_GET_OBJECT(php_git2_odb, getThis());
	if (git_oid_fromstr(&id, hash) != GIT_SUCCESS) {
		RETURN_FALSE;
	}
	
	error = git_odb_read(&object,m_odb->odb, &id);
	PHP_GIT2_EXCEPTION_CHECK(error);
	
	MAKE_STD_ZVAL(raw);
	object_init_ex(raw, git2_odb_object_class_entry);
	m_odb_object = PHP_GIT2_GET_OBJECT(php_git2_odb_object, raw);
	m_odb_object->object = object;

	RETVAL_ZVAL(raw, 0, 1);
}
/* }}} */


/*
{{{ proto: Git2\ODB::addAlternate(Git2\Backend $backend, $priority)
*/
PHP_METHOD(git2_odb, addAlternate)
{
}
/* }}} */

/*
{{{ proto: Git2\ODB::addBackend(Git2\Backend $backend, $priority)
*/
PHP_METHOD(git2_odb, addBackend)
{
}
/* }}} */


static zend_function_entry php_git2_odb_methods[] = {
	PHP_ME(git2_odb, hash,         arginfo_git2_odb_hash,          ZEND_ACC_PUBLIC)
	PHP_ME(git2_odb, write,        arginfo_git2_odb_write,         ZEND_ACC_PUBLIC)
	PHP_ME(git2_odb, exists,       arginfo_git2_odb_exists,        ZEND_ACC_PUBLIC)
	PHP_ME(git2_odb, read,         arginfo_git2_odb_read,          ZEND_ACC_PUBLIC)
	PHP_ME(git2_odb, addAlternate, arginfo_git2_odb_add_alternate, ZEND_ACC_PUBLIC)
	PHP_ME(git2_odb, addBackend,   arginfo_git2_odb_add_backend,   ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_odb_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "ODB", php_git2_odb_methods);
	git2_odb_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_odb_class_entry->create_object = php_git2_odb_new;

	memcpy(&git2_odb_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	git2_odb_object_handlers.clone_obj = NULL;
}