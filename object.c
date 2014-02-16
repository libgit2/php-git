#include "php_git2.h"
#include "php_git2_priv.h"
#include "object.h"

/* {{{ proto long git_object_lookup(resource $repo, string $id, long $type)
 */
PHP_FUNCTION(git_object_lookup)
{
	int result = 0, id_len = 0;
	git_object *object = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *id = NULL;
	git_oid __id = {0};
	long type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &id, &id_len, &type) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_object_lookup(&object, PHP_GIT2_V(_repo, repository), &__id, type);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_object_lookup_prefix(resource $repo, string $id, long $len, long $type)
 */
PHP_FUNCTION(git_object_lookup_prefix)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_object *object_out = NULL;
	zval *repo = NULL;
	char *id = NULL;
	int id_len = 0, error = 0;
	git_oid __id = {0};
	long len = 0, type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsll", &repo, &id, &id_len, &len, &type) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	error = git_object_lookup_prefix(&object_out, PHP_GIT2_V(_repo, repository), &__id, len, type);
	if (php_git2_check_error(error, "git_object_lookup_prefix" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_OBJECT, object_out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_object_lookup_bypath(resource $treeish, string $path, long $type)
 */
PHP_FUNCTION(git_object_lookup_bypath)
{
	php_git2_t *result = NULL, *_treeish = NULL;
	git_object *out = NULL;
	zval *treeish = NULL;
	char *path = NULL;
	int path_len = 0, error = 0;
	long type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &treeish, &path, &path_len, &type) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_treeish, php_git2_t*, &treeish, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_object_lookup_bypath(&out, PHP_GIT2_V(_treeish, object), path, type);
	if (php_git2_check_error(error, "git_object_lookup_bypath" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_OBJECT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_object_id(obj)
*/
PHP_FUNCTION(git_object_id)
{
	zval *obj;
	php_git2_t *_obj;
	const git_oid *id;
	char buf[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	id = git_object_id(PHP_GIT2_V(_obj, object));
	git_oid_fmt(buf, id);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto resource git_object_type(resource $obj)
 */
PHP_FUNCTION(git_object_type)
{
	git_otype result;
	zval *obj = NULL;
	php_git2_t *_obj = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_object_type(PHP_GIT2_V(_obj, object));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_object_owner(resource $obj)
 */
PHP_FUNCTION(git_object_owner)
{
	git_repository  *result = NULL;
	zval *obj = NULL;
	php_git2_t *_obj = NULL, *__result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_object_owner(PHP_GIT2_V(_obj, object));
	if (php_git2_make_resource(&__result, PHP_GIT2_TYPE_OBJECT, result, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(__result));
}
/* }}} */

/* {{{ proto void git_object_free(resource $object)
 */
PHP_FUNCTION(git_object_free)
{
	zval *object = NULL;
	php_git2_t *_object = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_object)) {
		git_object_free(PHP_GIT2_V(_object, object));
		GIT2_SHOULD_FREE(_object) = 0;
	};
	zval_ptr_dtor(&object);
}
/* }}} */

/* {{{ proto string git_object_type2string(long $type)
 */
PHP_FUNCTION(git_object_type2string)
{
	const char  *result = NULL;
	long type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &type) == FAILURE) {
		return;
	}

	result = git_object_type2string(type);
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto resource git_object_string2type(str)
*/
PHP_FUNCTION(git_object_string2type)
{
	char *str = {0};
	int str_len;
	git_otype type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &str, &str_len) == FAILURE) {
		return;
	}
	type = git_object_string2type(str);
	RETURN_LONG(type);
}
/* }}} */

/* {{{ proto long git_object_typeisloose(long $type)
 */
PHP_FUNCTION(git_object_typeisloose)
{
	int result = 0;
	long type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &type) == FAILURE) {
		return;
	}

	result = git_object_typeisloose(type);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_object__size(type)
*/
PHP_FUNCTION(git_object__size)
{
	long type;
	size_t size;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &type) == FAILURE) {
		return;
	}
	size = git_object__size(type);
	RETURN_LONG(size);
}

/* {{{ proto long git_object_peel(resource $object, long $target_type)
 */
PHP_FUNCTION(git_object_peel)
{
	int result = 0;
	git_object *peeled = NULL;
	zval *object = NULL;
	php_git2_t *_object = NULL, *_result;
	long target_type = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &object, &target_type) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_object_peel(&peeled, PHP_GIT2_V(_object, object), target_type);
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_OBJECT, peeled, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */

/* {{{ proto long git_object_dup(resource $source)
 */
PHP_FUNCTION(git_object_dup)
{
	int result = 0;
	git_object *dest = NULL;
	zval *source = NULL;
	php_git2_t *_source = NULL, *_result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &source) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_source, php_git2_t*, &source, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_object_dup(&dest, PHP_GIT2_V(_source, object));
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_OBJECT, dest, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */
