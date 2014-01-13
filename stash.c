#include "php_git2.h"
#include "php_git2_priv.h"
#include "stash.h"

static int php_git2_stash_cb(size_t index,
	const char* message,
	const git_oid *stash_id,
	void *payload)
{
	php_git2_t *result;
	zval *param_index, *param_message,*param_stash_id, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	char _oid[GIT2_OID_HEXSIZE] = {0};
	GIT2_TSRMLS_SET(p->tsrm_ls)

	git_oid_fmt(_oid, stash_id);

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_index);
	MAKE_STD_ZVAL(param_message);
	MAKE_STD_ZVAL(param_stash_id);
	ZVAL_LONG(param_index, index);
	ZVAL_STRING(param_message, message, 1);
	ZVAL_STRING(param_stash_id, _oid, 1);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 4, &param_index, &param_message, &param_stash_id, &p->payload)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}

/* {{{ proto resource git_stash_save(resource $repo, array $stasher, string $message, long $flags)
 */
PHP_FUNCTION(git_stash_save)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_oid out = {0};
	zval *repo = NULL, *stasher = NULL;
	char *message = NULL;
	int message_len = 0, error = 0;
	long flags = 0;
	char buf[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rasl", &repo, &stasher, &message, &message_len, &flags) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_stash_save(&out, PHP_GIT2_V(_repo, repository), stasher, message, flags);
	if (php_git2_check_error(error, "git_stash_save" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto long git_stash_foreach(resource $repo, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_stash_foreach)
{
	int result = 0, error = 0;
	zval *repo = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_repo = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &repo, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_stash_foreach(PHP_GIT2_V(_repo, repository), php_git2_stash_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_stash_drop(resource $repo, long $index)
 */
PHP_FUNCTION(git_stash_drop)
{
	int result = 0, error = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	long index = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &repo, &index) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_stash_drop(PHP_GIT2_V(_repo, repository), index);
	RETURN_LONG(result);
}
/* }}} */

