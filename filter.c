#include "php_git2.h"
#include "php_git2_priv.h"
#include "filter.h"


static int php_git2_git_filter_check_fn(
        git_filter  *self,
        void       **payload,
        const git_filter_source *src,
        const char **attr_values)
{
	php_git2_filter *filter = (php_git2_filter*)self;
	php_git2_t *result, *filter_source;
	zval *param_payload = NULL, *param_source = NULL, *param_attr = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = filter->multi;
	const unsigned char *ptr = self->attributes;
	int last_is_space = 0;
	int attribute_count = 0, len = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	if (self->attributes != NULL) {
		while (*ptr != '\0') {
			if (*ptr == 0x09 || *ptr == 0x20 && last_is_space == 0) {
				attribute_count++;
			}

			if (*ptr == 0x09 || *ptr == 0x20) {
				last_is_space = 1;
			} else {
				last_is_space = 0;
			}
			ptr++;
			len++;
		}
		if (len > 0) {
			attribute_count++;
		}
	}

	MAKE_STD_ZVAL(param_payload);
	MAKE_STD_ZVAL(param_source);
	MAKE_STD_ZVAL(param_attr);
	ZVAL_NULL(param_payload);
	if (php_git2_make_resource(&filter_source, PHP_GIT2_TYPE_FILTER_SOURCE, src, 0 TSRMLS_CC)) {
		return GIT_EUSER;
	}
	ZVAL_RESOURCE(param_source, GIT2_RVAL_P(filter_source));

	array_init(param_attr);

	if (attribute_count > 0) {
		int y = 0;
		for (y = 0; y < attribute_count; y++) {
			if (GIT_ATTR_TRUE(attr_values[y])) {
				add_next_index_bool(param_attr, 1);
			} else if (GIT_ATTR_FALSE(attr_values[y])) {
				add_next_index_bool(param_attr, 0);
			} else if (GIT_ATTR_UNSPECIFIED(attr_values[y])) {
				add_next_index_null(param_attr);
			} else {
				add_next_index_string(param_attr, attr_values[y], 1);
			}
		}
	} else {
	}

	if (php_git2_call_function_v(&p->callbacks[2].fci, &p->callbacks[2].fcc TSRMLS_CC, &retval_ptr, 3,
		&param_payload, &param_source, &param_attr)) {
		return GIT_EUSER;
	}

	if (retval_ptr) {
		result = Z_LVAL_P(retval_ptr);

		/* NOTE(chobie): adjust return value */
		if (result == 0) {
			result = GIT_PASSTHROUGH;
		} else if (result == 1) {
			result = 0;
		}
	}
	zval_ptr_dtor(&retval_ptr);

	return result;
}

static void php_git2_git_filter_shutdown_fn(git_filter *self)
{
	zval *param_self = NULL, *param_payload = NULL, *retval_ptr = NULL;
	php_git2_filter *filter = (php_git2_filter*)self;
	php_git2_multi_cb_t *p = filter->multi;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	MAKE_STD_ZVAL(param_self);
	MAKE_STD_ZVAL(param_payload);
	ZVAL_NULL(param_self);
	ZVAL_NULL(param_payload);

	if (php_git2_call_function_v(&p->callbacks[1].fci, &p->callbacks[1].fcc TSRMLS_CC, &retval_ptr, 2, &param_self, &param_payload)) {
	}
	zval_ptr_dtor(&retval_ptr);
}

static int php_git2_git_filter_init_fn(git_filter *self)
{
	zval *param_self = NULL, *param_payload = NULL, *retval_ptr = NULL;
	php_git2_filter *filter = (php_git2_filter*)self;
	php_git2_multi_cb_t *p = filter->multi;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	MAKE_STD_ZVAL(param_self);
	MAKE_STD_ZVAL(param_payload);
	ZVAL_NULL(param_self);
	ZVAL_NULL(param_payload);

	if (php_git2_call_function_v(&p->callbacks[0].fci, &p->callbacks[0].fcc TSRMLS_CC, &retval_ptr, 2, &param_self, &param_payload)) {
	}
	zval_ptr_dtor(&retval_ptr);
}

