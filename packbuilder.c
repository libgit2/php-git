#include "php_git2.h"
#include "php_git2_priv.h"
#include "packbuilder.h"

static int php_git2_git_packbuilder_progress(
	int stage,
	unsigned int current,
	unsigned int total,
	void *payload)
{
	php_git2_t *result;
	zval *param_stage = NULL, *param_current = NULL, *param_total = NULL, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_stage);
	MAKE_STD_ZVAL(param_current);
	MAKE_STD_ZVAL(param_total);
	ZVAL_LONG(param_stage, stage);
	ZVAL_LONG(param_current, current);
	ZVAL_LONG(param_total, total);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 4,
		&param_stage, &param_current, &param_total, &p->payload)) {
		return GIT_EUSER;
	}

	if (retval_ptr) {
		retval = Z_LVAL_P(retval_ptr);
		zval_ptr_dtor(&retval_ptr);
	}
	return retval;
}

static int php_git2_git_packbuilder_foreach_cb(void *buf, size_t size, void *payload)
{
	php_git2_t *result;
	zval *param_buf= NULL, *param_size = NULL, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_buf);
	MAKE_STD_ZVAL(param_size);
	ZVAL_STRINGL(param_buf, buf, size, 1);
	ZVAL_LONG(param_size, size);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 3,
		&param_buf, &param_size, &p->payload)) {
		return GIT_EUSER;
	}

	if (retval_ptr) {
		retval = Z_LVAL_P(retval_ptr);
		zval_ptr_dtor(&retval_ptr);
	}
	return retval;
}


static int php_git2_git_transfer_progress_callback(const git_transfer_progress *stats, void *payload)
{
	php_git2_t *result;
	zval *param_stats = NULL, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	php_git2_git_transfer_progress_to_array(stats, &param_stats TSRMLS_CC);


	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 2,
		&param_stats, &p->payload)) {
		return GIT_EUSER;
	}

	if (retval_ptr) {
		retval = Z_LVAL_P(retval_ptr);
		zval_ptr_dtor(&retval_ptr);
	}
	return retval;
}

/* {{{ proto resource git_packbuilder_new(resource $repo)
 */
PHP_FUNCTION(git_packbuilder_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_packbuilder *out = NULL;
	zval *repo = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_packbuilder_new(&out, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_packbuilder_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_PACKBUILDER, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_packbuilder_set_threads(resource $pb, long $n)
 */
PHP_FUNCTION(git_packbuilder_set_threads)
{
	unsigned int result = 0;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	long n = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &pb, &n) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_packbuilder_set_threads(PHP_GIT2_V(_pb, packbuilder), n);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_insert(resource $pb, string $id, string $name)
 */
PHP_FUNCTION(git_packbuilder_insert)
{
	int result = 0, id_len = 0, name_len = 0, error = 0;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	char *id = NULL, *name = NULL;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &pb, &id, &id_len, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_packbuilder_insert(PHP_GIT2_V(_pb, packbuilder), &__id, name);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_insert_tree(resource $pb, string $id)
 */
PHP_FUNCTION(git_packbuilder_insert_tree)
{
	int result = 0, id_len = 0, error = 0;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	char *id = NULL;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &pb, &id, &id_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_packbuilder_insert_tree(PHP_GIT2_V(_pb, packbuilder), &__id);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_insert_commit(resource $pb, string $id)
 */
PHP_FUNCTION(git_packbuilder_insert_commit)
{
	int result = 0, id_len = 0, error = 0;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	char *id = NULL;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &pb, &id, &id_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_packbuilder_insert_commit(PHP_GIT2_V(_pb, packbuilder), &__id);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_write(resource $pb, string $path, long $mode,  $progress_cb,  $progress_cb_payload)
 */
PHP_FUNCTION(git_packbuilder_write)
{
	int result = 0, path_len = 0, error = 0;
	zval *pb = NULL, *progress_cb = NULL, *progress_cb_payload = NULL;
	php_git2_t *_pb = NULL;
	char *path = NULL;
	long mode = 0;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rslfz", &pb, &path, &path_len, &mode, &fci, &fcc, &progress_cb_payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, progress_cb_payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_packbuilder_write(PHP_GIT2_V(_pb, packbuilder), path, mode, php_git2_git_transfer_progress_callback, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_packbuilder_hash(resource $pb)
 */
PHP_FUNCTION(git_packbuilder_hash)
{
	const git_oid  *result = NULL;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &pb) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_packbuilder_hash(PHP_GIT2_V(_pb, packbuilder));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */


/* {{{ proto long git_packbuilder_foreach(resource $pb, Callable $cb,  $payload)
 */
PHP_FUNCTION(git_packbuilder_foreach)
{
	int result = 0, error = 0;
	zval *pb = NULL, *payload = NULL;
	php_git2_t *_pb = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &pb, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_packbuilder_foreach(PHP_GIT2_V(_pb, packbuilder), php_git2_git_packbuilder_foreach_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_object_count(resource $pb)
 */
PHP_FUNCTION(git_packbuilder_object_count)
{
	uint32_t result = 0;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &pb) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_packbuilder_object_count(PHP_GIT2_V(_pb, packbuilder));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_written(resource $pb)
 */
PHP_FUNCTION(git_packbuilder_written)
{
	uint32_t result = 0;
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &pb) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_packbuilder_written(PHP_GIT2_V(_pb, packbuilder));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_packbuilder_set_callbacks(resource $pb,  $progress_cb,  $progress_cb_payload)
 */
PHP_FUNCTION(git_packbuilder_set_callbacks)
{
	int result = 0, error = 0;
	zval *pb = NULL, *progress_cb = NULL, *progress_cb_payload = NULL;
	php_git2_t *_pb = NULL;
	zend_fcall_info fci = empty_fcall_info, *_fci;
	zend_fcall_info_cache fcc = empty_fcall_info_cache, *_fcc;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &pb, &fci, &fcc, &progress_cb_payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	_fci = emalloc(sizeof(zend_fcall_info));
	_fcc = emalloc(sizeof(zend_fcall_info_cache));
	memcpy(_fci, &fci, sizeof(zend_fcall_info));
	memcpy(_fcc, &fcc, sizeof(zend_fcall_info_cache));

	/* TODO(chobie): free memory when the resource removed */
	if (php_git2_cb_init(&cb, &_fci, &_fcc, progress_cb_payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_packbuilder_set_callbacks(PHP_GIT2_V(_pb, packbuilder), php_git2_git_packbuilder_progress, cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_packbuilder_free(resource $pb)
 */
PHP_FUNCTION(git_packbuilder_free)
{
	zval *pb = NULL;
	php_git2_t *_pb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &pb) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_pb, php_git2_t*, &pb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_pb)) {
		git_packbuilder_free(PHP_GIT2_V(_pb, packbuilder));
		GIT2_SHOULD_FREE(_pb) = 0;
	};
	zval_ptr_dtor(&pb);
}
/* }}} */

