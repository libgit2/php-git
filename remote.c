#include "php_git2.h"
#include "php_git2_priv.h"
#include "remote.h"

/* {{{ proto resource git_remote_create(resource $repo, string $name, string $url)
 */
PHP_FUNCTION(git_remote_create)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_remote *out = NULL;
	zval *repo = NULL;
	char *name = NULL, *url = NULL;
	int name_len = 0, url_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &name, &name_len, &url, &url_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_create(&out, PHP_GIT2_V(_repo, repository), name, url);
	if (php_git2_check_error(error, "git_remote_create" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REMOTE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_remote_create_with_fetchspec(resource $repo, string $name, string $url, string $fetch)
 */
PHP_FUNCTION(git_remote_create_with_fetchspec)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_remote *out = NULL;
	zval *repo = NULL;
	char *name = NULL, *url = NULL, *fetch = NULL;
	int name_len = 0, url_len = 0, fetch_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsss", &repo, &name, &name_len, &url, &url_len, &fetch, &fetch_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_create_with_fetchspec(&out, PHP_GIT2_V(_repo, repository), name, url, fetch);
	if (php_git2_check_error(error, "git_remote_create_with_fetchspec" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REMOTE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */



/* {{{ proto resource git_remote_create_inmemory(resource $repo, string $fetch, string $url)
 */
PHP_FUNCTION(git_remote_create_inmemory)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_remote *out = NULL;
	zval *repo = NULL;
	char *fetch = NULL, *url = NULL;
	int fetch_len = 0, url_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &fetch, &fetch_len, &url, &url_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_create_inmemory(&out, PHP_GIT2_V(_repo, repository), fetch, url);
	if (php_git2_check_error(error, "git_remote_create_inmemory" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REMOTE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_remote_load(resource $repo, string $name)
 */
PHP_FUNCTION(git_remote_load)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_remote *out = NULL;
	zval *repo = NULL;
	char *name = NULL;
	int name_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_load(&out, PHP_GIT2_V(_repo, repository), name);
	if (php_git2_check_error(error, "git_remote_load" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REMOTE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto long git_remote_save(resource $remote)
 */
PHP_FUNCTION(git_remote_save)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_save(PHP_GIT2_V(_remote, remote));
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto resource git_remote_owner(resource $remote)
 */
PHP_FUNCTION(git_remote_owner)
{
	git_repository  *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL, *__result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_owner(PHP_GIT2_V(_remote, remote));
	if (php_git2_make_resource(&__result, PHP_GIT2_TYPE_REMOTE, result, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(__result));
}
/* }}} */

/* {{{ proto string git_remote_name(resource $remote)
 */
PHP_FUNCTION(git_remote_name)
{
	const char  *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_name(PHP_GIT2_V(_remote, remote));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_remote_url(resource $remote)
 */
PHP_FUNCTION(git_remote_url)
{
	const char  *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_url(PHP_GIT2_V(_remote, remote));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_remote_pushurl(resource $remote)
 */
PHP_FUNCTION(git_remote_pushurl)
{
	const char  *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_pushurl(PHP_GIT2_V(_remote, remote));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto long git_remote_set_url(resource $remote, string $url)
 */
PHP_FUNCTION(git_remote_set_url)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	char *url = NULL;
	int url_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &url, &url_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_url(PHP_GIT2_V(_remote, remote), url);
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto long git_remote_set_pushurl(resource $remote, string $url)
 */
PHP_FUNCTION(git_remote_set_pushurl)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	char *url = NULL;
	int url_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &url, &url_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_pushurl(PHP_GIT2_V(_remote, remote), url);
	RETURN_BOOL(result);
}
/* }}} */


/* {{{ proto long git_remote_add_fetch(resource $remote, string $refspec)
 */
PHP_FUNCTION(git_remote_add_fetch)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	char *refspec = NULL;
	int refspec_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &refspec, &refspec_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_add_fetch(PHP_GIT2_V(_remote, remote), refspec);
	RETURN_BOOL(result);
}
/* }}} */


/* {{{ proto array git_remote_get_fetch_refspecs(resource $remote)
 */
PHP_FUNCTION(git_remote_get_fetch_refspecs)
{
	zval *result;
	git_strarray array = {0};
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_get_fetch_refspecs(&array, PHP_GIT2_V(_remote, remote));
	php_git2_strarray_to_array(&array, &result TSRMLS_CC);
	git_strarray_free(&array);

	RETURN_ZVAL(result, 0, 1);

}
/* }}} */


/* {{{ proto long git_remote_set_fetch_refspecs(resource $remote, array $array)
 */
PHP_FUNCTION(git_remote_set_fetch_refspecs)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	zval *array = NULL;
	int error = 0;

	/* TODO(chobie): implement this */
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r<git_strarray>", &remote, &array) == FAILURE) {
//		return;
//	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_fetch_refspecs(PHP_GIT2_V(_remote, remote), array);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_remote_add_push(resource $remote, string $refspec)
 */
PHP_FUNCTION(git_remote_add_push)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	char *refspec = NULL;
	int refspec_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &refspec, &refspec_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_add_push(PHP_GIT2_V(_remote, remote), refspec);
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto long git_remote_get_push_refspecs(array $array, resource $remote)
 */
PHP_FUNCTION(git_remote_get_push_refspecs)
{
	zval *result;
	git_strarray array = {0};
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"<git_strarray>r", &array, &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_get_push_refspecs(&array, PHP_GIT2_V(_remote, remote));
	php_git2_strarray_to_array(&array, &result TSRMLS_CC);
	git_strarray_free(&array);

	RETURN_ZVAL(result, 0, 1);
}
/* }}} */


/* {{{ proto long git_remote_set_push_refspecs(resource $remote, array $array)
 */
PHP_FUNCTION(git_remote_set_push_refspecs)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	zval *array = NULL;
	int error = 0;

	/* TODO(chobie): implement this */
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r<git_strarray>", &remote, &array) == FAILURE) {
//		return;
//	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_push_refspecs(PHP_GIT2_V(_remote, remote), array);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto void git_remote_clear_refspecs(resource $remote)
 */
PHP_FUNCTION(git_remote_clear_refspecs)
{
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_clear_refspecs(PHP_GIT2_V(_remote, remote));
}
/* }}} */


/* {{{ proto long git_remote_refspec_count(resource $remote)
 */
PHP_FUNCTION(git_remote_refspec_count)
{
	size_t result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_refspec_count(PHP_GIT2_V(_remote, remote));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_remote_get_refspec(resource $remote, long $n)
 */
PHP_FUNCTION(git_remote_get_refspec)
{
	const git_refspec  *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	long n = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &n) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_get_refspec(PHP_GIT2_V(_remote, remote), n);
	/* TODO(chobie): implement this */
}
/* }}} */


/* {{{ proto bool git_remote_connect(resource $remote, long $direction)
 */
PHP_FUNCTION(git_remote_connect)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	long direction = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &direction) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_connect(PHP_GIT2_V(_remote, remote), direction);
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto resource git_remote_ls(long $size, resource $remote)
 */
PHP_FUNCTION(git_remote_ls)
{
	php_git2_t *result = NULL;
	git_remote_head **out = NULL;
	long size = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lr", &size, &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_ls(&out, size, PHP_GIT2_V(_remote, remote));
	if (php_git2_check_error(error, "git_remote_ls" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	/* TODO(chobie): implement this */
}
/* }}} */


/* {{{ proto long git_remote_download(resource $remote)
 */
PHP_FUNCTION(git_remote_download)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_download(PHP_GIT2_V(_remote, remote));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_remote_connected(resource $remote)
 */
PHP_FUNCTION(git_remote_connected)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_connected(PHP_GIT2_V(_remote, remote));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_remote_stop(resource $remote)
 */
PHP_FUNCTION(git_remote_stop)
{
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_stop(PHP_GIT2_V(_remote, remote));
}
/* }}} */

/* {{{ proto void git_remote_disconnect(resource $remote)
 */
PHP_FUNCTION(git_remote_disconnect)
{
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_disconnect(PHP_GIT2_V(_remote, remote));
}
/* }}} */


/* {{{ proto void git_remote_free(resource $remote)
 */
PHP_FUNCTION(git_remote_free)
{
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_remote->should_free_v) {
		git_remote_free(PHP_GIT2_V(_remote, remote));
	};
	zval_ptr_dtor(&remote);
}
/* }}} */


/* {{{ proto long git_remote_update_tips(resource $remote)
 */
PHP_FUNCTION(git_remote_update_tips)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_update_tips(PHP_GIT2_V(_remote, remote));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_remote_fetch(resource $remote)
 */
PHP_FUNCTION(git_remote_fetch)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_fetch(PHP_GIT2_V(_remote, remote));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_remote_valid_url(string $url)
 */
PHP_FUNCTION(git_remote_valid_url)
{
	int result = 0;
	char *url = NULL;
	int url_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &url, &url_len) == FAILURE) {
		return;
	}

	result = git_remote_valid_url(url);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_remote_supported_url(string $url)
 */
PHP_FUNCTION(git_remote_supported_url)
{
	int result = 0;
	char *url = NULL;
	int url_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &url, &url_len) == FAILURE) {
		return;
	}

	result = git_remote_supported_url(url);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_remote_list(resource $repo)
 */
PHP_FUNCTION(git_remote_list)
{
	zval *result = NULL;
	git_strarray out = {0};
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_list(&out, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_remote_list" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	php_git2_strarray_to_array(&out, &result TSRMLS_CC);
	git_strarray_free(&out);

	RETURN_ZVAL(result, 0, 1);
}
/* }}} */


/* {{{ proto void git_remote_check_cert(resource $remote, long $check)
 */
PHP_FUNCTION(git_remote_check_cert)
{
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	long check = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &check) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_check_cert(PHP_GIT2_V(_remote, remote), check);
}
/* }}} */


/* {{{ proto long git_remote_set_transport(resource $remote, resource $transport)
 */
PHP_FUNCTION(git_remote_set_transport)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	zval *transport = NULL;
	php_git2_t *_transport = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &remote, &transport) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_transport, php_git2_t*, &transport, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_transport(PHP_GIT2_V(_remote, remote), PHP_GIT2_V(_transport, transport));
	RETURN_LONG(result);
}
/* }}} */

static int cred_cb(git_cred **cred, const char *url, const char *username_from_url, unsigned int allowed_types, void *data)
{
	fprintf(stderr, "url: %s\n", url);
	fprintf(stderr, "name: %s\n", username_from_url);
	fprintf(stderr, "types: %d\n", allowed_types);

	return 0;
}

typedef struct php_git2_fcall_t {
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
} php_git2_fcall_t;
typedef struct php_git2_remote_cb_t {
	php_git2_fcall_t callbacks[4];
	zval *payload;
} php_git2_remote_cb_t;

/* {{{ proto long git_remote_set_callbacks(remote, callbacks)
*/
PHP_FUNCTION(git_remote_set_callbacks)
{
	zval *remote;
	php_git2_t *_remote;
	zval *callbacks;
	php_git2_t *_callbacks;
	struct git_remote_callbacks cb = GIT_REMOTE_CALLBACKS_INIT;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &remote, &callbacks) == FAILURE) {
		return;
	}

	cb.credentials = cred_cb;

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_set_callbacks(PHP_GIT2_V(_remote, remote), &cb);
}

/* {{{ proto resource git_remote_stats(resource $remote)
 */
PHP_FUNCTION(git_remote_stats)
{
	const git_transfer_progress  *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_stats(PHP_GIT2_V(_remote, remote));
	/* TODO(chobie): implement this */
}
/* }}} */


/* {{{ proto resource git_remote_autotag(resource $remote)
 */
PHP_FUNCTION(git_remote_autotag)
{
	git_remote_autotag_option_t *result = NULL;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_autotag(PHP_GIT2_V(_remote, remote));
	/* TODO(chobie): implement this */
}
/* }}} */

/* {{{ proto void git_remote_set_autotag(resource $remote,  $value)
 */
PHP_FUNCTION(git_remote_set_autotag)
{
	zval *remote = NULL, *value = NULL;
	php_git2_t *_remote = NULL;

	/* TODO(chobie):impelement this */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r<git_remote_autotag_option_t>", &remote, &value) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_set_autotag(PHP_GIT2_V(_remote, remote), value);
}
/* }}} */


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

/* {{{ proto long git_remote_update_fetchhead(resource $remote)
 */
PHP_FUNCTION(git_remote_update_fetchhead)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_update_fetchhead(PHP_GIT2_V(_remote, remote));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_remote_set_update_fetchhead(resource $remote, long $value)
 */
PHP_FUNCTION(git_remote_set_update_fetchhead)
{
	zval *remote = NULL;
	php_git2_t *_remote = NULL;
	long value = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &value) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_set_update_fetchhead(PHP_GIT2_V(_remote, remote), value);
}
/* }}} */

/* {{{ proto long git_remote_is_valid_name(string $remote_name)
 */
PHP_FUNCTION(git_remote_is_valid_name)
{
	int result = 0;
	char *remote_name = NULL;
	int remote_name_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &remote_name, &remote_name_len) == FAILURE) {
		return;
	}

	result = git_remote_is_valid_name(remote_name);
	RETURN_BOOL(result);
}
/* }}} */

