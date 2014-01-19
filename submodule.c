#include "php_git2.h"
#include "php_git2_priv.h"
#include "submodule.h"

static int php_git2_git_submodule_foreach_cb(git_submodule *sm, const char *name, void *payload)
{
	php_git2_t *result, *submodule;
	zval *param_sm, *param_name, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_sm);
	MAKE_STD_ZVAL(param_name);
	if (php_git2_make_resource(&submodule, PHP_GIT2_TYPE_SUBMODULE, sm, 0 TSRMLS_CC)) {
		return GIT_EUSER;
	}
	ZVAL_RESOURCE(param_sm, GIT2_RVAL_P(submodule));

	ZVAL_STRING(param_name, name, 1);
	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 3,
		&param_sm, &param_name, &p->payload)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;


}

/* {{{ proto long git_submodule_lookup(resource $repo, string $name)
 */
PHP_FUNCTION(git_submodule_lookup)
{
	int result = 0, name_len = 0, error = 0;
	git_submodule *submodule = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL, *_result = NULL;
	char *name = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_lookup(&submodule, PHP_GIT2_V(_repo, repository), name);
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_SUBMODULE, submodule, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */

/* {{{ proto long git_submodule_foreach(resource $repo, Callable $callback, $payload)
 */
PHP_FUNCTION(git_submodule_foreach)
{
	int result = 0, name_len = 0, error = 0;
	zval *repo = NULL, *payload = NULL;
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
	result = git_submodule_foreach(PHP_GIT2_V(_repo, repository), php_git2_git_submodule_foreach_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_add_setup(resource $repo, string $url, string $path, long $use_gitlink)
 */
PHP_FUNCTION(git_submodule_add_setup)
{
	int result = 0, url_len = 0, path_len = 0, error = 0;
	git_submodule *submodule = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *url = NULL, *path = NULL;
	long use_gitlink = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssl", &repo, &url, &url_len, &path, &path_len, &use_gitlink) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_add_setup(&submodule, PHP_GIT2_V(_repo, repository), url, path, use_gitlink);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_add_finalize(resource $submodule)
 */
PHP_FUNCTION(git_submodule_add_finalize)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_add_finalize(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_add_to_index(resource $submodule, long $write_index)
 */
PHP_FUNCTION(git_submodule_add_to_index)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	long write_index = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &submodule, &write_index) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_add_to_index(PHP_GIT2_V(_submodule, submodule), write_index);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_save(resource $submodule)
 */
PHP_FUNCTION(git_submodule_save)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_save(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_submodule_owner(resource $submodule)
 */
PHP_FUNCTION(git_submodule_owner)
{
	git_repository  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL, *__result = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_owner(PHP_GIT2_V(_submodule, submodule));
	if (php_git2_make_resource(&__result, PHP_GIT2_TYPE_REPOSITORY, result, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(__result));
}
/* }}} */

/* {{{ proto string git_submodule_name(resource $submodule)
 */
PHP_FUNCTION(git_submodule_name)
{
	const char  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_name(PHP_GIT2_V(_submodule, submodule));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_submodule_path(resource $submodule)
 */
PHP_FUNCTION(git_submodule_path)
{
	const char  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_path(PHP_GIT2_V(_submodule, submodule));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_submodule_url(resource $submodule)
 */
PHP_FUNCTION(git_submodule_url)
{
	const char  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_url(PHP_GIT2_V(_submodule, submodule));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto long git_submodule_set_url(resource $submodule, string $url)
 */
PHP_FUNCTION(git_submodule_set_url)
{
	int result = 0, url_len = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	char *url = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &submodule, &url, &url_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_set_url(PHP_GIT2_V(_submodule, submodule), url);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto string git_submodule_index_id(resource $submodule)
 */
PHP_FUNCTION(git_submodule_index_id)
{
	const git_oid  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_index_id(PHP_GIT2_V(_submodule, submodule));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto string git_submodule_head_id(resource $submodule)
 */
PHP_FUNCTION(git_submodule_head_id)
{
	const git_oid  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_head_id(PHP_GIT2_V(_submodule, submodule));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto string git_submodule_wd_id(resource $submodule)
 */
PHP_FUNCTION(git_submodule_wd_id)
{
	const git_oid  *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_wd_id(PHP_GIT2_V(_submodule, submodule));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto long git_submodule_ignore(resource $submodule)
 */
PHP_FUNCTION(git_submodule_ignore)
{
	git_submodule_ignore_t *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_ignore(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_set_ignore(resource $submodule,  $ignore)
 */
PHP_FUNCTION(git_submodule_set_ignore)
{
	git_submodule_ignore_t *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	long ignore = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &submodule, &ignore) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_set_ignore(PHP_GIT2_V(_submodule, submodule), ignore);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_submodule_update(resource $submodule)
 */
PHP_FUNCTION(git_submodule_update)
{
	git_submodule_update_t *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_update(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_submodule_set_update(resource $submodule,  $update)
 */
PHP_FUNCTION(git_submodule_set_update)
{
	git_submodule_update_t *result = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	long update = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &submodule, &update) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_set_update(PHP_GIT2_V(_submodule, submodule), update);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_fetch_recurse_submodules(resource $submodule)
 */
PHP_FUNCTION(git_submodule_fetch_recurse_submodules)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_fetch_recurse_submodules(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_set_fetch_recurse_submodules(resource $submodule, long $fetch_recurse_submodules)
 */
PHP_FUNCTION(git_submodule_set_fetch_recurse_submodules)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	long fetch_recurse_submodules = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &submodule, &fetch_recurse_submodules) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_set_fetch_recurse_submodules(PHP_GIT2_V(_submodule, submodule), fetch_recurse_submodules);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_init(resource $submodule, long $overwrite)
 */
PHP_FUNCTION(git_submodule_init)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	long overwrite = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &submodule, &overwrite) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_init(PHP_GIT2_V(_submodule, submodule), overwrite);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_sync(resource $submodule)
 */
PHP_FUNCTION(git_submodule_sync)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_sync(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_open(resource $submodule)
 */
PHP_FUNCTION(git_submodule_open)
{
	int result = 0, error = 0;
	git_repository *repo = NULL;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_open(&repo, PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_reload(resource $submodule)
 */
PHP_FUNCTION(git_submodule_reload)
{
	int result = 0, error = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_reload(PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_reload_all(resource $repo)
 */
PHP_FUNCTION(git_submodule_reload_all)
{
	int result = 0, error = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_reload_all(PHP_GIT2_V(_repo, repository));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_status(long $status, resource $submodule)
 */
PHP_FUNCTION(git_submodule_status)
{
	int result = 0, error = 0;
	long status = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lr", &status, &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_status(status, PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_submodule_location(long $location_status, resource $submodule)
 */
PHP_FUNCTION(git_submodule_location)
{
	int result = 0, error = 0;
	long location_status = 0;
	zval *submodule = NULL;
	php_git2_t *_submodule = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lr", &location_status, &submodule) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_submodule, php_git2_t*, &submodule, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_submodule_location(location_status, PHP_GIT2_V(_submodule, submodule));
	RETURN_LONG(result);
}
/* }}} */

