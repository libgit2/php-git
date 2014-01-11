#include "php_git2.h"
#include "php_git2_priv.h"
#include "cred.h"

/* {{{ proto long git_cred_has_username(cred)
*/
PHP_FUNCTION(git_cred_has_username)
{
	zval *cred;
	php_git2_t *_cred;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_has_username not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cred) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cred, php_git2_t*, &cred, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_cred_userpass_plaintext_new(username, password)
*/
PHP_FUNCTION(git_cred_userpass_plaintext_new)
{
	char *username = {0};
	int username_len;
	char *password = {0};
	int password_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_userpass_plaintext_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss", &username, &username_len, &password, &password_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_cred_ssh_key_new(username, publickey, privatekey, passphrase)
*/
PHP_FUNCTION(git_cred_ssh_key_new)
{
	char *username = {0};
	int username_len;
	char *publickey = {0};
	int publickey_len;
	char *privatekey = {0};
	int privatekey_len;
	char *passphrase = {0};
	int passphrase_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_ssh_key_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ssss", &username, &username_len, &publickey, &publickey_len, &privatekey, &privatekey_len, &passphrase, &passphrase_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_cred_ssh_custom_new(username, publickey, publickey_len, sign_fn, sign_data)
*/
PHP_FUNCTION(git_cred_ssh_custom_new)
{
	char *username = {0};
	int username_len;
	char *publickey = {0};
	int publickey_len;
	zval *sign_fn;
	php_git2_t *_sign_fn;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_ssh_custom_new not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"ssr", &username, &username_len, &publickey, &publickey_len, &publickey_len, &sign_fn, &sign_data) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_username, php_git2_t*, &username, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_cred_default_new()
*/
PHP_FUNCTION(git_cred_default_new)
{

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_default_new not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"", ) == FAILURE) {
//		return;
//	}
}

/* {{{ proto resource git_cred_userpass(url, user_from_url, allowed_types, payload)
*/
PHP_FUNCTION(git_cred_userpass)
{
	char *url = {0};
	int url_len;
	char *user_from_url = {0};
	int user_from_url_len;
	long allowed_types;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_cred_userpass not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"ssl", &url, &url_len, &user_from_url, &user_from_url_len, &allowed_types, &payload) == FAILURE) {
//		return;
//	}
}

