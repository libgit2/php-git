#include "php_git2.h"
#include "php_git2_priv.h"
#include "diff.h"

static int php_git2_git_diff_file_cb(
	const git_diff_delta *delta,
	float progress,
	void *payload)
{
	php_git2_t *result;
	zval *param_delta = NULL, *param_progress = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = (php_git2_multi_cb_t*)payload;
	int i = 0, retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_progress);
	ZVAL_DOUBLE(param_progress, progress);
	php_git2_diff_delta_to_array(delta, &param_delta TSRMLS_CC);
	if (php_git2_call_function_v(&p->callbacks[0].fci, &p->callbacks[0].fcc TSRMLS_CC, &retval_ptr, 3, &param_delta, &param_progress, &p->payload)) {
		return GIT_EUSER;
	}
	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);

	return retval;
}

static int php_git2_git_diff_hunk_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	void *payload)
{
	php_git2_t *result;
	zval *param_delta = NULL, *param_hunk = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = (php_git2_multi_cb_t*)payload;
	int i = 0, retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	php_git2_diff_delta_to_array(delta, &param_delta TSRMLS_CC);
	php_git2_diff_hunk_to_array(hunk, &param_hunk TSRMLS_CC);

	if (php_git2_call_function_v(&p->callbacks[1].fci, &p->callbacks[1].fcc TSRMLS_CC, &retval_ptr, 3, &param_delta, &param_hunk, &p->payload)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}

static int php_git2_git_diff_line_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	void *payload) {
	php_git2_t *result;
	zval *param_delta = NULL, *param_hunk = NULL, *param_line = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = (php_git2_multi_cb_t*)payload;
	int i = 0, retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	php_git2_diff_delta_to_array(delta, &param_delta TSRMLS_CC);
	php_git2_diff_hunk_to_array(hunk, &param_hunk TSRMLS_CC);
	php_git2_diff_line_to_array(line, &param_line TSRMLS_CC);

	if (php_git2_call_function_v(&p->callbacks[2].fci, &p->callbacks[2].fcc TSRMLS_CC, &retval_ptr, 4, &param_delta, &param_hunk, &param_line, &p->payload)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}

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
	php_git2_t *_repo = NULL, *_old_tree = NULL, *_result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &old_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_old_tree, php_git2_t*, &old_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_diff_tree_to_workdir(&diff, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_old_tree, tree), NULL);

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


/* {{{ proto long git_diff_foreach(resource $diff, Callable $file_cb, Callable $hunk_cb, Callable $line_cb,  $payload)
 */
PHP_FUNCTION(git_diff_foreach)
{
	int result = 0, error = 0;
	zval *diff = NULL, *file_cb = NULL, *hunk_cb = NULL, *line_cb = NULL, *payload = NULL;
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
	int result = 0, error = 0;
	zval *diff = NULL, *print_cb = NULL, *payload = NULL;
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
	int result = 0, old_as_path_len = 0, new_as_path_len = 0, error = 0;
	zval *old_blob = NULL, *new_blob = NULL, *options = NULL, *file_cb = NULL, *hunk_cb = NULL, *line_cb = NULL, *payload = NULL;
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
	int result = 0, old_as_path_len = 0, buffer_len = 0, buffer_as_path_len = 0, error = 0;
	zval *old_blob = NULL, *options = NULL, *file_cb = NULL, *hunk_cb = NULL, *line_cb = NULL, *payload = NULL;
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
