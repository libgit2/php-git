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

PHPAPI zend_class_entry *git2_repository_class_entry;
void php_git2_repository_init(TSRMLS_D);
static zend_object_handlers git2_repository_object_handlers;

static void php_git2_repository_free_storage(php_git2_repository *object TSRMLS_DC)
{
	if (object->repository != NULL) {
		git_repository_free(object->repository);
		object->repository = NULL;
	}
	
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_repository_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_repository);
	retval.handlers = &git2_repository_object_handlers;
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository___construct, 0,0,1)
	ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_init, 0,0,1)
	ZEND_ARG_INFO(0, isBare)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_discover, 0,0,3)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, across_fs)
	ZEND_ARG_INFO(0, ceiling_dirs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_exists, 0,0,1)
	ZEND_ARG_INFO(0, exists)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_write, 0,0,2)
	ZEND_ARG_INFO(0, contents)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_hash, 0,0,2)
	ZEND_ARG_INFO(0, contents)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_get_merge_base, 0,0,2)
	ZEND_ARG_INFO(0, one)
	ZEND_ARG_INFO(0, two)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_lookup, 0,0,1)
	ZEND_ARG_INFO(0, lookup)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_repository_checkout, 0,0,0)
ZEND_END_ARG_INFO()

static int php_git2_repository_initialize(zval *object, git_repository *repository TSRMLS_DC)
{
	zval *odb;
	php_git2_repository *m_repository;
	php_git2_odb *m_odb;
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, object);
	m_repository->repository = repository;

	MAKE_STD_ZVAL(odb);
	object_init_ex(odb,git2_odb_class_entry);
	m_odb = PHP_GIT2_GET_OBJECT(php_git2_odb, odb);
	git_repository_odb(&m_odb->odb,repository);
	
	add_property_string(object, "path", git_repository_path(repository),1);
	add_property_zval(object, "odb", odb);
	zval_ptr_dtor(&odb);
	
	return 0;
}

