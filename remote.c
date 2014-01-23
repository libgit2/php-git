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
	zval *remote = NULL, *array = NULL;
	php_git2_t *_remote = NULL;
	git_strarray out = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &remote, &array) == FAILURE) {
		return;
	}

	php_git2_array_to_strarray(&out, array TSRMLS_CC);

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_fetch_refspecs(PHP_GIT2_V(_remote, remote), &out);
	php_git2_strarray_free(&out);
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

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &remote, &refspec, &refspec_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_add_push(PHP_GIT2_V(_remote, remote), refspec);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_remote_get_push_refspecs(array $array, resource $remote)
 */
PHP_FUNCTION(git_remote_get_push_refspecs)
{
	git_strarray _array = {0};
	zval *remote = NULL, *array = NULL;
	php_git2_t *_remote = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ar", &array, &remote) == FAILURE) {
		return;
	}

	php_git2_strarray_to_array(&_array, array TSRMLS_CC);
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_remote_get_push_refspecs(&_array, PHP_GIT2_V(_remote, remote));
	git_strarray_free(&_array);

	RETURN_LONG(error);
}
/* }}} */


/* {{{ proto long git_remote_set_push_refspecs(resource $remote, array $array)
 */
PHP_FUNCTION(git_remote_set_push_refspecs)
{
	int result = 0;
	zval *remote = NULL, *array = NULL;
	php_git2_t *_remote = NULL;
	git_strarray _array = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote, &array) == FAILURE) {
		return;
	}

	php_git2_strarray_to_array(&_array, array TSRMLS_CC);
	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_set_push_refspecs(PHP_GIT2_V(_remote, remote), &_array);
	git_strarray_free(&_array);
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
	php_git2_t *_remote = NULL, *out;
	long n = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &n) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_get_refspec(PHP_GIT2_V(_remote, remote), n);
	if (php_git2_make_resource(&out, PHP_GIT2_TYPE_REFSPEC, result, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(out));
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

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &direction) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_connect(PHP_GIT2_V(_remote, remote), direction);
	RETURN_BOOL(result);
}
/* }}} */

static void php_git2_git_remote_head_to_array(git_remote_head *head, zval **out TSRMLS_DC)
{
	zval *result = NULL;
	char oid[41] = {0}, loid[41] = {0};


	git_oid_fmt(oid, &head->oid);
	git_oid_fmt(loid, &head->loid);

	MAKE_STD_ZVAL(result);
	array_init(result);
	add_assoc_long_ex(result, ZEND_STRS("local"), head->local);
	add_assoc_string_ex(result, ZEND_STRS("oid"), oid, 1);
	add_assoc_string_ex(result, ZEND_STRS("loid"), loid, 1);
	add_assoc_string_ex(result, ZEND_STRS("name"), head->name, 1);

	*out = result;
}

/* {{{ proto resource git_remote_ls(resource $remote)
 */
