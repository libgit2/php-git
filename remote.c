#include "php_git2.h"
#include "php_git2_priv.h"
#include "remote.h"

/* {{{ proto resource git_remote_create(repo, name, url)
*/
PHP_FUNCTION(git_remote_create)
{
	zval *repo;
	php_git2_t *_repo;
	char *name = {0};
	int name_len;
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_create not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &name, &name_len, &url, &url_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_create_with_fetchspec(repo, name, url, fetch)
*/
PHP_FUNCTION(git_remote_create_with_fetchspec)
{
	zval *repo;
	php_git2_t *_repo;
	char *name = {0};
	int name_len;
	char *url = {0};
	int url_len;
	char *fetch = {0};
	int fetch_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_create_with_fetchspec not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsss", &repo, &name, &name_len, &url, &url_len, &fetch, &fetch_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_create_inmemory(repo, fetch, url)
*/
PHP_FUNCTION(git_remote_create_inmemory)
{
	zval *repo;
	php_git2_t *_repo;
	char *fetch = {0};
	int fetch_len;
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_create_inmemory not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &fetch, &fetch_len, &url, &url_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_load(repo, name)
*/
PHP_FUNCTION(git_remote_load)
{
	zval *repo;
	php_git2_t *_repo;
	char *name = {0};
	int name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_load not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_save(remote)
*/
PHP_FUNCTION(git_remote_save)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_save not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_owner(remote)
*/
PHP_FUNCTION(git_remote_owner)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_owner not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_name(remote)
*/
PHP_FUNCTION(git_remote_name)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_name not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_url(remote)
*/
PHP_FUNCTION(git_remote_url)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_url not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_pushurl(remote)
*/
PHP_FUNCTION(git_remote_pushurl)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_pushurl not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_set_url(remote, url)
*/
PHP_FUNCTION(git_remote_set_url)
{
	zval *remote;
	php_git2_t *_remote;
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_url not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &url, &url_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_set_pushurl(remote, url)
*/
PHP_FUNCTION(git_remote_set_pushurl)
{
	zval *remote;
	php_git2_t *_remote;
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_pushurl not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &url, &url_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_add_fetch(remote, refspec)
*/
PHP_FUNCTION(git_remote_add_fetch)
{
	zval *remote;
	php_git2_t *_remote;
	char *refspec = {0};
	int refspec_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_add_fetch not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &refspec, &refspec_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_get_fetch_refspecs(array, remote)
*/
PHP_FUNCTION(git_remote_get_fetch_refspecs)
{
	zval *array;
	php_git2_t *_array;
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_get_fetch_refspecs not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &array, &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_array, php_git2_t*, &array, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_set_fetch_refspecs(remote, array)
*/
PHP_FUNCTION(git_remote_set_fetch_refspecs)
{
	zval *remote;
	php_git2_t *_remote;
	zval *array;
	php_git2_t *_array;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_fetch_refspecs not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &array) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_add_push(remote, refspec)
*/
PHP_FUNCTION(git_remote_add_push)
{
	zval *remote;
	php_git2_t *_remote;
	char *refspec = {0};
	int refspec_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_add_push not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &refspec, &refspec_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_get_push_refspecs(array, remote)
*/
PHP_FUNCTION(git_remote_get_push_refspecs)
{
	zval *array;
	php_git2_t *_array;
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_get_push_refspecs not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &array, &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_array, php_git2_t*, &array, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_set_push_refspecs(remote, array)
*/
PHP_FUNCTION(git_remote_set_push_refspecs)
{
	zval *remote;
	php_git2_t *_remote;
	zval *array;
	php_git2_t *_array;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_push_refspecs not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &array) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_clear_refspecs(remote)
*/
PHP_FUNCTION(git_remote_clear_refspecs)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_clear_refspecs not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_refspec_count(remote)
*/
PHP_FUNCTION(git_remote_refspec_count)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_refspec_count not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_get_refspec(remote, n)
*/
PHP_FUNCTION(git_remote_get_refspec)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_get_refspec not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &remote, &n) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_connect(remote, direction)
*/
PHP_FUNCTION(git_remote_connect)
{
	zval *remote;
	php_git2_t *_remote;
	zval *direction;
	php_git2_t *_direction;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_connect not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &direction) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_ls(size, remote)
*/
PHP_FUNCTION(git_remote_ls)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_ls not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &size, &remote) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_size, php_git2_t*, &size, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_download(remote)
*/
PHP_FUNCTION(git_remote_download)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_download not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_connected(remote)
*/
PHP_FUNCTION(git_remote_connected)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_connected not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_stop(remote)
*/
PHP_FUNCTION(git_remote_stop)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_stop not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_disconnect(remote)
*/
PHP_FUNCTION(git_remote_disconnect)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_disconnect not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_free(remote)
*/
PHP_FUNCTION(git_remote_free)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_update_tips(remote)
*/
PHP_FUNCTION(git_remote_update_tips)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_update_tips not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_fetch(remote)
*/
PHP_FUNCTION(git_remote_fetch)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_fetch not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_valid_url(url)
*/
PHP_FUNCTION(git_remote_valid_url)
{
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_valid_url not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &url, &url_len) == FAILURE) {
		return;
	}
}

/* {{{ proto long git_remote_supported_url(url)
*/
PHP_FUNCTION(git_remote_supported_url)
{
	char *url = {0};
	int url_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_supported_url not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &url, &url_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_remote_list(repo)
*/
PHP_FUNCTION(git_remote_list)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_list not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_check_cert(remote, check)
*/
PHP_FUNCTION(git_remote_check_cert)
{
	zval *remote;
	php_git2_t *_remote;
	long check;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_check_cert not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &check) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_set_transport(remote, transport)
*/
PHP_FUNCTION(git_remote_set_transport)
{
	zval *remote;
	php_git2_t *_remote;
	zval *transport;
	php_git2_t *_transport;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_transport not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &transport) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_set_callbacks(remote, callbacks)
*/
PHP_FUNCTION(git_remote_set_callbacks)
{
	zval *remote;
	php_git2_t *_remote;
	zval *callbacks;
	php_git2_t *_callbacks;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_callbacks not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &callbacks) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_stats(remote)
*/
PHP_FUNCTION(git_remote_stats)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_stats not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_remote_autotag(remote)
*/
PHP_FUNCTION(git_remote_autotag)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_autotag not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_set_autotag(remote, value)
*/
PHP_FUNCTION(git_remote_set_autotag)
{
	zval *remote;
	php_git2_t *_remote;
	zval *value;
	php_git2_t *_value;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_autotag not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_rename(remote, new_name, callback, payload)
*/
PHP_FUNCTION(git_remote_rename)
{
	zval *remote;
	php_git2_t *_remote;
	char *new_name = {0};
	int new_name_len;
	zval *callback;
	php_git2_t *_callback;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_rename not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rsr", &remote, &new_name, &new_name_len, &callback, &payload) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_update_fetchhead(remote)
*/
PHP_FUNCTION(git_remote_update_fetchhead)
{
	zval *remote;
	php_git2_t *_remote;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_update_fetchhead not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_remote_set_update_fetchhead(remote, value)
*/
PHP_FUNCTION(git_remote_set_update_fetchhead)
{
	zval *remote;
	php_git2_t *_remote;
	long value;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_set_update_fetchhead not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_remote_is_valid_name(remote_name)
*/
PHP_FUNCTION(git_remote_is_valid_name)
{
	char *remote_name = {0};
	int remote_name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_remote_is_valid_name not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &remote_name, &remote_name_len) == FAILURE) {
		return;
	}
}

