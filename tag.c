#include "php_git2.h"
#include "php_git2_priv.h"
#include "tag.h"

/* {{{ proto resource git_tag_lookup(resource $repo, string $id)
 */
PHP_FUNCTION(git_tag_lookup)
{
	php_git2_t *result = NULL;
	git_tag *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *id = NULL;
	int id_len = 0;
	git_oid __id;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &id, &id_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	error = git_tag_lookup(&out, PHP_GIT2_V(_repo, repository), &__id);
	if (php_git2_check_error(error, "git_tag_lookup" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, tag) = out;
	result->type = PHP_GIT2_TYPE_TAG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto resource git_tag_lookup_prefix(resource $repo, string $id)
 */
PHP_FUNCTION(git_tag_lookup_prefix)
{
	php_git2_t *result = NULL;
	git_tag *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *id = NULL;
	int id_len = 0;
	git_oid __id;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &id, &id_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	error = git_tag_lookup_prefix(&out, PHP_GIT2_V(_repo, repository), &__id, id_len);
	if (php_git2_check_error(error, "git_tag_lookup_prefix" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, tag) = out;
	result->type = PHP_GIT2_TYPE_TAG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto void git_tag_free(resource $tag)
 */
PHP_FUNCTION(git_tag_free)
{
	zval *tag = NULL;
	php_git2_t *_tag = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_tag->should_free_v) {
		git_tag_free(PHP_GIT2_V(_tag, tag));
	};
	zval_ptr_dtor(&tag);
}
/* }}} */

/* {{{ proto resource git_tag_id(resource $tag)
 */
PHP_FUNCTION(git_tag_id)
{
	const git_oid  *result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;
	char __result[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_id(PHP_GIT2_V(_tag, tag));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto resource git_tag_owner(resource $tag)
 */
PHP_FUNCTION(git_tag_owner)
{
	git_repository  *result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;
	php_git2_t *__result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_owner(PHP_GIT2_V(_tag, tag));
	PHP_GIT2_MAKE_RESOURCE(__result);
	PHP_GIT2_V(__result, tag) = tag;
	__result->type = PHP_GIT2_TYPE_TAG;
	__result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	__result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, __result->resource_id);
}
/* }}} */

/* {{{ proto resource git_tag_target(resource $tag)
 */
PHP_FUNCTION(git_tag_target)
{
	php_git2_t *result = NULL;
	git_object *target_out = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_tag_target(&target_out, PHP_GIT2_V(_tag, tag));
	if (php_git2_check_error(error, "git_tag_target" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = target_out;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto resource git_tag_target_id(resource $tag)
 */
PHP_FUNCTION(git_tag_target_id)
{
	const git_oid  *result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;
	char __result[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_target_id(PHP_GIT2_V(_tag, tag));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto resource git_tag_target_type(resource $tag)
 */
PHP_FUNCTION(git_tag_target_type)
{
	git_otype *result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_target_type(PHP_GIT2_V(_tag, tag));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto string git_tag_name(resource $tag)
 */
PHP_FUNCTION(git_tag_name)
{
	const char  *result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_name(PHP_GIT2_V(_tag, tag));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto array git_tag_tagger(resource $tag)
 */
PHP_FUNCTION(git_tag_tagger)
{
	const git_signature  *result = NULL;
	zval *__result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_tagger(PHP_GIT2_V(_tag, tag));
	php_git2_signature_to_array(result, &__result TSRMLS_CC);
	RETURN_ZVAL(__result, 0, 1);
}
/* }}} */

/* {{{ proto string git_tag_message(resource $tag)
 */
PHP_FUNCTION(git_tag_message)
{
	const char  *result = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_message(PHP_GIT2_V(_tag, tag));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_tag_create(resource $repo, string $tag_name, resource $target, array $tagger, string $message, long $force)
 */
PHP_FUNCTION(git_tag_create)
{
	int result = 0;
	git_oid __oid;
	zval *repo = NULL;
	php_git2_t *_repo = NULL, *out = NULL;
	char *tag_name = NULL;
	int tag_name_len = 0;
	zval *target = NULL;
	php_git2_t *_target = NULL;
	zval *tagger = NULL;
	char *message = NULL;
	int message_len = 0;
	long force = 0;
	int error = 0;
	char buffer[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrasl", &repo, &tag_name, &tag_name_len, &target, &tagger, &message, &message_len, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_target, php_git2_t*, &target, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_create(&__oid, PHP_GIT2_V(_repo, repository), tag_name, PHP_GIT2_V(_target, object), tagger, message, force);
	if (php_git2_check_error(result, "git_tag_create" TSRMLS_CC)) {
		RETURN_FALSE
	}
	git_oid_fmt(buffer, &__oid);
	RETURN_STRING(buffer, 1);

}
/* }}} */


/* {{{ proto string git_tag_annotation_create(resource $repo, string $tag_name, resource $target, array $tagger, string $message)
 */
PHP_FUNCTION(git_tag_annotation_create)
{
	int result = 0;
	git_oid __oid;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *tag_name = NULL;
	int tag_name_len = 0;
	zval *target = NULL;
	php_git2_t *_target = NULL;
	zval *tagger = NULL;
	char *message = NULL;
	int message_len = 0;
	int error = 0;
	char buffer[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsras", &repo, &tag_name, &tag_name_len, &target, &tagger, &message, &message_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_target, php_git2_t*, &target, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_annotation_create(&__oid, PHP_GIT2_V(_repo, repository), tag_name, PHP_GIT2_V(_target, object), tagger, message);
	if (php_git2_check_error(result, "git_tag_annotation_create" TSRMLS_CC)) {
		RETURN_FALSE
	}
	git_oid_fmt(buffer, &__oid);
	RETURN_STRING(buffer, 1);

}
/* }}} */

/* {{{ proto string git_tag_create_frombuffer(resource $repo, string $buffer, long $force)
 */
PHP_FUNCTION(git_tag_create_frombuffer)
{
	int result = 0;
	git_oid __oid;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *buffer = NULL;
	int buffer_len = 0;
	long force = 0;
	int error = 0;
	char oid[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &buffer, &buffer_len, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_create_frombuffer(&__oid, PHP_GIT2_V(_repo, repository), buffer, force);
	if (php_git2_check_error(result, "git_tag_create_frombuffer" TSRMLS_CC)) {
		RETURN_FALSE
	}
	git_oid_fmt(oid, &__oid);
	RETURN_STRING(oid, 1);
}
/* }}} */


/* {{{ proto string git_tag_create_lightweight(resource $repo, string $tag_name, resource $target, long $force)
 */
PHP_FUNCTION(git_tag_create_lightweight)
{
	int result = 0;
	git_oid __oid;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *tag_name = NULL;
	int tag_name_len = 0;
	zval *target = NULL;
	php_git2_t *_target = NULL;
	long force = 0;
	int error = 0;
	char oid[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrl", &repo, &tag_name, &tag_name_len, &target, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_target, php_git2_t*, &target, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_create_lightweight(&__oid, PHP_GIT2_V(_repo, repository), tag_name, PHP_GIT2_V(_target, object), force);
	if (php_git2_check_error(result, "git_tag_create_lightweight" TSRMLS_CC)) {
		RETURN_FALSE
	}
	git_oid_fmt(oid, &__oid);
	RETURN_STRING(oid, 1);
}
/* }}} */


/* {{{ proto long git_tag_delete(resource $repo, string $tag_name)
 */
PHP_FUNCTION(git_tag_delete)
{
	int result = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *tag_name = NULL;
	int tag_name_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &tag_name, &tag_name_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tag_delete(PHP_GIT2_V(_repo, repository), tag_name);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_tag_list(resource $repo)
 */
PHP_FUNCTION(git_tag_list)
{
	int error = 0;
	git_strarray tag_names = {0};
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_tag_list(&tag_names, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_tag_list" TSRMLS_CC)) {
		RETURN_FALSE
	}
	php_git2_strarray_to_array(&tag_names, &result TSRMLS_CC);
	git_strarray_free(&tag_names);
	RETURN_ZVAL(result, 0, 1);
}
/* }}} */


/* {{{ proto long git_tag_list_match(string $pattern, resource $repo)
 */
PHP_FUNCTION(git_tag_list_match)
{
	zval *result;
	git_strarray tag_names = {0};
	char *pattern = NULL;
	int pattern_len = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sr", &pattern, &pattern_len, &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_tag_list_match(&tag_names, pattern, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_tag_list_match" TSRMLS_CC)) {
		RETURN_FALSE
	}
	php_git2_strarray_to_array(&tag_names, &result TSRMLS_CC);
	git_strarray_free(&tag_names);
	RETURN_ZVAL(result, 0, 1);

}
/* }}} */


/* {{{ proto long git_tag_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_tag_foreach)
{
	zval *repo;
	php_git2_t *_repo;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &repo, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_peel(resource $tag)
 */
PHP_FUNCTION(git_tag_peel)
{
	php_git2_t *result = NULL;
	git_object *tag_target_out = NULL;
	zval *tag = NULL;
	php_git2_t *_tag = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_tag_peel(&tag_target_out, PHP_GIT2_V(_tag, tag));
	if (php_git2_check_error(error, "git_tag_peel" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = tag_target_out;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */
