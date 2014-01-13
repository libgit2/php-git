#include "php_git2.h"
#include "php_git2_priv.h"
#include "g_config.h"

enum php_git2_config {
	PHP_GIT2_CONFIG_STRING,
	PHP_GIT2_CONFIG_BOOL,
	PHP_GIT2_CONFIG_INT64,
	PHP_GIT2_CONFIG_INT32,
};

static void php_git2_config_entry_to_array(git_config_entry *entry, zval **result);

static int php_git2_config_foreach_cb(const git_config_entry *entry, void *payload)
{
	php_git2_t *result;
	zval *param_config_entry, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	php_git2_config_entry_to_array(entry, &param_config_entry);
	Z_ADDREF_P(p->payload);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 2, &param_config_entry, &p->payload)) {
		zval_ptr_dtor(&param_config_entry);
		zval_ptr_dtor(&p->payload);
		zend_list_delete(result->resource_id);
		retval = 0;
		return 0;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}


static void php_git2_config_get_with(INTERNAL_FUNCTION_PARAMETERS, enum php_git2_config type)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &cfg, &name, &name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	switch (type) {
		case PHP_GIT2_CONFIG_STRING: {
			const char *ptr;
			error = git_config_get_string(&ptr, PHP_GIT2_V(_cfg, config), name);
			if (php_git2_check_error(error, "git_config_get_string" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_STRING(ptr, 1);
			break;
		}
		case PHP_GIT2_CONFIG_BOOL: {
			int ptr;
			error = git_config_get_bool(&ptr, PHP_GIT2_V(_cfg, config), name);
			if (php_git2_check_error(error, "git_config_get_bool" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_BOOL(ptr);
			break;
		}
		case PHP_GIT2_CONFIG_INT64: {
			int64_t ptr;
			error = git_config_get_int64(&ptr, PHP_GIT2_V(_cfg, config), name);
			if (php_git2_check_error(error, "git_config_get_int64" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_LONG(ptr);
			break;
		}
		case PHP_GIT2_CONFIG_INT32: {
			int32_t ptr;
			error = git_config_get_int32(&ptr, PHP_GIT2_V(_cfg, config), name);
			if (php_git2_check_error(error, "git_config_get_int32" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_LONG(ptr);
			break;
		}
	}
}

static void php_git2_config_set_with(INTERNAL_FUNCTION_PARAMETERS, enum php_git2_config type)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	int error = 0;
	zval *value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsz", &cfg, &name, &name_len, &value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	switch (type) {
		case PHP_GIT2_CONFIG_STRING: {
			if (Z_TYPE_P(value) != IS_STRING) {
				convert_to_string(value);
			}
			error = git_config_set_string(PHP_GIT2_V(_cfg, config), name, Z_STRVAL_P(value));
			if (php_git2_check_error(error, "git_config_set_string" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_TRUE;
			break;
		}
		case PHP_GIT2_CONFIG_BOOL: {
			if (Z_TYPE_P(value) != IS_BOOL) {
				convert_to_bool(value);
			}
			error = git_config_set_bool(PHP_GIT2_V(_cfg, config), name, Z_LVAL_P(value));
			if (php_git2_check_error(error, "git_config_set_bool" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_TRUE;
			break;
		}
		case PHP_GIT2_CONFIG_INT32: {
			if (Z_TYPE_P(value) != IS_LONG) {
				convert_to_long(value);
			}
			error = git_config_set_int32(PHP_GIT2_V(_cfg, config), name, Z_LVAL_P(value));
			if (php_git2_check_error(error, "git_config_set_int32" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_TRUE;
			break;
		}
		case PHP_GIT2_CONFIG_INT64: {
			if (Z_TYPE_P(value) != IS_LONG) {
				convert_to_long(value);
			}
			error = git_config_set_int64(PHP_GIT2_V(_cfg, config), name, Z_LVAL_P(value));
			if (php_git2_check_error(error, "git_config_set_int64" TSRMLS_CC)) {
				RETURN_FALSE
			}
			RETURN_TRUE;
			break;
		}
	}
}


static void php_git2_config_parse_with(INTERNAL_FUNCTION_PARAMETERS, enum php_git2_config type)
{
	char *value = {0};
	int value_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &value, &value_len) == FAILURE) {
		return;
	}

	switch (type) {
		case PHP_GIT2_CONFIG_BOOL: {
			int result;
			result = git_config_parse_bool(&result, value);
			RETURN_BOOL(result);
			break;
		}
		case PHP_GIT2_CONFIG_INT32: {
			int32_t result;
			result = git_config_parse_int32(&result, value);
			RETURN_LONG(result);
			break;
		}
		case PHP_GIT2_CONFIG_INT64: {
			int64_t result;
			result = git_config_parse_int64(&result, value);
			RETURN_LONG(result);
			break;
		}
	}
}

static void php_git2_config_entry_to_array(git_config_entry *entry, zval **result)
{
	zval *tmp;

	MAKE_STD_ZVAL(tmp);
	array_init(tmp);

	add_assoc_string_ex(tmp, ZEND_STRS("name"), entry->name, 1);
	add_assoc_string_ex(tmp, ZEND_STRS("value"), entry->value, 1);
	add_assoc_long_ex(tmp, ZEND_STRS("level"), entry->level);
	*result = tmp;
}

/* {{{ proto resource git_config_find_global()
*/
PHP_FUNCTION(git_config_find_global)
{
	char buffer[GIT2_BUFFER_SIZE];
	size_t buffer_len = GIT2_BUFFER_SIZE;
	int error = 0;

	error = git_config_find_global(buffer, buffer_len);
	if (php_git2_check_error(error, "git_config_find_global" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_STRING(buffer, 1);
}

/* {{{ proto resource git_config_find_xdg(length)
*/
PHP_FUNCTION(git_config_find_xdg)
{

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_find_xdg not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"", &length) == FAILURE) {
//		return;
//	}
}

/* {{{ proto resource git_config_find_system(length)
*/
PHP_FUNCTION(git_config_find_system)
{
	char buffer[GIT2_BUFFER_SIZE];
	size_t buffer_len = GIT2_BUFFER_SIZE;
	int error = 0;

	error = git_config_find_system(buffer, buffer_len);
	if (php_git2_check_error(error, "git_config_find_system" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_STRING(buffer, 1);
}

/* {{{ proto resource git_config_open_default()
*/
PHP_FUNCTION(git_config_open_default)
{
	git_config *config;
	int error = 0;
	php_git2_t *result;

	error = git_config_open_default(&config);
	if (php_git2_check_error(error, "git_config_open_default" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, config) = config;
	result->type = PHP_GIT2_TYPE_CONFIG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_config_new()
*/
PHP_FUNCTION(git_config_new)
{
	git_config *config;
	php_git2_t *result;
	int error = 0;

	error = git_config_new(&config);
	if (php_git2_check_error(error, "git_config_new" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, config) = config;
	result->type = PHP_GIT2_TYPE_CONFIG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto long git_config_add_file_ondisk(cfg, path, level, force)
*/
PHP_FUNCTION(git_config_add_file_ondisk)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *path = {0};
	int path_len;
	long level;
	long force = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrl", &cfg, &path, &path_len, &level, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_add_file_ondisk(PHP_GIT2_V(_cfg, config), path, level, force);
	if (php_git2_check_error(error, "git_config_add_file_ondisk" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto resource git_config_open_ondisk(path)
*/
PHP_FUNCTION(git_config_open_ondisk)
{
	char *path = {0};
	int path_len;
	git_config *config;
	php_git2_t *result;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}
	error = git_config_open_ondisk(&config, path);
	if (php_git2_check_error(error, "git_config_open_ondisk" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, config) = config;
	result->type = PHP_GIT2_TYPE_CONFIG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_config_open_level(parent, level)
*/
PHP_FUNCTION(git_config_open_level)
{
	zval *parent;
	php_git2_t *_parent, *result;
	long level;
	int error = 0;
	git_config *out;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &parent, &level) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_parent, php_git2_t*, &parent, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_config_open_level(&out, PHP_GIT2_V(_parent, config), level);
	if (php_git2_check_error(error, "git_config_open_level" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, config) = out;
	result->type = PHP_GIT2_TYPE_CONFIG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_config_open_global(config)
*/
PHP_FUNCTION(git_config_open_global)
{
	zval *config;
	php_git2_t *_config, *result;
	git_config *out;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &config) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_config, php_git2_t*, &config, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_open_global(&out, PHP_GIT2_V(_config, config));
	if (php_git2_check_error(error, "git_config_open_global" TSRMLS_CC)) {
		RETURN_FALSE
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CONFIG, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto long git_config_refresh(cfg)
*/
PHP_FUNCTION(git_config_refresh)
{
	zval *cfg;
	php_git2_t *_cfg;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cfg) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_refresh(PHP_GIT2_V(_cfg, config));
	if (php_git2_check_error(error, "git_config_refresh" TSRMLS_CC)) {
		RETURN_FALSE
	}

	RETURN_TRUE;
}

/* {{{ proto void git_config_free(resource $cfg)
 */
PHP_FUNCTION(git_config_free)
{
	zval *cfg = NULL;
	php_git2_t *_cfg = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cfg) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_cfg)) {
		git_config_free(PHP_GIT2_V(_cfg, config));
		GIT2_SHOULD_FREE(_cfg) = 0;
	};
	zval_ptr_dtor(&cfg);
}
/* }}} */

/* {{{ proto resource git_config_get_entry(cfg, name)
*/
PHP_FUNCTION(git_config_get_entry)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	git_config_entry *entry;
	int error = 0;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &cfg, &name, &name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_get_entry(&entry, PHP_GIT2_V(_cfg, config), name);
	if (php_git2_check_error(error, "git_config_get_entry" TSRMLS_CC)) {
		RETURN_FALSE
	}

	php_git2_config_entry_to_array(entry, &result);
	RETURN_ZVAL(result, 0, 1);
}

/* {{{ proto resource git_config_get_int32(cfg, name)
*/
PHP_FUNCTION(git_config_get_int32)
{
	php_git2_config_get_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_INT32);
}

/* {{{ proto resource git_config_get_int64(cfg, name)
*/
PHP_FUNCTION(git_config_get_int64)
{
	php_git2_config_get_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_INT64);
}

/* {{{ proto resource git_config_get_bool(cfg, name)
*/
PHP_FUNCTION(git_config_get_bool)
{
	php_git2_config_get_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_BOOL);
}

/* {{{ proto resource git_config_get_string(cfg, name)
*/
PHP_FUNCTION(git_config_get_string)
{
	php_git2_config_get_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_STRING);
}

/* {{{ proto long git_config_get_multivar_foreach(resource $cfg, string $name, string $regexp, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_config_get_multivar_foreach)
{
	int result = 0, name_len = 0, regexp_len = 0, error = 0;
	zval *cfg = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_cfg = NULL;
	char *name = NULL, *regexp = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssfz", &cfg, &name, &name_len, &regexp, &regexp_len, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_config_get_multivar_foreach(PHP_GIT2_V(_cfg, config), name, regexp, php_git2_config_foreach_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_config_multivar_iterator_new(resource $cfg, string $name, string $regexp)
 */
PHP_FUNCTION(git_config_multivar_iterator_new)
{
	php_git2_t *result = NULL, *_cfg = NULL;
	git_config_iterator *out = NULL;
	zval *cfg = NULL;
	char *name = NULL, *regexp = NULL;
	int name_len = 0, regexp_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &cfg, &name, &name_len, &regexp, &regexp_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_multivar_iterator_new(&out, PHP_GIT2_V(_cfg, config), name, regexp);
	if (php_git2_check_error(error, "git_config_multivar_iterator_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CONFIG_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_config_next(resource $iter)
 */
PHP_FUNCTION(git_config_next)
{
	int result = 0, error = 0;
	git_config_entry *entry = NULL;
	zval *iter = NULL;
	php_git2_t *_iter = NULL;
	zval *out;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_config_next(&entry, PHP_GIT2_V(_iter, config_iterator));
	if (result == GIT_ITEROVER || php_git2_check_error(result, "git_config_next" TSRMLS_CC)) {
		RETURN_FALSE
	}
	php_git2_config_entry_to_array(entry, &out);
	RETURN_ZVAL(out, 0, 1);
}
/* }}} */

/* {{{ proto void git_config_iterator_free(resource $iter)
 */
PHP_FUNCTION(git_config_iterator_free)
{
	zval *iter = NULL;
	php_git2_t *_iter = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_iter)) {
		git_config_iterator_free(PHP_GIT2_V(_iter, config_iterator));
		GIT2_SHOULD_FREE(_iter) = 0;
	};
	zval_ptr_dtor(&iter);
}
/* }}} */

/* {{{ proto long git_config_set_int32(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_int32)
{
	php_git2_config_set_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_INT32);
}

/* {{{ proto long git_config_set_int64(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_int64)
{
	php_git2_config_set_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_INT64);
}

/* {{{ proto long git_config_set_bool(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_bool)
{
	php_git2_config_set_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_BOOL);
}

/* {{{ proto long git_config_set_string(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_string)
{
	php_git2_config_set_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_STRING);
}

/* {{{ proto long git_config_set_multivar(resource $cfg, string $name, string $regexp, string $value)
 */
PHP_FUNCTION(git_config_set_multivar)
{
	int result = 0, name_len = 0, regexp_len = 0, value_len = 0, error = 0;
	zval *cfg = NULL;
	php_git2_t *_cfg = NULL;
	char *name = NULL, *regexp = NULL, *value = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsss", &cfg, &name, &name_len, &regexp, &regexp_len, &value, &value_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_config_set_multivar(PHP_GIT2_V(_cfg, config), name, regexp, value);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_config_delete_entry(cfg, name)
*/
PHP_FUNCTION(git_config_delete_entry)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &cfg, &name, &name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_config_delete_entry(PHP_GIT2_V(_cfg, config), name);
	if (php_git2_check_error(error, "git_config_delete_entry" TSRMLS_CC)) {
		RETURN_FALSE
	}

	RETURN_TRUE;
}

/* {{{ proto long git_config_delete_multivar(resource $cfg, string $name, string $regexp)
 */
PHP_FUNCTION(git_config_delete_multivar)
{
	int result = 0, name_len = 0, regexp_len = 0, error = 0;
	zval *cfg = NULL;
	php_git2_t *_cfg = NULL;
	char *name = NULL, *regexp = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &cfg, &name, &name_len, &regexp, &regexp_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_config_delete_multivar(PHP_GIT2_V(_cfg, config), name, regexp);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_config_foreach(resource $cfg,  $callback,  $payload)
 */
PHP_FUNCTION(git_config_foreach)
{
	int result = 0, error = 0;
	zval *cfg = NULL, *callback = NULL;
	php_git2_t *_cfg = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb;
	zval *payload = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &cfg, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_config_foreach(PHP_GIT2_V(_cfg, config), php_git2_config_foreach_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_config_iterator_new(resource $cfg)
 */
PHP_FUNCTION(git_config_iterator_new)
{
	php_git2_t *result = NULL, *_cfg = NULL;
	git_config_iterator *out = NULL;
	zval *cfg = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cfg) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_iterator_new(&out, PHP_GIT2_V(_cfg, config));
	if (php_git2_check_error(error, "git_config_iterator_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CONFIG_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_config_iterator_glob_new(resource $cfg, string $regexp)
 */
PHP_FUNCTION(git_config_iterator_glob_new)
{
	php_git2_t *result = NULL, *_cfg = NULL;
	git_config_iterator *out = NULL;
	zval *cfg = NULL;
	char *regexp = NULL;
	int regexp_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &cfg, &regexp, &regexp_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_config_iterator_glob_new(&out, PHP_GIT2_V(_cfg, config), regexp);
	if (php_git2_check_error(error, "git_config_iterator_glob_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_CONFIG_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_config_foreach_match(resource $cfg, string $regexp, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_config_foreach_match)
{
	int result = 0, regexp_len = 0, error = 0;
	zval *cfg = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_cfg = NULL;
	char *regexp = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsfz", &cfg, &regexp, &regexp_len, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_config_foreach_match(PHP_GIT2_V(_cfg, config), regexp, php_git2_config_foreach_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_config_get_mapped(cfg, name, maps, map_n)
*/
PHP_FUNCTION(git_config_get_mapped)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	zval *maps;
	php_git2_t *_maps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_get_mapped not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rsr", &cfg, &name, &name_len, &maps, &map_n) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_lookup_map_value(maps, map_n, value)
*/
PHP_FUNCTION(git_config_lookup_map_value)
{
	zval *maps;
	php_git2_t *_maps;
	char *value = {0};
	int value_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_lookup_map_value not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rs", &maps, &map_n, &value, &value_len) == FAILURE) {
//		return;
//	}
	ZEND_FETCH_RESOURCE(_maps, php_git2_t*, &maps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_parse_bool(value)
*/
PHP_FUNCTION(git_config_parse_bool)
{
	php_git2_config_parse_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_BOOL);
}

/* {{{ proto resource git_config_parse_int32(value)
*/
PHP_FUNCTION(git_config_parse_int32)
{
	php_git2_config_parse_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_INT32);
}

/* {{{ proto resource git_config_parse_int64(value)
*/
PHP_FUNCTION(git_config_parse_int64)
{
	php_git2_config_parse_with(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GIT2_CONFIG_INT64);
}

/* {{{ proto long git_config_backend_foreach_match(backend, regexp, , ), data)
*/
PHP_FUNCTION(git_config_backend_foreach_match)
{
	zval *backend;
	php_git2_t *_backend;
	char *regexp = {0};
	int regexp_len;
	long ;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_backend_foreach_match not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rsl", &backend, &regexp, &regexp_len, &, &), &data) == FAILURE) {
//		return;
//	}
	ZEND_FETCH_RESOURCE(_backend, php_git2_t*, &backend, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}
