#include "php_git2.h"
#include "php_git2_priv.h"
#include "transport.h"

/* {{{ proto resource git_transport_new(owner, url)
*/
PHP_FUNCTION(git_transport_new)
{
	zval *owner;
	php_git2_t *_owner;
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_transport_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &owner, &url, &url_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_transport_register(prefix, priority, cb, param)
*/
PHP_FUNCTION(git_transport_register)
{
	char *prefix = {0};
	int prefix_len;
	zval *cb;
	php_git2_t *_cb;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_transport_register not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"sr", &prefix, &prefix_len, &priority, &cb, &param) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_prefix, php_git2_t*, &prefix, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_transport_unregister(prefix, priority)
*/
PHP_FUNCTION(git_transport_unregister)
{
	char *prefix = {0};
	int prefix_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_transport_unregister not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"s", &prefix, &prefix_len, &priority) == FAILURE) {
//		return;
//	}
}

/* {{{ proto resource git_transport_dummy(owner, payload)
*/
PHP_FUNCTION(git_transport_dummy)
{
	zval *owner;
	php_git2_t *_owner;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_transport_dummy not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &owner, &payload) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_transport_local(owner, payload)
*/
PHP_FUNCTION(git_transport_local)
{
	zval *owner;
	php_git2_t *_owner;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_transport_local not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &owner, &payload) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_transport_smart(owner, payload)
*/
PHP_FUNCTION(git_transport_smart)
{
	zval *owner;
	php_git2_t *_owner;
	zval *payload;
	php_git2_t *_payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_transport_smart not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &owner, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_smart_subtransport_http(owner)
*/
PHP_FUNCTION(git_smart_subtransport_http)
{
	zval *owner;
	php_git2_t *_owner;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_smart_subtransport_http not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_smart_subtransport_git(owner)
*/
PHP_FUNCTION(git_smart_subtransport_git)
{
	zval *owner;
	php_git2_t *_owner;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_smart_subtransport_git not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_smart_subtransport_ssh(owner)
*/
PHP_FUNCTION(git_smart_subtransport_ssh)
{
	zval *owner;
	php_git2_t *_owner;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_smart_subtransport_ssh not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &owner) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_owner, php_git2_t*, &owner, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

