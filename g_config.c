#include "php_git2.h"
#include "php_git2_priv.h"
#include "g_config.h"


enum php_git2_config {
	PHP_GIT2_CONFIG_STRING,
	PHP_GIT2_CONFIG_BOOL,
	PHP_GIT2_CONFIG_INT64,
	PHP_GIT2_CONFIG_INT32,
};

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


/* {{{ proto resource git_config_find_global()
*/
PHP_FUNCTION(git_config_find_global)
{
	char buffer[512];
	size_t buffer_len = 512;
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
	char buffer[512];
	size_t buffer_len = 512;
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
	zval *level;
	php_git2_t *_level;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_add_file_ondisk not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrl", &cfg, &path, &path_len, &level, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_open_ondisk(path)
*/
PHP_FUNCTION(git_config_open_ondisk)
{
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_open_ondisk not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_config_open_level(parent, level)
*/
PHP_FUNCTION(git_config_open_level)
{
	zval *parent;
	php_git2_t *_parent;
	zval *level;
	php_git2_t *_level;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_open_level not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &parent, &level) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_parent, php_git2_t*, &parent, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_open_global(config)
*/
PHP_FUNCTION(git_config_open_global)
{
	zval *config;
	php_git2_t *_config;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_open_global not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &config) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_config, php_git2_t*, &config, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
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

/* {{{ proto void git_config_free(cfg)
*/
PHP_FUNCTION(git_config_free)
{
	zval *cfg;
	php_git2_t *_cfg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cfg) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	if (_cfg->should_free_v) {
		git_config_free(PHP_GIT2_V(_cfg, config));
		_cfg->should_free_v = 0;
	}
	zval_ptr_dtor(&cfg);
}

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

	MAKE_STD_ZVAL(result);
	array_init(result);

	add_assoc_string_ex(result, ZEND_STRS("name"), entry->name, 1);
	add_assoc_string_ex(result, ZEND_STRS("value"), entry->value, 1);
	add_assoc_long_ex(result, ZEND_STRS("level"), entry->level);

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

/* {{{ proto long git_config_get_multivar_foreach(cfg, name, regexp, callback, payload)
*/
PHP_FUNCTION(git_config_get_multivar_foreach)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	char *regexp = {0};
	int regexp_len;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_get_multivar_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssrz", &cfg, &name, &name_len, &regexp, &regexp_len, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_multivar_iterator_new(cfg, name, regexp)
*/
PHP_FUNCTION(git_config_multivar_iterator_new)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	char *regexp = {0};
	int regexp_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_multivar_iterator_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &cfg, &name, &name_len, &regexp, &regexp_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_next(iter)
*/
PHP_FUNCTION(git_config_next)
{
	zval *iter;
	php_git2_t *_iter;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_next not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_config_iterator_free(iter)
*/
PHP_FUNCTION(git_config_iterator_free)
{
	zval *iter;
	php_git2_t *_iter;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_iterator_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_set_int32(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_int32)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	long value;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_set_int32 not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &cfg, &name, &name_len, &value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_set_int64(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_int64)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	long value;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_set_int64 not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &cfg, &name, &name_len, &value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_set_bool(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_bool)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	long value;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_set_bool not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &cfg, &name, &name_len, &value) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_set_string(cfg, name, value)
*/
PHP_FUNCTION(git_config_set_string)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	char *value = {0};
	int value_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_set_string not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &cfg, &name, &name_len, &value, &value_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_set_multivar(cfg, name, regexp, value)
*/
PHP_FUNCTION(git_config_set_multivar)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	char *regexp = {0};
	int regexp_len;
	char *value = {0};
	int value_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_set_multivar not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsss", &cfg, &name, &name_len, &regexp, &regexp_len, &value, &value_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_delete_entry(cfg, name)
*/
PHP_FUNCTION(git_config_delete_entry)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_delete_entry not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &cfg, &name, &name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_delete_multivar(cfg, name, regexp)
*/
PHP_FUNCTION(git_config_delete_multivar)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *name = {0};
	int name_len;
	char *regexp = {0};
	int regexp_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_delete_multivar not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &cfg, &name, &name_len, &regexp, &regexp_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_foreach(cfg, callback, payload)
*/
PHP_FUNCTION(git_config_foreach)
{
	zval *cfg;
	php_git2_t *_cfg;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &cfg, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_iterator_new(cfg)
*/
PHP_FUNCTION(git_config_iterator_new)
{
	zval *cfg;
	php_git2_t *_cfg;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_iterator_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &cfg) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_config_iterator_glob_new(cfg, regexp)
*/
PHP_FUNCTION(git_config_iterator_glob_new)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *regexp = {0};
	int regexp_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_iterator_glob_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &cfg, &regexp, &regexp_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_config_foreach_match(cfg, regexp, callback, payload)
*/
PHP_FUNCTION(git_config_foreach_match)
{
	zval *cfg;
	php_git2_t *_cfg;
	char *regexp = {0};
	int regexp_len;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_foreach_match not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrz", &cfg, &regexp, &regexp_len, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_cfg, php_git2_t*, &cfg, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

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
	char *value = {0};
	int value_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_parse_bool not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &value, &value_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_config_parse_int32(value)
*/
PHP_FUNCTION(git_config_parse_int32)
{
	char *value = {0};
	int value_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_parse_int32 not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &value, &value_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_config_parse_int64(value)
*/
PHP_FUNCTION(git_config_parse_int64)
{
	char *value = {0};
	int value_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_config_parse_int64 not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &value, &value_len) == FAILURE) {
		return;
	}
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
