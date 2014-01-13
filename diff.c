#include "php_git2.h"
#include "php_git2_priv.h"
#include "diff.h"

/* {{{ proto void git_diff_free(resource $diff)
 */
PHP_FUNCTION(git_diff_free)
{
	zval *diff = NULL;
	php_git2_t *_diff = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &diff) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_diff)) {
		git_diff_free(PHP_GIT2_V(_diff, diff));
		GIT2_SHOULD_FREE(_diff) = 0;
	};
	zval_ptr_dtor(&diff);
}
/* }}} */


/* {{{ proto long git_diff_tree_to_tree(resource $repo, resource $old_tree, resource $new_tree,  $opts)
 */
PHP_FUNCTION(git_diff_tree_to_tree)
{
	int result = 0;
	git_diff *diff = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *old_tree = NULL;
	php_git2_t *_old_tree = NULL;
	zval *new_tree = NULL;
	php_git2_t *_new_tree = NULL;
	zval *opts = NULL;
	int error = 0;

	/* TODO(chobie): generate converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrra", &repo, &old_tree, &new_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_new_tree, php_git2_t*, &new_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_tree_to_tree(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), PHP_GIT2_V(_new_tree, tree), opts);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_diff_tree_to_index(resource $repo, resource $old_tree, resource $index,  $opts)
 */
PHP_FUNCTION(git_diff_tree_to_index)
{
	int result = 0, error = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *old_tree = NULL, *index = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_old_tree = NULL, *_index = NULL, *_diff = NULL;

	/* TODO(chobie): convert options */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrra", &repo, &old_tree, &index, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_tree_to_index(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), PHP_GIT2_V(_index, index), opts);
	if (php_git2_make_resource(&_diff, PHP_GIT2_TYPE_DIFF, diff, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_diff));

}
/* }}} */

/* {{{ proto long git_diff_index_to_workdir(resource $repo, resource $index,  $opts)
 */
PHP_FUNCTION(git_diff_index_to_workdir)
{
	int result = 0, error = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *index = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_index = NULL, *_diff = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &index, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_index_to_workdir(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_index, index), opts);
	if (php_git2_make_resource(&_diff, PHP_GIT2_TYPE_DIFF, diff, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_diff));

}
/* }}} */

/* {{{ proto long git_diff_tree_to_workdir(resource $repo, resource $old_tree,  $opts)
 */
PHP_FUNCTION(git_diff_tree_to_workdir)
{
	int result = 0, error = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *old_tree = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_old_tree = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr<git_diff_options>", &repo, &old_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_tree_to_workdir(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), opts);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_diff_tree_to_workdir_with_index(resource $repo, resource $old_tree,  $opts)
 */
PHP_FUNCTION(git_diff_tree_to_workdir_with_index)
{
	int result = 0, error = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *old_tree = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_old_tree = NULL, *_diff = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &old_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_tree_to_workdir_with_index(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), opts);
	if (php_git2_make_resource(&_diff, PHP_GIT2_TYPE_DIFF, diff, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_diff));
}
/* }}} */

/* {{{ proto long git_diff_merge(resource $onto, resource $from)
 */
PHP_FUNCTION(git_diff_merge)
{
	int result = 0, error = 0;
	zval *onto = NULL, *from = NULL;
	php_git2_t *_onto = NULL, *_from = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &onto, &from) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_onto, php_git2_t*, &onto, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_from, php_git2_t*, &from, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_merge(PHP_GIT2_V(_onto, diff), PHP_GIT2_V(_from, diff));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_diff_find_similar(resource $diff,  $options)
 */
PHP_FUNCTION(git_diff_find_similar)
{
	int result = 0;
	zval *diff = NULL;
	php_git2_t *_diff = NULL;
	zval *options = NULL;
	int error = 0;

	/* TODO(chobie): generate converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &diff, &options) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_find_similar(PHP_GIT2_V(_diff, diff), options);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_diff_options_init( $options, long $version)
 */
PHP_FUNCTION(git_diff_options_init)
{
	int result = 0;
	zval *options = NULL;
	long version = 0;
	int error = 0;

	/* TODO(chobie): generate converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"al", &options, &version) == FAILURE) {
		return;
	}

	result = git_diff_options_init(options, version);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_diff_num_deltas(resource $diff)
 */
PHP_FUNCTION(git_diff_num_deltas)
{
	size_t result = 0;
	zval *diff = NULL;
	php_git2_t *_diff = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &diff) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_num_deltas(PHP_GIT2_V(_diff, diff));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_diff_num_deltas_of_type(resource $diff,  $type)
 */
PHP_FUNCTION(git_diff_num_deltas_of_type)
{
	size_t result = 0;
	zval *diff = NULL;
	php_git2_t *_diff = NULL;
	long type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &diff, &type) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_num_deltas_of_type(PHP_GIT2_V(_diff, diff), type);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_diff_get_delta(resource $diff, long $idx)
 */
PHP_FUNCTION(git_diff_get_delta)
{
	const git_diff_delta  *result = NULL;
	zval *diff = NULL;
	php_git2_t *_diff = NULL;
	long idx = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &diff, &idx) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_get_delta(PHP_GIT2_V(_diff, diff), idx);
	/* TODO(chobie): implement this */
}
/* }}} */


/* {{{ proto long git_diff_is_sorted_icase(resource $diff)
 */
PHP_FUNCTION(git_diff_is_sorted_icase)
{
	int result = 0;
	zval *diff = NULL;
	php_git2_t *_diff = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &diff) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_is_sorted_icase(PHP_GIT2_V(_diff, diff));
	RETURN_BOOL(result);
}
/* }}} */


/* {{{ proto long git_diff_foreach(diff, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_foreach)
{
}

/* {{{ proto string git_diff_status_char( $status)
 */
PHP_FUNCTION(git_diff_status_char)
{
	char *result = NULL;
	long status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &status) == FAILURE) {
		return;
	}

	result = git_diff_status_char(status);
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto long git_diff_print(diff, format, print_cb, payload)
*/
PHP_FUNCTION(git_diff_print)
{
}

/* {{{ proto long git_diff_blobs(old_blob, old_as_path, new_blob, new_as_path, options, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_blobs)
{
}

/* {{{ proto long git_diff_blob_to_buffer(old_blob, old_as_path, buffer, buffer_len, buffer_as_path, options, file_cb, hunk_cb, line_cb, payload)
*/
PHP_FUNCTION(git_diff_blob_to_buffer)
{
}