static int php_git2_git_filter_apply_fn(
               git_filter    *self,
               void         **payload, /* may be read and/or set */
               git_buf       *to,
               const git_buf *from,
               const git_filter_source *src)
{
	php_git2_filter *filter = (php_git2_filter*)self;
	php_git2_t *filter_source;
	zval *param_payload = NULL, *param_from = NULL, *param_src = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = filter->multi;
	int retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	MAKE_STD_ZVAL(param_payload);
	MAKE_STD_ZVAL(param_from);
	MAKE_STD_ZVAL(param_src);
	ZVAL_NULL(param_payload);
	ZVAL_STRINGL(param_from, from->ptr, from->size, 1);
	if (php_git2_make_resource(&filter_source, PHP_GIT2_TYPE_FILTER_SOURCE, src, 0 TSRMLS_CC)) {
		return GIT_EUSER;
	}
	ZVAL_RESOURCE(param_src, GIT2_RVAL_P(filter_source));

	if (php_git2_call_function_v(&p->callbacks[3].fci, &p->callbacks[3].fcc TSRMLS_CC, &retval_ptr, 3,
		&param_payload, &param_from, &param_src)) {
		return GIT_EUSER;
	}

	if (retval_ptr) {
		if (Z_TYPE_P(retval_ptr) == IS_LONG) {
			retval = Z_LVAL_P(retval_ptr);
		} else {
			if (Z_TYPE_P(retval_ptr) != IS_STRING) {
				convert_to_string(retval_ptr);
			}
			git_buf_set(to, Z_STRVAL_P(retval_ptr), Z_STRLEN_P(retval_ptr));
		}
	}

	zval_ptr_dtor(&retval_ptr);
	return retval;
}

static void php_git2_git_filter_cleanup_fn(
        git_filter *self,
        void       *payload)
{
	zval *param_self = NULL, *param_payload = NULL, *retval_ptr = NULL;
	php_git2_filter *filter = (php_git2_filter*)self;
	php_git2_multi_cb_t *p = filter->multi;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	MAKE_STD_ZVAL(param_self);
	MAKE_STD_ZVAL(param_payload);
	ZVAL_NULL(param_self);
	ZVAL_NULL(param_payload);

	if (php_git2_call_function_v(&p->callbacks[4].fci, &p->callbacks[4].fcc TSRMLS_CC, &retval_ptr, 2, &param_self, &param_payload)) {
	}
}

/* {{{ proto long git_filter_list_load(resource $repo, resource $blob, string $path,  $mode)
 */
PHP_FUNCTION(git_filter_list_load)
{
	int result = 0, path_len = 0;
	git_filter_list *filters = NULL;
	zval *repo = NULL, *blob = NULL;
	php_git2_t *_repo = NULL, *_blob = NULL, *_result;
	char *path = NULL;
	long mode = 0;
	git_blob *__blob = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r|zsl", &repo, &blob, &path, &path_len, &mode) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	if (blob != NULL && Z_TYPE_P(blob) == IS_RESOURCE) {
		ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
		__blob = PHP_GIT2_V(_blob, blob);
	}

	result = git_filter_list_load(&filters, PHP_GIT2_V(_repo, repository), blob, path, mode);
	if (php_git2_check_error(result, "git_filter_list_load" TSRMLS_CC)) {
		RETURN_FALSE
	}
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_FILTER_LIST, filters, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */

/* {{{ proto resource git_filter_list_apply_to_data(resource $filters, resource $in)
 */
