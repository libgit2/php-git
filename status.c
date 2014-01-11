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

/* {{{ proto long git_status_file(resource $repo, string $path)
 */
PHP_FUNCTION(git_status_file)
{
	unsigned int status_flags = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *path = NULL;
	int path_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_status_file(status_flags, PHP_GIT2_V(_repo, repository), path);
	if (php_git2_check_error(error, "git_status_file" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_LONG(status_flags);
}
/* }}} */


/* {{{ proto resource git_status_list_new(resource $repo,  $opts)
 */
PHP_FUNCTION(git_status_list_new)
{
	php_git2_t *result = NULL;
	git_status_list *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *opts = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rz", &repo, &opts) == FAILURE) {
		return;
	}

	/* TODO(chobie): convert arra to git_status_options */

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_status_list_new(&out, PHP_GIT2_V(_repo, repository), opts);
	if (php_git2_check_error(error, "git_status_list_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, status_list) = out;
	result->type = PHP_GIT2_TYPE_STATUS_LIST;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto long git_status_list_entrycount(resource $statuslist)
 */
PHP_FUNCTION(git_status_list_entrycount)
{
	size_t result = 0;
	zval *statuslist = NULL;
	php_git2_t *_statuslist = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &statuslist) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_status_list_entrycount(PHP_GIT2_V(_statuslist, status_list));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_status_byindex(resource $statuslist, long $idx)
 */
PHP_FUNCTION(git_status_byindex)
{
	const git_status_entry *result = NULL;
	zval *statuslist = NULL;
	php_git2_t *_statuslist = NULL;
	long idx = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &statuslist, &idx) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_status_byindex(PHP_GIT2_V(_statuslist, status_list), idx);
	/* TODO(chobie): implement this */
}
/* }}} */

/* {{{ proto void git_status_list_free(resource $statuslist)
 */
PHP_FUNCTION(git_status_list_free)
{
	zval *statuslist = NULL;
	php_git2_t *_statuslist = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &statuslist) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_statuslist->should_free_v) {
		git_status_list_free(PHP_GIT2_V(_statuslist, status_list));
	};
	zval_ptr_dtor(&statuslist);
}
/* }}} */

/* {{{ proto long git_status_should_ignore(resource $repo, string $path)
 */
PHP_FUNCTION(git_status_should_ignore)
{
	int ignored = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *path = NULL;
	int path_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_status_should_ignore(&ignored, PHP_GIT2_V(_repo, repository), path);
	if (php_git2_check_error(error, "git_status_should_ignore" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	RETURN_LONG(ignored);
}
/* }}} */

