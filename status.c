#include "php_git2.h"
#include "php_git2_priv.h"
#include "status.h"

static void php_git2_git_status_options_to_array(git_status_options *options, zval **out TSRMLS_DC)
{
	zval *result, *pathspec;

	MAKE_STD_ZVAL(result);
	array_init(result);

	add_assoc_long_ex(result, ZEND_STRS("version"), options->version);
	add_assoc_long_ex(result, ZEND_STRS("show"), options->show);
	add_assoc_long_ex(result, ZEND_STRS("flags"), options->flags);
	php_git2_strarray_to_array(&options->pathspec, &pathspec TSRMLS_CC);
	add_assoc_zval_ex(result, ZEND_STRS("pathspec"), pathspec);

	*out = result;
}

static void php_git2_array_to_git_status_options(git_status_options *options, zval *array TSRMLS_DC)
{
	options->version = php_git2_read_arrval_long2(array, ZEND_STRS("version"), 1 TSRMLS_CC);
	options->show = php_git2_read_arrval_long2(array, ZEND_STRS("version"), 0 TSRMLS_CC);
	options->flags = php_git2_read_arrval_long2(array, ZEND_STRS("version"), 0 TSRMLS_CC);

	php_git2_array_to_strarray(&options->pathspec, php_git2_read_arrval(array, ZEND_STRS("pathspec") TSRMLS_CC) TSRMLS_CC);
}

static void php_git2_git_status_entry_to_array(git_status_entry *entry, zval **out TSRMLS_DC)
{
	zval *result, *head_to_index, *index_to_workdir;

	MAKE_STD_ZVAL(result);
	array_init(result);

	if (entry->head_to_index) {
		php_git2_diff_delta_to_array(entry->head_to_index, &head_to_index TSRMLS_CC);
	} else {
		MAKE_STD_ZVAL(head_to_index);
		ZVAL_NULL(head_to_index);
	}

	if (entry->index_to_workdir) {
		php_git2_diff_delta_to_array(entry->index_to_workdir, &index_to_workdir TSRMLS_CC);
	} else {
		MAKE_STD_ZVAL(index_to_workdir);
		ZVAL_NULL(index_to_workdir);
	}

	add_assoc_long_ex(result, ZEND_STRS("status"), entry->status);
	add_assoc_zval_ex(result, ZEND_STRS("head_to_index"), head_to_index);
	add_assoc_zval_ex(result, ZEND_STRS("index_to_workdir"), index_to_workdir);

	*out = result;
}

static int php_git2_git_status_cb(
	const char *path, unsigned int status_flags, void *payload)
{
	zval *param_path, *param_status_flags, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_path);
	MAKE_STD_ZVAL(param_status_flags);
	ZVAL_STRING(param_path, path, 1);
	ZVAL_LONG(param_status_flags, status_flags);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 3,
		&param_path, &param_status_flags, &p->payload)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}

/* {{{ proto long git_status_foreach(resource $repo, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_status_foreach)
{
	int result = 0;
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
	result = git_status_foreach(PHP_GIT2_V(_repo, repository), php_git2_git_status_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_status_foreach_ext(resource $repo,  $opts, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_status_foreach_ext)
{
	int result = 0;
	zval *repo = NULL, *opts = NULL, *payload = NULL;
	php_git2_t *_repo = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	git_status_options options = GIT_STATUS_OPTIONS_INIT;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rafz", &repo, &opts, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_status_options(&options, opts TSRMLS_CC);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_status_foreach_ext(PHP_GIT2_V(_repo, repository), &options, php_git2_git_status_cb, cb);
	php_git2_cb_free(cb);
	if (options.pathspec.count > 0) {
		php_git2_strarray_free(&options.pathspec);
	}
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_status_file(long $status_flags, resource $repo, string $path)
 */
PHP_FUNCTION(git_status_file)
{
	int result = 0, path_len = 0;
	long status_flags = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *path = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &status_flags, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_status_file(&status_flags, PHP_GIT2_V(_repo, repository), path);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_status_list_new(resource $repo,  $opts)
 */
PHP_FUNCTION(git_status_list_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_status_list *out = NULL;
	zval *repo = NULL, *opts = NULL;
	git_status_options options = GIT_STATUS_OPTIONS_INIT;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &repo, &opts) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_status_options(&options, opts TSRMLS_CC);
	error = git_status_list_new(&out, PHP_GIT2_V(_repo, repository), &options);
	if (options.pathspec.count > 0) {
		php_git2_strarray_free(&options.pathspec);
	}
	if (php_git2_check_error(error, "git_status_list_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_STATUS_LIST, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_status_list_entrycount(resource $statuslist)
 */
PHP_FUNCTION(git_status_list_entrycount)
{
	size_t result = 0;
	zval *statuslist = NULL;
	php_git2_t *_statuslist = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &statuslist) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_status_list_entrycount(PHP_GIT2_V(_statuslist, status_list));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_status_byindex(resource $statuslist, long $idx)
 */
PHP_FUNCTION(git_status_byindex)
{
	const git_status_entry  *result = NULL;
	zval *statuslist = NULL, *out;
	php_git2_t *_statuslist = NULL;
	long idx = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &statuslist, &idx) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_status_byindex(PHP_GIT2_V(_statuslist, status_list), idx);
	if (result == NULL) {
		RETURN_FALSE;
	}
	php_git2_git_status_entry_to_array(result, &out TSRMLS_CC);
	RETURN_ZVAL(out, 0, 1);
}
/* }}} */

/* {{{ proto void git_status_list_free(resource $statuslist)
 */
PHP_FUNCTION(git_status_list_free)
{
	zval *statuslist = NULL;
	php_git2_t *_statuslist = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &statuslist) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_statuslist, php_git2_t*, &statuslist, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_statuslist)) {
		git_status_list_free(PHP_GIT2_V(_statuslist, status_list));
		GIT2_SHOULD_FREE(_statuslist) = 0;
	};
	zval_ptr_dtor(&statuslist);
}
/* }}} */

/* {{{ proto long git_status_should_ignore(long $ignored, resource $repo, string $path)
 */
PHP_FUNCTION(git_status_should_ignore)
{
	int result = 0, path_len = 0;
	long ignored = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *path = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &ignored, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_status_should_ignore(ignored, PHP_GIT2_V(_repo, repository), path);
	RETURN_LONG(result);
}
/* }}} */

PHP_FUNCTION(git_status_options_new)
{
	git_status_options options = GIT_STATUS_OPTIONS_INIT;
	zval *result;

	php_git2_git_status_options_to_array(&options, &result TSRMLS_CC);
	RETURN_ZVAL(result, 0, 1);
}
