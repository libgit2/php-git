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

