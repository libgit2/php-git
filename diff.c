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
	git_diff_options options = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrra", &repo, &old_tree, &new_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_new_tree, php_git2_t*, &new_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_diff_options(&options, opts TSRMLS_CC);
	result = git_diff_tree_to_tree(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), PHP_GIT2_V(_new_tree, tree), opts);
	php_git2_git_diff_options_free(&options);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_diff_tree_to_index(resource $repo, resource $old_tree, resource $index,  $opts)
 */
PHP_FUNCTION(git_diff_tree_to_index)
{
	int result = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *old_tree = NULL, *index = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_old_tree = NULL, *_index = NULL, *_diff = NULL;
	git_diff_options options = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrra", &repo, &old_tree, &index, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_diff_options(&options, opts TSRMLS_CC);
	result = git_diff_tree_to_index(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), PHP_GIT2_V(_index, index), opts);
	php_git2_git_diff_options_free(&options);
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
	int result = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *index = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_index = NULL, *_diff = NULL;
	git_diff_options options = GIT_DIFF_OPTIONS_INIT;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &index, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_diff_options(&options, opts TSRMLS_CC);
	result = git_diff_index_to_workdir(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_index, index), opts);
	php_git2_git_diff_options_free(&options);
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
	int result = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *old_tree = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_old_tree = NULL, *_result;
	git_diff_options options = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &old_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_diff_options(&options, opts TSRMLS_CC);
	result = git_diff_tree_to_workdir(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), &options);
	if (php_git2_check_error(result, "git_diff_tree_to_workdir" TSRMLS_CC)) {
		php_git2_git_diff_options_free(&options);
		RETURN_FALSE
	}

	php_git2_git_diff_options_free(&options);

	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_DIFF, diff, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */

/* {{{ proto long git_diff_tree_to_workdir_with_index(resource $repo, resource $old_tree,  $opts)
 */
PHP_FUNCTION(git_diff_tree_to_workdir_with_index)
{
	int result = 0;
	git_diff *diff = NULL;
	zval *repo = NULL, *old_tree = NULL, *opts = NULL;
	php_git2_t *_repo = NULL, *_old_tree = NULL, *_diff = NULL;
	git_diff_options options = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &old_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_diff_options(&options, opts TSRMLS_CC);
	result = git_diff_tree_to_workdir_with_index(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), opts);
	php_git2_git_diff_options_free(&options);
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
	int result = 0;
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
	git_diff_options _options = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &diff, &options) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_diff_options(&_options, options TSRMLS_CC);
	result = git_diff_find_similar(PHP_GIT2_V(_diff, diff), &_options);
	php_git2_git_diff_options_free(&_options);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_diff_options_init(long $version)
 */
PHP_FUNCTION(git_diff_options_init)
{
	int result = 0;
	git_diff_options options = {0};
	long version = GIT_DIFF_OPTIONS_VERSION;
	zval *out;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|l", &version) == FAILURE) {
		return;
	}

	result = git_diff_options_init(&options, version);
	php_git2_git_diff_options_to_array(&options, &out TSRMLS_CC);
	RETURN_ZVAL(out, 0, 1);
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
	zval *diff = NULL, *_result;
	php_git2_t *_diff = NULL;
	long idx = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &diff, &idx) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_get_delta(PHP_GIT2_V(_diff, diff), idx);
	php_git2_git_diff_delta_to_array(result, &_result TSRMLS_CC);
	RETURN_ZVAL(_result, 0, 1);
}
/* }}} */

/* {{{ proto long git_diff_is_sorted_icase(resource $diff)
 */
PHP_FUNCTION(git_diff_is_sorted_icase)
{
	int result = 0;
	zval *diff = NULL;
	php_git2_t *_diff = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &diff) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_is_sorted_icase(PHP_GIT2_V(_diff, diff));
	RETURN_BOOL(result);
}
/* }}} */


/* {{{ proto long git_diff_foreach(resource $diff, Callable $file_cb, Callable $hunk_cb, Callable $line_cb,  $payload)
 */
PHP_FUNCTION(git_diff_foreach)
{
	int result = 0;
	zval *diff = NULL, *payload = NULL;
	php_git2_t *_diff = NULL;
	zend_fcall_info file_fci = empty_fcall_info;
	zend_fcall_info_cache file_fcc = empty_fcall_info_cache;
	zend_fcall_info hunk_fci = empty_fcall_info;
	zend_fcall_info_cache hunk_fcc = empty_fcall_info_cache;
	zend_fcall_info line_fci = empty_fcall_info;
	zend_fcall_info_cache line_fcc = empty_fcall_info_cache;
	php_git2_multi_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfffz", &diff, &file_fci, &file_fcc, &hunk_fci, &hunk_fcc, &line_fci, &line_fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_multi_cb_init(&cb, payload TSRMLS_CC, 3,
		&file_fci, &file_fcc,
		&hunk_fci, &hunk_fcc,
		&line_fci, &line_fcc
	);

	result = git_diff_foreach(PHP_GIT2_V(_diff, diff), php_git2_git_diff_file_cb, php_git2_git_diff_hunk_cb, php_git2_git_diff_line_cb, cb);
	php_git2_multi_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto string git_diff_status_char( $status)
 */
