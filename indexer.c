#include "php_git2.h"
#include "php_git2_priv.h"
#include "indexer.h"

/* {{{ proto resource git_indexer_new(path, mode, odb, progress_cb, progress_cb_payload)
*/
PHP_FUNCTION(git_indexer_new)
{
	char *path = {0};
	int path_len;
	long mode;
	zval *odb;
	php_git2_t *_odb;
	zval *progress_cb;
	php_git2_t *_progress_cb;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_indexer_new not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"slrr", &path, &path_len, &mode, &odb, &progress_cb, &progress_cb_payload) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_path, php_git2_t*, &path, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_indexer_append(idx, data, size, stats)
*/
PHP_FUNCTION(git_indexer_append)
{
	zval *idx;
	php_git2_t *_idx;
	zval *stats;
	php_git2_t *_stats;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_indexer_append not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rr", &idx, &data, &size, &stats) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_indexer_commit(idx, stats)
*/
PHP_FUNCTION(git_indexer_commit)
{
	zval *idx;
	php_git2_t *_idx;
	zval *stats;
	php_git2_t *_stats;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_indexer_commit not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &idx, &stats) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_indexer_hash(idx)
*/
PHP_FUNCTION(git_indexer_hash)
{
	zval *idx;
	php_git2_t *_idx;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_indexer_hash not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &idx) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_indexer_free(idx)
*/
PHP_FUNCTION(git_indexer_free)
{
	zval *idx;
	php_git2_t *_idx;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_indexer_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &idx) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