PHP_FUNCTION(git_filter_list_apply_to_data)
{
	php_git2_t *_filters = NULL, *_in = NULL;
	git_buf out = {0};
	zval *filters = NULL, *in = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &filters, &in) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_in, php_git2_t*, &in, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_apply_to_data(&out, PHP_GIT2_V(_filters, filter_list), PHP_GIT2_V(_in, buf));
	if (php_git2_check_error(error, "git_filter_list_apply_to_data" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETVAL_STRINGL(out.ptr, out.size, 1);
	git_buf_free(&out);
}
/* }}} */

/* {{{ proto resource git_filter_list_apply_to_file(resource $filters, resource $repo, string $path)
 */
PHP_FUNCTION(git_filter_list_apply_to_file)
{
	php_git2_t *_filters = NULL, *_repo = NULL;
	git_buf out = {0};
	zval *filters = NULL, *repo = NULL;
	char *path = NULL;
	int path_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrs", &filters, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_apply_to_file(&out, PHP_GIT2_V(_filters, filter_list), PHP_GIT2_V(_repo, repository), path);
	if (php_git2_check_error(error, "git_filter_list_apply_to_file" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETVAL_STRINGL(out.ptr, out.size, 1);
	git_buf_free(&out);
}
/* }}} */

/* {{{ proto resource git_filter_list_apply_to_blob(resource $filters, resource $blob)
 */
PHP_FUNCTION(git_filter_list_apply_to_blob)
{
	php_git2_t *result = NULL, *_filters = NULL, *_blob = NULL;
	git_buf out = {0};
	zval *filters = NULL, *blob = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &filters, &blob) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_filter_list_apply_to_blob(&out, PHP_GIT2_V(_filters, filter_list), PHP_GIT2_V(_blob, blob));
	if (php_git2_check_error(error, "git_filter_list_apply_to_blob" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BUF, &out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETVAL_STRINGL(out.ptr, out.size, 1);
	git_buf_free(&out);
}
/* }}} */

/* {{{ proto void git_filter_list_free(resource $filters)
 */
PHP_FUNCTION(git_filter_list_free)
{
	zval *filters = NULL;
	php_git2_t *_filters = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &filters) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_filters, php_git2_t*, &filters, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_filters)) {
		git_filter_list_free(PHP_GIT2_V(_filters, filter_list));
		GIT2_SHOULD_FREE(_filters) = 0;
	};
	zval_ptr_dtor(&filters);
}
/* }}} */


/* sys/filter */

/* {{{ proto resource git_filter_lookup(string $name)
 */
PHP_FUNCTION(git_filter_lookup)
{
	git_filter  *result = NULL;
	char *name = NULL;
	int name_len = 0;
	zval *filter;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}

	result = git_filter_lookup(name);
	if (result == NULL) {
		RETURN_FALSE;
	}
	MAKE_STD_ZVAL(filter);
	array_init(filter);
	add_assoc_long_ex(filter, ZEND_STRS("version"), result->version);

	RETURN_ZVAL(filter, 0, 1);
}
/* }}} */

/* {{{ proto resource git_filter_list_new(resource $repo,  $mode)
 */
