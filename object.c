#include "php_git2.h"
#include "php_git2_priv.h"
#include "object.h"

/* {{{ proto resource git_object_lookup(repo, id, type)
*/
PHP_FUNCTION(git_object_lookup)
{
	zval *repo;
	php_git2_t *_repo, *result;
	char *id = {0};
	int id_len;
	zval *type;
	php_git2_t *_type;
	int error = 0;
	git_object *object;
	git_oid oid;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsr", &repo, &id, &id_len, &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&oid, id, id_len) != GIT_OK) {
		return;
	}
	error = git_object_lookup(&object, PHP_GIT2_V(_repo, repository), &oid, type);
	if (php_git2_check_error(error, "git_object_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = object;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_object_lookup_prefix(repo, id, len, type)
*/
PHP_FUNCTION(git_object_lookup_prefix)
{
	zval *repo;
	php_git2_t *_repo;
	char *id = {0};
	int id_len;
	zval *type;
	php_git2_t *_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_lookup_prefix not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rsr", &repo, &id, &id_len, &len, &type) == FAILURE) {
//		return;
//	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_lookup_bypath(treeish, path, type)
*/
PHP_FUNCTION(git_object_lookup_bypath)
{
	zval *treeish;
	php_git2_t *_treeish, *result;
	char *path = {0};
	int path_len;
	zval *type;
	php_git2_t *_type;
	git_object *object;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsr", &treeish, &path, &path_len, &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_treeish, php_git2_t*, &treeish, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	// TODO: cast object
	error = git_object_lookup_bypath(&object, PHP_GIT2_V(_treeish, tree), path, type);
	if (php_git2_check_error(error, "git_object_lookup_bypath" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = object;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	
	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_object_id(obj)
*/
PHP_FUNCTION(git_object_id)
{
	zval *obj;
	php_git2_t *_obj;
	const git_oid *id;
	char buf[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	id = git_object_id(PHP_GIT2_V(_obj, object));
	git_oid_fmt(buf, id);
	RETURN_STRING(buf, 1);
}

/* {{{ proto resource git_object_type(obj)
*/
PHP_FUNCTION(git_object_type)
{
	zval *obj;
	php_git2_t *_obj;
	const git_otype *type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	type = git_object_type(PHP_GIT2_V(_obj, object));
	RETURN_LONG(type);
}

/* {{{ proto resource git_object_owner(obj)
*/
PHP_FUNCTION(git_object_owner)
{
	zval *obj;
	php_git2_t *_obj, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	// TODO: consider cast
	repository = git_object_owner(PHP_GIT2_V(_obj, object));
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto void git_object_free(object)
*/
PHP_FUNCTION(git_object_free)
{
	zval *object;
	php_git2_t *_object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_object->should_free_v) {
		git_object_free(PHP_GIT2_V(_object, object));
		_object->should_free_v = 0;
	}
	zval_ptr_dtor(&object);
}

/* {{{ proto resource git_object_type2string(type)
*/
PHP_FUNCTION(git_object_type2string)
{
	zval *type;
	php_git2_t *_type;
	const char *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_type, php_git2_t*, &type, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	// TODO: consider cast
	result = git_object_type2string(PHP_GIT2_V(_type, object));
	RETURN_STRING(result, 1);
}

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

/* {{{ proto long git_object_typeisloose(type)
*/
PHP_FUNCTION(git_object_typeisloose)
{
	zval *type;
	php_git2_t *_type;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_type, php_git2_t*, &type, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_object_typeisloose(PHP_GIT2_V(_type, object));
	if (php_git2_check_error(error, "git_object_typeisloose" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

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

/* {{{ proto resource git_object_peel(object, target_type)
*/
PHP_FUNCTION(git_object_peel)
{
	zval *object;
	php_git2_t *_object, *result;
	zval *target_type;
	php_git2_t *_target_type;
	int error = 0;
	git_object *out;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &object, &target_type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_object_peel(&out, PHP_GIT2_V(_object, object), target_type);
	if (php_git2_check_error(error, "git_object_peel" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = object;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;
	
	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_object_dup(source)
*/
PHP_FUNCTION(git_object_dup)
{
	zval *source;
	php_git2_t *_source, *result;
	git_object *dest;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &source) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_source, php_git2_t*, &source, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_object_dup(&dest, PHP_GIT2_V(_source, object));
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = dest;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

