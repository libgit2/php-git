#include "php_git2.h"
#include "php_git2_priv.h"
#include "filter.h"

/* {{{ proto resource git_filter_list_load(repo, blob, path, mode)
*/
PHP_FUNCTION(git_filter_list_load)
{
	zval *repo;
	php_git2_t *_repo;
	zval *blob;
	php_git2_t *_blob;
	char *path = {0};
	int path_len;
	zval *mode;
	php_git2_t *_mode;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_load not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrsr", &repo, &blob, &path, &path_len, &mode) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_list_apply_to_data(filters, in)
*/
PHP_FUNCTION(git_filter_list_apply_to_data)
{
	zval *filters;
	php_git2_t *_filters;
	zval *in;
	php_git2_t *_in;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_apply_to_data not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &filters, &in) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_list_apply_to_file(filters, repo, path)
*/
PHP_FUNCTION(git_filter_list_apply_to_file)
{
	zval *filters;
	php_git2_t *_filters;
	zval *repo;
	php_git2_t *_repo;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_apply_to_file not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrs", &filters, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_list_apply_to_blob(filters, blob)
*/
PHP_FUNCTION(git_filter_list_apply_to_blob)
{
	zval *filters;
	php_git2_t *_filters;
	zval *blob;
	php_git2_t *_blob;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_apply_to_blob not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &filters, &blob) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_filter_list_free(filters)
*/
PHP_FUNCTION(git_filter_list_free)
{
	zval *filters;
	php_git2_t *_filters;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &filters) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_lookup(name)
*/
PHP_FUNCTION(git_filter_lookup)
{
	char *name = {0};
	int name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_lookup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_filter_list_new(repo, mode)
*/
PHP_FUNCTION(git_filter_list_new)
{
	zval *repo;
	php_git2_t *_repo;
	zval *mode;
	php_git2_t *_mode;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &mode) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

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

/* {{{ proto resource git_filter_list_length(fl)
*/
PHP_FUNCTION(git_filter_list_length)
{
	zval *fl;
	php_git2_t *_fl;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_list_length not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &fl) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_fl, php_git2_t*, &fl, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_source_repo(src)
*/
PHP_FUNCTION(git_filter_source_repo)
{
	zval *src;
	php_git2_t *_src;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_source_repo not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_source_path(src)
*/
PHP_FUNCTION(git_filter_source_path)
{
	zval *src;
	php_git2_t *_src;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_source_path not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_source_filemode(src)
*/
PHP_FUNCTION(git_filter_source_filemode)
{
	zval *src;
	php_git2_t *_src;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_source_filemode not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_source_id(src)
*/
PHP_FUNCTION(git_filter_source_id)
{
	zval *src;
	php_git2_t *_src;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_source_id not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_filter_source_mode(src)
*/
PHP_FUNCTION(git_filter_source_mode)
{
	zval *src;
	php_git2_t *_src;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_source_mode not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_filter_register(name, filter, priority)
*/
PHP_FUNCTION(git_filter_register)
{
	char *name = {0};
	int name_len;
	zval *filter;
	php_git2_t *_filter;
	long priority;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_register not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"srl", &name, &name_len, &filter, &priority) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_name, php_git2_t*, &name, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_filter_unregister(name)
*/
PHP_FUNCTION(git_filter_unregister)
{
	char *name = {0};
	int name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_filter_unregister not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}
}

