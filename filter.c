#include "php_git2.h"
#include "php_git2_priv.h"
#include "filter.h"

/* {{{ proto long git_filter_list_load(resource $repo, resource $blob, string $path,  $mode)
 */
PHP_FUNCTION(git_filter_list_load)
{
	int result = 0;
	git_filter_list *filters = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *blob = NULL;
	php_git2_t *_blob = NULL;
	char *path = NULL;
	int path_len = 0;
	long mode = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrsl", &repo, &blob, &path, &path_len, &mode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_list_load(&filters, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_blob, blob), path, mode);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_filter_list_apply_to_data(resource $filters, resource $in)
 */
PHP_FUNCTION(git_filter_list_apply_to_data)
{
	php_git2_t *result = NULL;
	git_buf out = {0};
	zval *filters = NULL;
	php_git2_t *_filters = NULL;
	zval *in = NULL;
	php_git2_t *_in = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &filters, &in) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_in, php_git2_t*, &in, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_apply_to_data(&out, PHP_GIT2_V(_filters, filter_list), PHP_GIT2_V(_in, buf));
	if (php_git2_check_error(error, "git_filter_list_apply_to_data" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, buf) = &out;
	result->type = PHP_GIT2_TYPE_BUF;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto resource git_filter_list_apply_to_file(resource $filters, resource $repo, string $path)
 */
PHP_FUNCTION(git_filter_list_apply_to_file)
{
	php_git2_t *result = NULL;
	git_buf out = {0};
	zval *filters = NULL;
	php_git2_t *_filters = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *path = NULL;
	int path_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrs", &filters, &repo, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_apply_to_file(&out, PHP_GIT2_V(_filters, filter_list), PHP_GIT2_V(_repo, repository), path);
	if (php_git2_check_error(error, "git_filter_list_apply_to_file" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, buf) = &out;
	result->type = PHP_GIT2_TYPE_BUF;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto resource git_filter_list_apply_to_blob(resource $filters, resource $blob)
 */
PHP_FUNCTION(git_filter_list_apply_to_blob)
{
	php_git2_t *result = NULL;
	git_buf out = {0};
	zval *filters = NULL;
	php_git2_t *_filters = NULL;
	zval *blob = NULL;
	php_git2_t *_blob = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &filters, &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_apply_to_blob(&out, PHP_GIT2_V(_filters, filter_list), PHP_GIT2_V(_blob, blob));
	if (php_git2_check_error(error, "git_filter_list_apply_to_blob" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, buf) = &out;
	result->type = PHP_GIT2_TYPE_BUF;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto void git_filter_list_free(resource $filters)
 */
PHP_FUNCTION(git_filter_list_free)
{
	zval *filters = NULL;
	php_git2_t *_filters = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &filters) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_filters->should_free_v) {
		git_filter_list_free(PHP_GIT2_V(_filters, filter_list));
	};
	zval_ptr_dtor(&filters);
}
/* }}} */

/* {{{ proto resource git_filter_lookup(string $name)
 */
PHP_FUNCTION(git_filter_lookup)
{
	git_filter  *result = NULL;
	char *name = NULL;
	int name_len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}

	result = git_filter_lookup(name);
	/* TODO(chobie): implement this */
}
/* }}} */


/* {{{ proto resource git_filter_list_new(resource $repo,  $mode)
 */
PHP_FUNCTION(git_filter_list_new)
{
	php_git2_t *result = NULL;
	git_filter_list *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	long mode = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &repo, &mode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_new(&out, PHP_GIT2_V(_repo, repository), mode);
	if (php_git2_check_error(error, "git_filter_list_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, filter_list) = out;
	result->type = PHP_GIT2_TYPE_FILTER_LIST;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto long git_filter_list_push(fl, filter, payload)
*/
PHP_FUNCTION(git_filter_list_push)
{
	zval *fl;
	php_git2_t *_fl;
	zval *filter;
	php_git2_t *_filter;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_push not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rr", &fl, &filter, &payload) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_fl, php_git2_t*, &fl, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_filter_list_length(resource $fl)
 */
PHP_FUNCTION(git_filter_list_length)
{
	size_t result = 0;
	zval *fl = NULL;
	php_git2_t *_fl = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &fl) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_fl, php_git2_t*, &fl, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_list_length(PHP_GIT2_V(_fl, filter_list));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_filter_source_repo(resource $src)
 */
PHP_FUNCTION(git_filter_source_repo)
{
	git_repository  *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_repo(PHP_GIT2_V(_src, filter_source));
	/* TODO(chobie): implement this */
}
/* }}} */


/* {{{ proto string git_filter_source_path(resource $src)
 */
PHP_FUNCTION(git_filter_source_path)
{
	const char  *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_path(PHP_GIT2_V(_src, filter_source));
	RETURN_STRING(result, 1);
}
/* }}} */


/* {{{ proto long git_filter_source_filemode(resource $src)
 */
PHP_FUNCTION(git_filter_source_filemode)
{
	uint16_t result = 0;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_filemode(PHP_GIT2_V(_src, filter_source));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_filter_source_id(resource $src)
 */
PHP_FUNCTION(git_filter_source_id)
{
	const git_oid  *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_id(PHP_GIT2_V(_src, filter_source));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */


/* {{{ proto resource git_filter_source_mode(resource $src)
 */
PHP_FUNCTION(git_filter_source_mode)
{
	git_filter_mode_t *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_mode(PHP_GIT2_V(_src, filter_source));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_filter_register(string $name,  $filter, long $priority)
 */
PHP_FUNCTION(git_filter_register)
{
	int result = 0;
	char *name = NULL;
	int name_len = 0;
	zval *filter = NULL;
	long priority = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sal", &name, &name_len, &filter, &priority) == FAILURE) {
		return;
	}

	result = git_filter_register(name, filter, priority);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_filter_unregister(string $name)
 */
PHP_FUNCTION(git_filter_unregister)
{
	int result = 0;
	char *name = NULL;
	int name_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}

	result = git_filter_unregister(name);
	RETURN_LONG(result);
}
/* }}} */