PHP_FUNCTION(git_remote_ls)
{
	git_remote_head **out = NULL;
	size_t size = 0;
	zval *remote = NULL, *retval = NULL, *container = NULL;
	php_git2_t *_remote = NULL;
	int error = 0, i = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	if (git_remote_connected(PHP_GIT2_V(_remote, remote)) == 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "passed git_remote hasn't been connected");
		RETURN_FALSE;
	}
	error = git_remote_ls(&out, &size, PHP_GIT2_V(_remote, remote));
	if (php_git2_check_error(error, "git_remote_ls" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	MAKE_STD_ZVAL(container);
	array_init(container);
	for (i = 0; i < size; i++) {
		php_git2_git_remote_head_to_array(out[i], &retval TSRMLS_CC);
		add_next_index_zval(container, retval);
	}
	RETURN_ZVAL(container, 0, 1);
}
/* }}} */


/* {{{ proto long git_remote_download(resource $remote)
 */
PHP_FUNCTION(git_remote_download)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

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

typedef struct php_git2_remote_cb_t {
	php_git2_fcall_t callbacks[4];
	zval *payload;
	GIT2_TSRMLS_DECL
} php_git2_remote_cb_t;

static int cred_cb(git_cred **cred, const char *url, const char *username_from_url, unsigned int allowed_types, void *data)
{
	php_git2_t *result;
	zval *param_url = NULL, *param_username_from_url = NULL, *param_allowed_types = NULL, *retval_ptr;
	php_git2_remote_cb_t *cb = (php_git2_remote_cb_t*)data;
	GIT2_TSRMLS_SET(cb->tsrm_ls);
	int retval = 1;

	if (cb != NULL) {
		MAKE_STD_ZVAL(param_url);
		MAKE_STD_ZVAL(param_username_from_url);
		MAKE_STD_ZVAL(param_allowed_types);
		ZVAL_NULL(param_url);
		ZVAL_NULL(param_username_from_url);

		if (url != NULL) {
			ZVAL_STRING(param_url, url, 1);
		}
		if (username_from_url != NULL) {
			ZVAL_STRING(param_username_from_url, username_from_url, 1);
		}
		ZVAL_LONG(param_allowed_types, allowed_types);
		Z_ADDREF_P(cb->payload);
		SEPARATE_ZVAL_TO_MAKE_IS_REF(&cb->payload);

		if (php_git2_call_function_v(&cb->callbacks[0].fci, &cb->callbacks[0].fcc TSRMLS_CC, &retval_ptr, 4,
			&param_url, &param_username_from_url, &param_allowed_types, &cb->payload)) {
				fprintf(stderr, "CALL FUNCTION ERROR");
		}
	}

	if (retval_ptr && Z_TYPE_P(retval_ptr) == IS_RESOURCE) {
		ZEND_FETCH_RESOURCE_NO_RETURN(result, php_git2_t*, &retval_ptr, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
		*cred = PHP_GIT2_V(result, cred);
		zval_ptr_dtor(&retval_ptr);
	}
	return retval;
}

/* {{{ proto long git_remote_set_callbacks(remote, callbacks)
*/
PHP_FUNCTION(git_remote_set_callbacks)
{
	zval *remote;
	php_git2_t *_remote;
	zval *callbacks, *credentials_cb = NULL;
	struct git_remote_callbacks cb = GIT_REMOTE_CALLBACKS_INIT;
	php_git2_remote_cb_t *_payload = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &remote, &callbacks) == FAILURE) {
		return;
	}

	/* TODO(chobie): support other callbacks */
	cb.credentials = cred_cb;
	credentials_cb = php_git2_read_arrval(callbacks, ZEND_STRS("credentials") TSRMLS_CC);

	/* TODO(chobie): can we free payload? */
	_payload = emalloc(sizeof(php_git2_remote_cb_t));
	MAKE_STD_ZVAL(_payload->payload);
	GIT2_TSRMLS_SET2(_payload, TSRMLS_C);

	if (credentials_cb != NULL) {
		char *is_callable_error;

		if(zend_fcall_info_init(credentials_cb, 0, &(_payload->callbacks[0].fci), &(_payload->callbacks[0].fci), NULL, &is_callable_error TSRMLS_CC) == SUCCESS) {
			if (is_callable_error) {
				efree(is_callable_error);
			}
		}
		Z_ADDREF_P(credentials_cb);
	}
	cb.payload = _payload;

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_set_callbacks(PHP_GIT2_V(_remote, remote), &cb);
}

/* {{{ proto resource git_remote_stats(resource $remote)
 */
PHP_FUNCTION(git_remote_stats)
{
	const git_transfer_progress  *result = NULL;
	zval *remote = NULL, *retval = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &remote) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_remote_stats(PHP_GIT2_V(_remote, remote));
	php_git2_git_transfer_progress_to_array(result, &retval TSRMLS_CC);
	RETURN_ZVAL(retval, 0, 1);
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
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_remote_set_autotag(resource $remote,  $value)
 */
PHP_FUNCTION(git_remote_set_autotag)
{
	zval *remote = NULL, *value = NULL;
	php_git2_t *_remote = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &remote, &value) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_remote_set_autotag(PHP_GIT2_V(_remote, remote), value);
}
/* }}} */


static int php_git2_git_remote_rename_problem_cb(const char *problematic_refspec, void *payload)
{
	return 0;
}


/* {{{ proto long git_remote_rename(resource $remote, string $new_name, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_remote_rename)
{
	int result = 0, new_name_len = 0;
	zval *remote = NULL, *payload = NULL;
	php_git2_t *_remote = NULL;
	char *new_name = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsfz", &remote, &new_name, &new_name_len, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_remote, php_git2_t*, &remote, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_remote_rename(PHP_GIT2_V(_remote, remote), new_name, php_git2_git_remote_rename_problem_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_remote_update_fetchhead(resource $remote)
 */
PHP_FUNCTION(git_remote_update_fetchhead)
{
	int result = 0;
	zval *remote = NULL;
	php_git2_t *_remote = NULL;

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

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &remote_name, &remote_name_len) == FAILURE) {
		return;
	}

	result = git_remote_is_valid_name(remote_name);
	RETURN_BOOL(result);
}
/* }}} */

