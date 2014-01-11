#include "php_git2.h"
#include "php_git2_priv.h"
#include "status.h"

/* {{{ proto long git_status_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_status_foreach)
{
	zval *repo;
	php_git2_t *_repo;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &repo, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_status_foreach_ext(repo, opts, callback, payload)
*/
PHP_FUNCTION(git_status_foreach_ext)
{
	zval *repo;
	php_git2_t *_repo;
	zval *opts;
	php_git2_t *_opts;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_foreach_ext not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrrz", &repo, &opts, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_status_file(status_flags, repo, path)
*/
PHP_FUNCTION(git_status_file)
{
	long status_flags;
	zval *repo;
	php_git2_t *_repo;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_file not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &status_flags, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_status_list_new(repo, opts)
*/
PHP_FUNCTION(git_status_list_new)
{
	zval *repo;
	php_git2_t *_repo;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_list_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_status_list_entrycount(statuslist)
*/
PHP_FUNCTION(git_status_list_entrycount)
{
	zval *statuslist;
	php_git2_t *_statuslist;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_list_entrycount not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &statuslist) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_status_byindex(statuslist, idx)
*/
PHP_FUNCTION(git_status_byindex)
{
	zval *statuslist;
	php_git2_t *_statuslist;
	long idx;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_byindex not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &statuslist, &idx) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_status_list_free(statuslist)
*/
PHP_FUNCTION(git_status_list_free)
{
	zval *statuslist;
	php_git2_t *_statuslist;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_list_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &statuslist) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_status_should_ignore(ignored, repo, path)
*/
PHP_FUNCTION(git_status_should_ignore)
{
	long ignored;
	zval *repo;
	php_git2_t *_repo;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_status_should_ignore not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &ignored, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

