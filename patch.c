#include "php_git2.h"
#include "php_git2_priv.h"
#include "patch.h"

/* {{{ proto resource git_patch_from_diff(diff, idx)
*/
PHP_FUNCTION(git_patch_from_diff)
{
	zval *diff;
	php_git2_t *_diff;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_from_diff not implemented yet");
	return;

}

/* {{{ proto resource git_patch_from_blobs(old_blob, old_as_path, new_blob, new_as_path, opts)
*/
PHP_FUNCTION(git_patch_from_blobs)
{
	zval *old_blob;
	php_git2_t *_old_blob;
	char *old_as_path = {0};
	int old_as_path_len;
	zval *new_blob;
	php_git2_t *_new_blob;
	char *new_as_path = {0};
	int new_as_path_len;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_from_blobs not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrsr", &old_blob, &old_as_path, &old_as_path_len, &new_blob, &new_as_path, &new_as_path_len, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_old_blob, php_git2_t*, &old_blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_patch_from_blob_and_buffer(old_blob, old_as_path, buffer, buffer_len, buffer_as_path, opts)
*/
PHP_FUNCTION(git_patch_from_blob_and_buffer)
{
	zval *old_blob;
	php_git2_t *_old_blob;
	char *old_as_path = {0};
	int old_as_path_len;
	char *buffer = {0};
	int buffer_len;
	char *buffer_as_path = {0};
	int buffer_as_path_len;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_from_blob_and_buffer not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsssr", &old_blob, &old_as_path, &old_as_path_len, &buffer, &buffer_len, &buffer_len, &buffer_as_path, &buffer_as_path_len, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_old_blob, php_git2_t*, &old_blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_patch_free(patch)
*/
PHP_FUNCTION(git_patch_free)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &patch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_patch, php_git2_t*, &patch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_patch_get_delta(patch)
*/
PHP_FUNCTION(git_patch_get_delta)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_get_delta not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &patch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_patch, php_git2_t*, &patch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_patch_num_hunks(patch)
*/
PHP_FUNCTION(git_patch_num_hunks)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_num_hunks not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &patch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_patch, php_git2_t*, &patch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_patch_line_stats(total_context, total_additions, total_deletions, patch)
*/
PHP_FUNCTION(git_patch_line_stats)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_line_stats not implemented yet");
	return;

}

/* {{{ proto resource git_patch_get_hunk(lines_in_hunk, patch, hunk_idx)
*/
PHP_FUNCTION(git_patch_get_hunk)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_get_hunk not implemented yet");
	return;
}

/* {{{ proto long git_patch_num_lines_in_hunk(patch, hunk_idx)
*/
PHP_FUNCTION(git_patch_num_lines_in_hunk)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_num_lines_in_hunk not implemented yet");
	return;
}

/* {{{ proto resource git_patch_get_line_in_hunk(patch, hunk_idx, line_of_hunk)
*/
PHP_FUNCTION(git_patch_get_line_in_hunk)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_get_line_in_hunk not implemented yet");
	return;
}

/* {{{ proto resource git_patch_size(patch, include_context, include_hunk_headers, include_file_headers)
*/
PHP_FUNCTION(git_patch_size)
{
	zval *patch;
	php_git2_t *_patch;
	long include_context;
	long include_hunk_headers;
	long include_file_headers;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_size not implemented yet");
	return;
}

/* {{{ proto long git_patch_print(patch, print_cb, payload)
*/
PHP_FUNCTION(git_patch_print)
{
	zval *patch;
	php_git2_t *_patch;
	zval *print_cb;
	php_git2_t *_print_cb;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_print not implemented yet");
	return;
}

/* {{{ proto resource git_patch_to_str(patch)
*/
PHP_FUNCTION(git_patch_to_str)
{
	zval *patch;
	php_git2_t *_patch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_patch_to_str not implemented yet");
	return;
}
