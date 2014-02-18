#include "php_git2.h"
#include "php_git2_priv.h"
#include "transport.h"

static int php_git2_transport_cb(git_transport **out, git_remote *owner, void *param)
{
	zval *param_owner, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)param;
	php_git2_t *_param_owner;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_owner);
	if (php_git2_make_resource(&_param_owner, PHP_GIT2_TYPE_REMOTE, owner, 0 TSRMLS_CC)) {
		return 0;
	}
	ZVAL_RESOURCE(param_owner, GIT2_RVAL_P(_param_owner));

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 2, &param_owner, &p->payload)) {
		return GIT_EUSER;
	}

	/* TODO(chobie): implement this */

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}


/* {{{ proto resource git_transport_new(resource $owner, string $url)
 */
PHP_FUNCTION(git_transport_new)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_transport *out = NULL;
	zval *owner = NULL;
	char *url = NULL;
	int url_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &owner, &url, &url_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_transport_new(&out, PHP_GIT2_V(_owner, remote), url);
	if (php_git2_check_error(error, "git_transport_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_transport_register(string $prefix,  $priority, Callable $cb, $param)
 */
PHP_FUNCTION(git_transport_register)
{
	int result = 0, prefix_len = 0;
	char *prefix = NULL;
	long priority = NULL;
	zval *param = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"slfz", &prefix, &prefix_len, &priority, &fci, &fcc, &param) == FAILURE) {
		return;
	}

	if (php_git2_cb_init(&cb, &fci, &fcc, param TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_transport_register(prefix, priority, php_git2_transport_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_transport_unregister(string $prefix,  $priority)
 */
PHP_FUNCTION(git_transport_unregister)
{
	int result = 0, prefix_len = 0;
	char *prefix = NULL;
	long priority = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &prefix, &prefix_len, &priority) == FAILURE) {
		return;
	}

	result = git_transport_unregister(prefix, priority);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_transport_dummy(resource $owner)
 */
PHP_FUNCTION(git_transport_dummy)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_transport *out = NULL;
	zval *owner = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_transport_dummy(&out, PHP_GIT2_V(_owner, remote), NULL);
	if (php_git2_check_error(error, "git_transport_dummy" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_transport_local(resource $owner)
 */
PHP_FUNCTION(git_transport_local)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_transport *out = NULL;
	zval *owner = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_transport_local(&out, PHP_GIT2_V(_owner, remote), NULL);
	if (php_git2_check_error(error, "git_transport_local" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_transport_smart(resource $owner,  $payload)
 */
PHP_FUNCTION(git_transport_smart)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_transport *out = NULL;
	zval *owner = NULL, *payload = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r</* (git_smart_subtransport_definition *) */ void>", &owner, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_transport_smart(&out, PHP_GIT2_V(_owner, remote), payload);
	if (php_git2_check_error(error, "git_transport_smart" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_smart_subtransport_http(resource $owner)
 */
PHP_FUNCTION(git_smart_subtransport_http)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_smart_subtransport *out = NULL;
	zval *owner = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_smart_subtransport_http(&out, PHP_GIT2_V(_owner, transport));
	if (php_git2_check_error(error, "git_smart_subtransport_http" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_SMART_SUBTRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_smart_subtransport_git(resource $owner)
 */
PHP_FUNCTION(git_smart_subtransport_git)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_smart_subtransport *out = NULL;
	zval *owner = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_smart_subtransport_git(&out, PHP_GIT2_V(_owner, transport));
	if (php_git2_check_error(error, "git_smart_subtransport_git" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_SMART_SUBTRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_smart_subtransport_ssh(resource $owner)
 */
PHP_FUNCTION(git_smart_subtransport_ssh)
{
	php_git2_t *result = NULL, *_owner = NULL;
	git_smart_subtransport *out = NULL;
	zval *owner = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_smart_subtransport_ssh(&out, PHP_GIT2_V(_owner, transport));
	if (php_git2_check_error(error, "git_smart_subtransport_ssh" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_SMART_SUBTRANSPORT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */
