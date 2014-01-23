#include "php_git2.h"
#include "php_git2_priv.h"
#include "pathspec.h"

/* {{{ proto resource git_pathspec_new(array $pathspec)
 */
PHP_FUNCTION(git_pathspec_new)
{
	php_git2_t *result = NULL;
	git_pathspec *out = NULL;
	zval *pathspec = NULL;
	git_strarray _pathspec = {0};
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &pathspec) == FAILURE) {
		return;
	}

	php_git2_array_to_strarray(&_pathspec, pathspec TSRMLS_CC);
	error = git_pathspec_new(&out, &_pathspec);
	php_git2_strarray_free(&_pathspec);
	if (php_git2_check_error(error, "git_pathspec_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PATHSPEC, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto void git_pathspec_free(resource $ps)
 */
PHP_FUNCTION(git_pathspec_free)
{
	zval *ps = NULL;
	php_git2_t *_ps = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ps) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_ps)) {
		git_pathspec_free(PHP_GIT2_V(_ps, pathspec));
		GIT2_SHOULD_FREE(_ps) = 0;
	};
	zval_ptr_dtor(&ps);
}
/* }}} */


/* {{{ proto long git_pathspec_matches_path(resource $ps, long $flags, string $path)
 */
PHP_FUNCTION(git_pathspec_matches_path)
{
	int result = 0, path_len = 0;
	zval *ps = NULL;
	php_git2_t *_ps = NULL;
	long flags = 0;
	char *path = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rls", &ps, &flags, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_pathspec_matches_path(PHP_GIT2_V(_ps, pathspec), flags, path);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_pathspec_match_workdir(resource $repo, long $flags, resource $ps)
 */
PHP_FUNCTION(git_pathspec_match_workdir)
{
	php_git2_t *result = NULL, *_repo = NULL, *_ps = NULL;
	git_pathspec_match_list *out;
	zval *repo = NULL, *ps = NULL;
	long flags = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &repo, &flags, &ps) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_pathspec_match_workdir(&out, PHP_GIT2_V(_repo, repository), flags, PHP_GIT2_V(_ps, pathspec));
	if (php_git2_check_error(error, "git_pathspec_match_workdir" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PATHSPEC_MATCH_LIST, out, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_pathspec_match_index(resource $index, long $flags, resource $ps)
 */
PHP_FUNCTION(git_pathspec_match_index)
{
	php_git2_t *result = NULL, *_index = NULL, *_ps = NULL;
	git_pathspec_match_list *out = NULL;
	zval *index = NULL, *ps = NULL;
	long flags = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &index, &flags, &ps) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_pathspec_match_index(&out, PHP_GIT2_V(_index, index), flags, PHP_GIT2_V(_ps, pathspec));
	if (php_git2_check_error(error, "git_pathspec_match_index" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PATHSPEC_MATCH_LIST, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_pathspec_match_tree(resource $tree, long $flags, resource $ps)
 */
PHP_FUNCTION(git_pathspec_match_tree)
{
	php_git2_t *result = NULL, *_tree = NULL, *_ps = NULL;
	git_pathspec_match_list *out = NULL;
	zval *tree = NULL, *ps = NULL;
	long flags = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &tree, &flags, &ps) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tree, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_pathspec_match_tree(&out, PHP_GIT2_V(_tree, tree), flags, PHP_GIT2_V(_ps, pathspec));
	if (php_git2_check_error(error, "git_pathspec_match_tree" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PATHSPEC_MATCH_LIST, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_pathspec_match_diff(resource $diff, long $flags, resource $ps)
 */
PHP_FUNCTION(git_pathspec_match_diff)
{
	php_git2_t *result = NULL, *_diff = NULL, *_ps = NULL;
	git_pathspec_match_list *out = NULL;
	zval *diff = NULL, *ps = NULL;
	long flags = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &diff, &flags, &ps) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_pathspec_match_diff(&out, PHP_GIT2_V(_diff, diff), flags, PHP_GIT2_V(_ps, pathspec));
	if (php_git2_check_error(error, "git_pathspec_match_diff" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PATHSPEC_MATCH_LIST, out, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto void git_pathspec_match_list_free(resource $m)
 */
PHP_FUNCTION(git_pathspec_match_list_free)
{
	zval *m = NULL;
	php_git2_t *_m = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &m) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_m)) {
		git_pathspec_match_list_free(PHP_GIT2_V(_m, pathspec_match_list));
		GIT2_SHOULD_FREE(_m) = 0;
	};
	zval_ptr_dtor(&m);
}
/* }}} */


/* {{{ proto long git_pathspec_match_list_entrycount(resource $m)
 */
PHP_FUNCTION(git_pathspec_match_list_entrycount)
{
	size_t result = 0;
	zval *m = NULL;
	php_git2_t *_m = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &m) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_pathspec_match_list_entrycount(PHP_GIT2_V(_m, pathspec_match_list));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto string git_pathspec_match_list_entry(resource $m, long $pos)
 */
PHP_FUNCTION(git_pathspec_match_list_entry)
{
	const char  *result = NULL;
	zval *m = NULL;
	php_git2_t *_m = NULL;
	long pos = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &m, &pos) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_pathspec_match_list_entry(PHP_GIT2_V(_m, pathspec_match_list), pos);
	RETURN_STRING(result, 1);
}
/* }}} */


/* {{{ proto resource git_pathspec_match_list_diff_entry(resource $m, long $pos)
 */
PHP_FUNCTION(git_pathspec_match_list_diff_entry)
{
	const git_diff_delta *result = NULL;
	zval *m = NULL, *_result = NULL;
	php_git2_t *_m = NULL;
	long pos = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &m, &pos) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_pathspec_match_list_diff_entry(PHP_GIT2_V(_m, pathspec_match_list), pos);
	if (result == NULL) {
		RETURN_FALSE;
	}
	php_git2_diff_delta_to_array(result, &_result TSRMLS_CC);
	RETURN_ZVAL(_result, 0, 1);
}
/* }}} */


/* {{{ proto long git_pathspec_match_list_failed_entrycount(resource $m)
 */
PHP_FUNCTION(git_pathspec_match_list_failed_entrycount)
{
	size_t result = 0;
	zval *m = NULL;
	php_git2_t *_m = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &m) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_pathspec_match_list_failed_entrycount(PHP_GIT2_V(_m, pathspec_match_list));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto string git_pathspec_match_list_failed_entry(resource $m, long $pos)
 */
PHP_FUNCTION(git_pathspec_match_list_failed_entry)
{
	const char  *result = NULL;
	zval *m = NULL;
	php_git2_t *_m = NULL;
	long pos = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &m, &pos) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_pathspec_match_list_failed_entry(PHP_GIT2_V(_m, pathspec_match_list), pos);
	RETURN_STRING(result, 1);
}
/* }}} */