PHP_FUNCTION(git_diff_status_char)
{
	char result;
	long status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"l", &status) == FAILURE) {
		return;
	}

	result = git_diff_status_char(status);
	RETURN_STRINGL(&result, 1, 1);
}
/* }}} */

/* {{{ proto long git_diff_print(resource $diff, long $format, Callable $print_cb,  $payload)
 */
PHP_FUNCTION(git_diff_print)
{
	int result = 0;
	zval *diff = NULL, *payload = NULL;
	php_git2_t *_diff = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_multi_cb_t *cb = NULL;
	long format = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlfz", &diff, &format, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_multi_cb_init(&cb, payload TSRMLS_CC, 3, &empty_fcall_info, &empty_fcall_info_cache, &empty_fcall_info, &empty_fcall_info_cache, &fci, &fcc)) {
		RETURN_FALSE;
	}
	result = git_diff_print(PHP_GIT2_V(_diff, diff), format, php_git2_git_diff_line_cb, cb);
	php_git2_multi_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_diff_blobs(resource $old_blob, string $old_as_path, resource $new_blob, string $new_as_path,  $options, Callable $file_cb, Callable $hunk_cb, Callable $line_cb,  $payload)
 */
PHP_FUNCTION(git_diff_blobs)
{
	int result = 0, old_as_path_len = 0, new_as_path_len = 0;
	zval *old_blob = NULL, *new_blob = NULL, *options = NULL, *payload = NULL;
	php_git2_t *_old_blob = NULL, *_new_blob = NULL;
	char *old_as_path = NULL, *new_as_path = NULL;
	zend_fcall_info file_fci = empty_fcall_info;
	zend_fcall_info_cache file_fcc = empty_fcall_info_cache;
	zend_fcall_info hunk_fci = empty_fcall_info;
	zend_fcall_info_cache hunk_fcc = empty_fcall_info_cache;
	zend_fcall_info line_fci = empty_fcall_info;
	zend_fcall_info_cache line_fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrsafffz", &old_blob, &old_as_path, &old_as_path_len, &new_blob, &new_as_path, &new_as_path_len, &options,
		  &file_fci, &file_fcc, &hunk_fci, &hunk_fcc, &line_fci, &line_fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_old_blob, php_git2_t*, &old_blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_new_blob, php_git2_t*, &new_blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_multi_cb_init(&cb, payload TSRMLS_CC, 3,
		&file_fci, &file_fcc,
		&hunk_fci, &hunk_fcc,
		&line_fci, &line_fcc
	);
	result = git_diff_blobs(
		PHP_GIT2_V(_old_blob, blob), old_as_path,
		PHP_GIT2_V(_new_blob, blob), new_as_path, NULL,
		php_git2_git_diff_file_cb, php_git2_git_diff_hunk_cb, php_git2_git_diff_line_cb, cb);
	php_git2_multi_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_diff_blob_to_buffer(resource $old_blob, string $old_as_path, string $buffer, long $buffer_len, string $buffer_as_path,  $options, Callable $file_cb, Callable $hunk_cb, Callable $line_cb,  $payload)
 */
PHP_FUNCTION(git_diff_blob_to_buffer)
{
	int result = 0, old_as_path_len = 0, buffer_len = 0, buffer_as_path_len = 0;
	zval *old_blob = NULL, *options = NULL, *payload = NULL;
	php_git2_t *_old_blob = NULL;
	char *old_as_path = NULL, *buffer = NULL, *buffer_as_path = NULL;
	zend_fcall_info file_fci = empty_fcall_info;
	zend_fcall_info_cache file_fcc = empty_fcall_info_cache;
	zend_fcall_info hunk_fci = empty_fcall_info;
	zend_fcall_info_cache hunk_fcc = empty_fcall_info_cache;
	zend_fcall_info line_fci = empty_fcall_info;
	zend_fcall_info_cache line_fcc = empty_fcall_info_cache;
	php_git2_multi_cb_t *cb = NULL;
	git_diff_options opts = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsslsafffz", &old_blob, &old_as_path, &old_as_path_len,
		&buffer, &buffer_len, &buffer_len, &buffer_as_path, &buffer_as_path_len, &options,
		&file_fci, &file_fcc, &hunk_fci, &hunk_fcc, &line_fci, &line_fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_old_blob, php_git2_t*, &old_blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_multi_cb_init(&cb, payload TSRMLS_CC, 3,
		&file_fci, &file_fcc,
		&hunk_fci, &hunk_fcc,
		&line_fci, &line_fcc
	);
	result = git_diff_blob_to_buffer(
		PHP_GIT2_V(_old_blob, blob), old_as_path,
		buffer, buffer_len, buffer_as_path,
		&opts,
		php_git2_git_diff_file_cb, php_git2_git_diff_hunk_cb, php_git2_git_diff_line_cb, cb);
	php_git2_multi_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */
