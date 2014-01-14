#include "php_git2.h"
#include "php_git2_priv.h"
#include "push.h"

/* {{{ proto resource git_push_new(resource $remote)
 */
PHP_FUNCTION(git_push_new)
{
	php_git2_t *result = NULL, *_remote = NULL;
	git_push *out = NULL;
	zval *remote = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_push_new(&out, PHP_GIT2_V(_remote, remote));
	if (php_git2_check_error(error, "git_push_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PUSH, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_push_set_options(resource $push,  $opts)
 */
PHP_FUNCTION(git_push_set_options)
{
	int result = 0, error = 0;
	zval *push = NULL, *opts = NULL;
	php_git2_t *_push = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r<git_push_options>", &push, &opts) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	//result = git_push_set_options(PHP_GIT2_V(_push, push), opts);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_push_set_callbacks(resource $push,  $pack_progress_cb,  $pack_progress_cb_payload,  $transfer_progress_cb,  $transfer_progress_cb_payload)
 */
PHP_FUNCTION(git_push_set_callbacks)
{
	int result = 0, error = 0;
	zval *push = NULL, *pack_progress_cb = NULL, *pack_progress_cb_payload = NULL, *transfer_progress_cb = NULL, *transfer_progress_cb_payload = NULL;
	php_git2_t *_push = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz<git_push_transfer_progress>z", &push, &fci, &fcc, &pack_progress_cb_payload, &transfer_progress_cb, &transfer_progress_cb_payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
//	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
//		RETURN_FALSE;
//	}
	//result = git_push_set_callbacks(PHP_GIT2_V(_push, push), <CHANGEME>, cb, transfer_progress_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_push_add_refspec(resource $push, string $refspec)
 */
PHP_FUNCTION(git_push_add_refspec)
{
	int result = 0, refspec_len = 0, error = 0;
	zval *push = NULL;
	php_git2_t *_push = NULL;
	char *refspec = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &push, &refspec, &refspec_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_push_add_refspec(PHP_GIT2_V(_push, push), refspec);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_push_update_tips(resource $push)
 */
PHP_FUNCTION(git_push_update_tips)
{
	int result = 0, error = 0;
	zval *push = NULL;
	php_git2_t *_push = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &push) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_push_update_tips(PHP_GIT2_V(_push, push));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_push_finish(resource $push)
 */
PHP_FUNCTION(git_push_finish)
{
	int result = 0, error = 0;
	zval *push = NULL;
	php_git2_t *_push = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &push) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_push_finish(PHP_GIT2_V(_push, push));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_push_unpack_ok(resource $push)
 */
PHP_FUNCTION(git_push_unpack_ok)
{
	int result = 0, error = 0;
	zval *push = NULL;
	php_git2_t *_push = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &push) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_push_unpack_ok(PHP_GIT2_V(_push, push));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_push_status_foreach(resource $push, string $ref, string $msg,  $data),  $data)
 */
PHP_FUNCTION(git_push_status_foreach)
{
	int result = 0, ref_len = 0, msg_len = 0, error = 0;
	zval *push = NULL;
	php_git2_t *_push = NULL;
	char *ref = NULL, *msg = NULL;
	
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rss<void><void>", &push, &ref, &ref_len, &msg, &msg_len, &data, &data) == FAILURE) {
//		return;
//	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	//result = git_push_status_foreach(PHP_GIT2_V(_push, push), ref, msg, data);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_push_free(resource $push)
 */
PHP_FUNCTION(git_push_free)
{
	zval *push = NULL;
	php_git2_t *_push = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &push) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_push, php_git2_t*, &push, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_push)) {
		git_push_free(PHP_GIT2_V(_push, push));
		GIT2_SHOULD_FREE(_push) = 0;
	};
	zval_ptr_dtor(&push);
}
/* }}} */