PHP_FUNCTION(git_filter_list_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_filter_list *out = NULL;
	zval *repo = NULL;
	long mode = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &repo, &mode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_filter_list_new(&out, PHP_GIT2_V(_repo, repository), mode);
	if (php_git2_check_error(error, "git_filter_list_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_FILTER_LIST, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_filter_list_push(resource $fl, resource $filter, mixed $payload)
 */
PHP_FUNCTION(git_filter_list_push)
{
	int result = 0;
	zval *fl = NULL, *filter = NULL, *payload = NULL;
	php_git2_t *_fl = NULL, *_filter = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr|z", &fl, &filter, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_fl, php_git2_t*, &fl, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_filter, php_git2_t*, &filter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_list_push(PHP_GIT2_V(_fl, filter_list), PHP_GIT2_V(_filter, filter), NULL);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_filter_list_length(resource $fl)
 */
PHP_FUNCTION(git_filter_list_length)
{
	size_t result = 0;
	zval *fl = NULL;
	php_git2_t *_fl = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &fl) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_fl, php_git2_t*, &fl, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_list_length(PHP_GIT2_V(_fl, filter_list));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_filter_source_repo(resource $src)
 */
PHP_FUNCTION(git_filter_source_repo)
{
	git_repository  *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL, *_result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_repo(PHP_GIT2_V(_src, filter_source));
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_REPOSITORY, result, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */

/* {{{ proto string git_filter_source_path(resource $src)
 */
PHP_FUNCTION(git_filter_source_path)
{
	const char  *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_path(PHP_GIT2_V(_src, filter_source));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto long git_filter_source_filemode(resource $src)
 */
PHP_FUNCTION(git_filter_source_filemode)
{
	uint16_t result = 0;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_filemode(PHP_GIT2_V(_src, filter_source));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_filter_source_id(resource $src)
 */
PHP_FUNCTION(git_filter_source_id)
{
	const git_oid  *result = NULL;
	zval *src = NULL;
	php_git2_t *_src = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_id(PHP_GIT2_V(_src, filter_source));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto long git_filter_source_mode(resource $src)
 */
PHP_FUNCTION(git_filter_source_mode)
{
	git_filter_mode_t result;
	zval *src = NULL;
	php_git2_t *_src = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &src) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_src, php_git2_t*, &src, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_source_mode(PHP_GIT2_V(_src, filter_source));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_filter_register(string $name, resource $filter, long $priority)
 */
PHP_FUNCTION(git_filter_register)
{
	int result = 0, name_len = 0;
	char *name = NULL;
	zval *filter = NULL;
	php_git2_t *_filter = NULL;
	long priority = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"srl", &name, &name_len, &filter, &priority) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_filter, php_git2_t*, &filter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_filter_register(name, PHP_GIT2_V(_filter, filter), priority);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_filter_unregister(string $name)
 */
PHP_FUNCTION(git_filter_unregister)
{
	int result = 0, name_len = 0;
	char *name = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &name, &name_len) == FAILURE) {
		return;
	}

	result = git_filter_unregister(name);
	RETURN_LONG(result);
}
/* }}} */

PHP_FUNCTION(git_filter_new)
{
	git_filter *filter = NULL;
	php_git2_t *result = NULL;
	php_git2_filter *_filter = NULL;
	zval *mixed = NULL, *tmp = NULL;
	zend_fcall_info initialize_fci, shutdown_fci, check_fci, apply_fci, cleanup_fci;
	zend_fcall_info_cache initialize_fcc, shutdown_fcc, check_fcc, apply_fcc, cleanup_fcc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &mixed) == FAILURE) {
		return;
	}

	_filter = (php_git2_filter*)ecalloc(1, sizeof(php_git2_filter));
	filter = (git_filter*)&_filter->super;
	filter->version = GIT_FILTER_VERSION;
	filter->attributes = php_git2_read_arrval_string(mixed, ZEND_STRS("attributes") TSRMLS_CC);

	if (tmp = php_git2_read_arrval(mixed, ZEND_STRS("initialize") TSRMLS_CC)) {
		php_git2_fcall_info_wrapper2(tmp, &initialize_fci, &initialize_fcc TSRMLS_CC);
	}
	if (tmp = php_git2_read_arrval(mixed, ZEND_STRS("shutdown") TSRMLS_CC)) {
		php_git2_fcall_info_wrapper2(tmp, &shutdown_fci, &shutdown_fcc TSRMLS_CC);
	}
	if (tmp = php_git2_read_arrval(mixed, ZEND_STRS("check") TSRMLS_CC)) {
		php_git2_fcall_info_wrapper2(tmp, &check_fci, &check_fcc TSRMLS_CC);
	}
	if (tmp = php_git2_read_arrval(mixed, ZEND_STRS("apply") TSRMLS_CC)) {
		php_git2_fcall_info_wrapper2(tmp, &apply_fci, &apply_fcc TSRMLS_CC);
	}
	if (tmp = php_git2_read_arrval(mixed, ZEND_STRS("cleanup") TSRMLS_CC)) {
		php_git2_fcall_info_wrapper2(tmp, &cleanup_fci, &cleanup_fcc TSRMLS_CC);
	}

	filter->initialize = php_git2_git_filter_init_fn;
	filter->shutdown = php_git2_git_filter_shutdown_fn;
	filter->check = php_git2_git_filter_check_fn;
	filter->apply = php_git2_git_filter_apply_fn;
	filter->cleanup = php_git2_git_filter_cleanup_fn;

	Z_ADDREF_P(mixed);
	php_git2_multi_cb_init(&_filter->multi, mixed TSRMLS_CC, 5,
		&initialize_fci, &initialize_fcc,
		&shutdown_fci, &shutdown_fcc,
		&check_fci, &check_fcc,
		&apply_fci, &apply_fcc,
		&cleanup_fci, &cleanup_fcc
	);

	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_FILTER, filter, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
