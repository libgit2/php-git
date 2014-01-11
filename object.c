#include "php_git2.h"
#include "php_git2_priv.h"
#include "object.h"

/* {{{ proto resource git_object_lookup(repo, id, type)
*/
PHP_FUNCTION(git_object_lookup)
{
	zval *repo;
	php_git2_t *_repo;
	char *id = {0};
	int id_len;
	zval *type;
	php_git2_t *_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_lookup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsr", &repo, &id, &id_len, &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
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
	php_git2_t *_treeish;
	char *path = {0};
	int path_len;
	zval *type;
	php_git2_t *_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_lookup_bypath not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsr", &treeish, &path, &path_len, &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_treeish, php_git2_t*, &treeish, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_id(obj)
*/
PHP_FUNCTION(git_object_id)
{
	zval *obj;
	php_git2_t *_obj;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_id not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_type(obj)
*/
PHP_FUNCTION(git_object_type)
{
	zval *obj;
	php_git2_t *_obj;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_type not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_owner(obj)
*/
PHP_FUNCTION(git_object_owner)
{
	zval *obj;
	php_git2_t *_obj;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_owner not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &obj) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_obj, php_git2_t*, &obj, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_object_free(object)
*/
PHP_FUNCTION(git_object_free)
{
	zval *object;
	php_git2_t *_object;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_type2string(type)
*/
PHP_FUNCTION(git_object_type2string)
{
	zval *type;
	php_git2_t *_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_type2string not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_type, php_git2_t*, &type, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_string2type(str)
*/
PHP_FUNCTION(git_object_string2type)
{
	char *str = {0};
	int str_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_string2type not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &str, &str_len) == FAILURE) {
		return;
	}
}

/* {{{ proto long git_object_typeisloose(type)
*/
PHP_FUNCTION(git_object_typeisloose)
{
	zval *type;
	php_git2_t *_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_typeisloose not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_type, php_git2_t*, &type, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object__size(type)
*/
PHP_FUNCTION(git_object__size)
{
	zval *type;
	php_git2_t *_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object__size not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_type, php_git2_t*, &type, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_peel(object, target_type)
*/
PHP_FUNCTION(git_object_peel)
{
	zval *object;
	php_git2_t *_object;
	zval *target_type;
	php_git2_t *_target_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_peel not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &object, &target_type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_object_dup(source)
*/
PHP_FUNCTION(git_object_dup)
{
	zval *source;
	php_git2_t *_source;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_object_dup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &source) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_source, php_git2_t*, &source, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

