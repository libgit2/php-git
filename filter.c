#include "php_git2.h"
#include "php_git2_priv.h"
#include "filter.h"

/* {{{ proto long git_filter_list_load(resource $repo, resource $blob, string $path,  $mode)
 */
PHP_FUNCTION(git_filter_list_load)
{
	int result = 0, path_len = 0, error = 0;
	git_filter_list *filters = NULL;
	zval *repo = NULL, *blob = NULL;
	php_git2_t *_repo = NULL, *_blob = NULL;
	char *path = NULL;
	long mode = 0;
	
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
	php_git2_t *result = NULL, *_filters = NULL, *_in = NULL;
	git_buf out = {0};
	zval *filters = NULL, *in = NULL;
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BUF, &out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_filter_list_apply_to_file(resource $filters, resource $repo, string $path)
 */
PHP_FUNCTION(git_filter_list_apply_to_file)
{
	php_git2_t *result = NULL, *_filters = NULL, *_repo = NULL;
	git_buf out = {0};
	zval *filters = NULL, *repo = NULL;
	char *path = NULL;
	int path_len = 0, error = 0;
	
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BUF, &out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_filter_list_apply_to_blob(resource $filters, resource $blob)
 */
PHP_FUNCTION(git_filter_list_apply_to_blob)
{
	php_git2_t *result = NULL, *_filters = NULL, *_blob = NULL;
	git_buf out = {0};
	zval *filters = NULL, *blob = NULL;
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BUF, &out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
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
	if (GIT2_SHOULD_FREE(_filters)) {
		git_filter_list_free(PHP_GIT2_V(_filters, filter_list));
		GIT2_SHOULD_FREE(_filters) = 0;
	};
	zval_ptr_dtor(&filters);
}
/* }}} */


/* sys/filter */

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
	php_git2_t *result = NULL, *_repo = NULL;
	git_filter_list *out = NULL;
	zval *repo = NULL, *mode = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r<git_filter_mode_t>", &repo, &mode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_new(&out, PHP_GIT2_V(_repo, repository), mode);
	if (php_git2_check_error(error, "git_filter_list_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_FILTER_LIST, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_filter_list_push(resource $fl, resource $filter,  $payload)
 */
PHP_FUNCTION(git_filter_list_push)
{
	int result = 0, error = 0;
	zval *fl = NULL, *filter = NULL, *payload = NULL;
	php_git2_t *_fl = NULL, *_filter = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr<void>", &fl, &filter, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_fl, php_git2_t*, &fl, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_filter, php_git2_t*, &filter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	//result = git_filter_list_push(PHP_GIT2_V(_fl, filter_list), PHP_GIT2_V(_filter, filter), cb);
	RETURN_LONG(result);
}
/* }}} */

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
	/* TODO(chobie): implement this */
}
/* }}} */

/* {{{ proto long git_filter_register(string $name, resource $filter, long $priority)
 */
PHP_FUNCTION(git_filter_register)
{
	int result = 0, name_len = 0, error = 0;
	char *name = NULL;
	zval *filter = NULL;
	php_git2_t *_filter = NULL;
	long priority = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"srl", &name, &name_len, &filter, &priority) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_filter, php_git2_t*, &filter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	//result = git_filter_register(name, PHP_GIT2_V(_filter, filter), priority);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_filter_unregister(string $name)
 */
PHP_FUNCTION(git_filter_unregister)
{
	int result = 0, name_len = 0, error = 0;
	char *name = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}

	result = git_filter_unregister(name);
	RETURN_LONG(result);
}
/* }}} */

