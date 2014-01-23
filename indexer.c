#include "php_git2.h"
#include "php_git2_priv.h"
#include "indexer.h"

/* {{{ proto resource git_indexer_new(string $path, long $mode, resource $odb,  $progress_cb,  $progress_cb_payload)
 */
PHP_FUNCTION(git_indexer_new)
{
	php_git2_t *result = NULL, *_odb = NULL;
	git_indexer *out = NULL;
	char *path = NULL;
	int path_len = 0, error = 0;
	long mode = 0;
	zval *odb = NULL, *progress_cb_payload = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"slrfz", &path, &path_len, &mode, &odb, &fci, &fcc, &progress_cb_payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, progress_cb_payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	//error = git_indexer_new(&out, path, mode, PHP_GIT2_V(_odb, odb), progress_cb, cb);
	if (php_git2_check_error(error, "git_indexer_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_INDEXER, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_indexer_append(resource $idx,  $data, long $size,  $stats)
 */
PHP_FUNCTION(git_indexer_append)
{

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r<void>l<git_transfer_progress>", &idx, &data, &size, &stats) == FAILURE) {
//		return;
//	}
//
//	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
//	result = git_indexer_append(PHP_GIT2_V(_idx, indexer), data, size, stats);
//	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_indexer_commit(resource $idx,  $stats)
 */
PHP_FUNCTION(git_indexer_commit)
{

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r<git_transfer_progress>", &idx, &stats) == FAILURE) {
//		return;
//	}
//
//	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
//	result = git_indexer_commit(PHP_GIT2_V(_idx, indexer), stats);
//	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_indexer_hash(resource $idx)
 */
PHP_FUNCTION(git_indexer_hash)
{
	const git_oid  *result = NULL;
	zval *idx = NULL;
	php_git2_t *_idx = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &idx) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_indexer_hash(PHP_GIT2_V(_idx, indexer));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto void git_indexer_free(resource $idx)
 */
PHP_FUNCTION(git_indexer_free)
{
	zval *idx = NULL;
	php_git2_t *_idx = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &idx) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_idx, php_git2_t*, &idx, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_idx)) {
		git_indexer_free(PHP_GIT2_V(_idx, indexer));
		GIT2_SHOULD_FREE(_idx) = 0;
	};
	zval_ptr_dtor(&idx);
}
/* }}} */