/*
{{{ proto: Git2\Repository::__construct(string $path)
*/
PHP_METHOD(git2_repository, __construct)
{
	const char *repository_path = NULL;
	int repository_path_len, ret = 0;
	git_repository *repository;
	php_git2_repository *m_repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|s", &repository_path, &repository_path_len) == FAILURE) {
		return;
	}

	if (repository_path_len > 0) {
		ret = git_repository_open(&repository, repository_path);
		PHP_GIT2_EXCEPTION_CHECK(ret);
		
		php_git2_repository_initialize(getThis(), repository TSRMLS_CC);
	} else {
		m_repository->repository = NULL;
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::isEmpty()
*/
PHP_METHOD(git2_repository, isEmpty)
{
	php_git2_repository *m_repository;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		if (git_repository_is_empty(m_repository->repository)) {
			RETURN_TRUE;
		} else {
			RETURN_FALSE;
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::isBare()
*/
PHP_METHOD(git2_repository, isBare)
{
	php_git2_repository *m_repository;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		if (git_repository_is_bare(m_repository->repository) == 1) {
			RETURN_TRUE;
		} else {
			RETURN_FALSE;
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::getPath()
*/
PHP_METHOD(git2_repository, getPath)
{
	php_git2_repository *m_repository;
	const char *path = NULL;
	zval *m_path = NULL;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		path = git_repository_path(m_repository->repository);
		if (path != NULL) {
			MAKE_STD_ZVAL(m_path);
			ZVAL_STRING(m_path, path, 1);
			RETVAL_ZVAL(m_path,0,1);
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::getWorkdir()
*/
PHP_METHOD(git2_repository, getWorkdir)
{
	php_git2_repository *m_repository;
	const char *path = NULL;
	zval *m_path = NULL;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		path = git_repository_workdir(m_repository->repository);
		if (path != NULL) {
			MAKE_STD_ZVAL(m_path);
			ZVAL_STRING(m_path, path, 1);
			RETVAL_ZVAL(m_path,0,1);
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */


/*
{{{ proto: Git2\Repository::init(string $path [, bool isBare])
*/
PHP_METHOD(git2_repository, init)
{
	char *path;
	int ret, path_len = 0;
	zend_bool is_bare = 0;
	git_repository *repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s|b", &path, &path_len, &is_bare) == FAILURE) {
		return;
	}
	
	ret = git_repository_init(&repository, path, is_bare);
	if (ret == GIT_OK) {
		zval *object;
		
		MAKE_STD_ZVAL(object);
		object_init_ex(object, git2_repository_class_entry);
		php_git2_repository_initialize(object, repository TSRMLS_CC);
		
		RETVAL_ZVAL(object,0,1);
	} else {
		php_git2_exception_check(ret TSRMLS_CC);
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::headDetached()
	A repository's HEAD is detached when it points directly to a commit instead of a branch.
*/
PHP_METHOD(git2_repository, headDetached)
{
	php_git2_repository *m_repository;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		if (git_repository_head_detached(m_repository->repository) == 1) {
			RETURN_TRUE;
		} else {
			RETURN_FALSE;
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::headOrphan()
 An orphan branch is one named from HEAD but which doesn't exist in	
 the refs namespace, because it doesn't have any commit to point to.
*/                                                                                           
PHP_METHOD(git2_repository, headOrphan)
{
	php_git2_repository *m_repository;

	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	if (m_repository->repository != NULL) {
		if (git_repository_head_orphan(m_repository->repository) == 1) {
			RETURN_TRUE;
		} else {
			RETURN_FALSE;
		}
	} else {
		/* @todo: throws an exectpion */
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::discover(string $path[, bool across_fs, string ceiling_dirs])
*/
PHP_METHOD(git2_repository, discover)
{
	char path_buffer[1024] = {0};
	size_t path_size = 1024;
	zend_bool across_fs = 1;
	char *start_path, *ceiling_dirs = NULL;
	int start_path_len, ceiling_dirs_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s|bs", &start_path, &start_path_len, &across_fs, &ceiling_dirs, & ceiling_dirs_len) == FAILURE) {
		return;
	}
	
	if (git_repository_discover(path_buffer,path_size,(const char *)start_path,(int)across_fs, (const char *)ceiling_dirs) == GIT_OK) {
		RETVAL_STRING(path_buffer, 1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Repository::exists(string $sha1)
*/
PHP_METHOD(git2_repository, exists)
{
	char *hash;
	int error, hash_len = 0;
	git_odb *odb;
	git_oid id;
	php_git2_repository *m_repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &hash, &hash_len) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	error = git_repository_odb(&odb, m_repository->repository);
	PHP_GIT2_EXCEPTION_CHECK(error);

	if (git_oid_fromstr(&id, hash) != GIT_OK) {
		RETURN_FALSE;
	}
	
	if (git_odb_exists(odb, &id) == 1) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


/*
{{{ proto: Git2\Repository::getMergeBase(string $oid_one, string $oid_two)
*/
PHP_METHOD(git2_repository, getMergeBase)
{
	char *one, *two, oid_out[GIT_OID_HEXSZ];
	int error, one_len = 0, two_len = 0;
	git_oid out, one_id, two_id;
	php_git2_repository *m_repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss", &one, &one_len, &two, &two_len) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());

	if (git_oid_fromstrn(&one_id, one, one_len) != GIT_OK) {
		RETURN_FALSE;
	}

	if (git_oid_fromstrn(&two_id, two, two_len) != GIT_OK) {
		RETURN_FALSE;
	}

	error = git_merge_base(&out, m_repository->repository, &one_id, &two_id);
	if (error == GIT_OK) {
		git_oid_fmt(oid_out, &out);
		RETURN_STRINGL(oid_out, GIT_OID_HEXSZ, 1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */




/*
{{{ proto: Git2\Repository::lookup(string $sha1[, int type = GIT_OBJ_ANY])
*/
PHP_METHOD(git2_repository, lookup)
{
	char *hash;
	int error, hash_len = 0;
	git_odb *odb;
	git_oid id;
	git_object *object;
	long type = GIT_OBJ_ANY;
	php_git2_repository *m_repository;
	zval *result = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s|l", &hash, &hash_len, type) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	error = git_repository_odb(&odb, m_repository->repository);
	PHP_GIT2_EXCEPTION_CHECK(error);

	if (git_oid_fromstrn(&id, hash, hash_len) != GIT_OK) {
		RETURN_FALSE;
	}
	
	if (hash_len < GIT_OID_HEXSZ) {
		error = git_object_lookup_prefix(&object, m_repository->repository, &id, hash_len, (git_otype)type);
	} else {
		error = git_object_lookup(&object, m_repository->repository, &id, (git_otype)type);
	}
	
	result = php_git2_object_new(m_repository->repository, object TSRMLS_CC);
	RETVAL_ZVAL(result,0,1);
}
/* }}} */

/*
{{{ proto: Git2\Repository::write(string $contents, int $type)
*/
PHP_METHOD(git2_repository, write)
{
	char *contents;
	int contents_len = 0;
	long type = 0;
	git_odb_stream *stream;
	git_odb *odb;
	git_oid oid;
	char oid_out[GIT_OID_HEXSZ+1];
	int error = 0;
	php_git2_repository *m_repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &contents, &contents_len, &type) == FAILURE) {
		return;
	}
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	
	error  = git_repository_odb(&odb, m_repository->repository);
	PHP_GIT2_EXCEPTION_CHECK(error);
	
	error = git_odb_open_wstream(&stream, odb, contents_len, (git_otype)type);
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
{{{ proto: Git2\Repository::hash(string $contents, int $type)
*/
PHP_METHOD(git2_repository, hash)
{
	char *contents;
	int contents_len = 0;
	long type = 0;
	git_odb *odb;
	git_oid oid;
	char oid_out[GIT_OID_HEXSZ+1];
	int error = 0;
	php_git2_repository *m_repository;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &contents, &contents_len, &type) == FAILURE) {
		return;
	}
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	
	error  = git_repository_odb(&odb, m_repository->repository);
	PHP_GIT2_EXCEPTION_CHECK(error);

	error = git_odb_hash(&oid, contents,contents_len, type);
	PHP_GIT2_EXCEPTION_CHECK(error);
	
	git_oid_fmt(oid_out, &oid);
	RETURN_STRINGL(oid_out,GIT_OID_HEXSZ,1);
}
/* }}} */


/*
{{{ proto: Git2\Repository::checkout(Git2\Tree $tree[, int $opts, zval $stats)
	TODO: implement this
*/
PHP_METHOD(git2_repository, checkout)
{
/*
	php_git2_repository *m_repository;
	php_git2_tree *m_tree;
	zval *tree;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"O", &tree, git2_tree_class_entry) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, getThis());
	m_tree = PHP_GIT2_GET_OBJECT(php_git2_tree, tree);
	
	error = git_checkout_tree(m_repository->repository, m_tree->tree, NULL, NULL);
	RETURN_LONG(error);
*/
}
/* }}} */


static zend_function_entry php_git2_repository_methods[] = {
	PHP_ME(git2_repository, __construct, arginfo_git2_repository___construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(git2_repository, isEmpty,     NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, isBare,      NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, getPath,     NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, getWorkdir,  NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, headDetached,NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, headOrphan,  NULL,                                ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, init,        arginfo_git2_repository_init,        ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(git2_repository, discover,    arginfo_git2_repository_discover,    ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(git2_repository, exists,      arginfo_git2_repository_exists,      ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, hash,        arginfo_git2_repository_hash,       ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, write,       arginfo_git2_repository_write,       ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, getMergeBase,arginfo_git2_repository_get_merge_base,ZEND_ACC_PUBLIC)
	PHP_ME(git2_repository, checkout,    arginfo_git2_repository_checkout, ZEND_ACC_PUBLIC)
#ifdef lookup
#undef lookup
#endif
	PHP_ME(git2_repository, lookup,      arginfo_git2_repository_lookup,      ZEND_ACC_PUBLIC)
#ifndef lookup
#define lookup php_lookup
#endif
	{NULL,NULL,NULL}
};

void php_git2_repository_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Repository", php_git2_repository_methods);
	git2_repository_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_repository_class_entry->create_object = php_git2_repository_new;

	memcpy(&git2_repository_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	git2_repository_object_handlers.clone_obj = NULL;
}
