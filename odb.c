#include "php_git2.h"
#include "php_git2_priv.h"
#include "odb.h"

/* {{{ proto resource git_odb_new()
 */
PHP_FUNCTION(git_odb_new)
{
	php_git2_t *result = NULL;
	git_odb *out = NULL;
	int error = 0;
	
	error = git_odb_new(&out);
	if (php_git2_check_error(error, "git_odb_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_odb_open(string $objects_dir)
 */
PHP_FUNCTION(git_odb_open)
{
	php_git2_t *result = NULL;
	git_odb *out = NULL;
	char *objects_dir = NULL;
	int objects_dir_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &objects_dir, &objects_dir_len) == FAILURE) {
		return;
	}
	
	error = git_odb_open(&out, objects_dir);
	if (php_git2_check_error(error, "git_odb_open" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_odb_add_disk_alternate(resource $odb, string $path)
 */
PHP_FUNCTION(git_odb_add_disk_alternate)
{
	int result = 0, path_len = 0, error = 0;
	zval *odb = NULL;
	php_git2_t *_odb = NULL;
	char *path = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &odb, &path, &path_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_add_disk_alternate(PHP_GIT2_V(_odb, odb), path);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_odb_free(resource $db)
 */
PHP_FUNCTION(git_odb_free)
{
	zval *db = NULL;
	php_git2_t *_db = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &db) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_db)) {
		git_odb_free(PHP_GIT2_V(_db, odb));
		GIT2_SHOULD_FREE(_db) = 0;
	};
	zval_ptr_dtor(&db);
}
/* }}} */

/* {{{ proto resource git_odb_read(resource $db, string $id)
 */
PHP_FUNCTION(git_odb_read)
{
	php_git2_t *result = NULL, *_db = NULL;
	git_odb_object *out = NULL;
	zval *db = NULL;
	char *id = NULL;
	int id_len = 0, error = 0;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &db, &id, &id_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	error = git_odb_read(&out, PHP_GIT2_V(_db, odb),&__id);
	if (php_git2_check_error(error, "git_odb_read" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_OBJECT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_odb_read_prefix(resource $db, string $short_id, long $len)
 */
PHP_FUNCTION(git_odb_read_prefix)
{
	php_git2_t *result = NULL, *_db = NULL;
	git_odb_object *out = NULL;
	zval *db = NULL;
	char *short_id = NULL;
	int short_id_len = 0, error = 0;
	git_oid __short_id = {0};
	long len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &db, &short_id, &short_id_len, &len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__short_id, short_id, short_id_len)) {
		RETURN_FALSE;
	}
	error = git_odb_read_prefix(&out, PHP_GIT2_V(_db, odb), &__short_id, len);
	if (php_git2_check_error(error, "git_odb_read_prefix" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_OBJECT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_odb_read_header( $type_out, resource $db, string $id)
 */
PHP_FUNCTION(git_odb_read_header)
{
	php_git2_t *result = NULL, *_db = NULL;
	size_t len_out = NULL;
	zval *type_out = NULL, *db = NULL;
	char *id = NULL;
	int id_len = 0, error = 0;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"<git_otype>rs", &type_out, &db, &id, &id_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	error = git_odb_read_header(&len_out, type_out, PHP_GIT2_V(_db, odb), &__id);
	if (php_git2_check_error(error, "git_odb_read_header" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_LONG(len_out);
}
/* }}} */

/* {{{ proto long git_odb_exists(resource $db, string $id)
 */
PHP_FUNCTION(git_odb_exists)
{
	int result = 0, id_len = 0, error = 0;
	zval *db = NULL;
	php_git2_t *_db = NULL;
	char *id = NULL;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &db, &id, &id_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_odb_exists(PHP_GIT2_V(_db, odb), &__id);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_odb_refresh(resource $db)
 */
PHP_FUNCTION(git_odb_refresh)
{
	int result = 0, error = 0;
	zval *db = NULL;
	php_git2_t *_db = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &db) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_refresh(PHP_GIT2_V(_db, odb));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_odb_foreach(resource $db, Callable $cb,  $payload)
 */
PHP_FUNCTION(git_odb_foreach)
{
	int result = 0, error = 0;
	zval *db = NULL, *payload = NULL;
	php_git2_t *_db = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &db, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	// TODO(chobie): implment callback */
	//result = git_odb_foreach(PHP_GIT2_V(_db, odb), <CHANGEME>, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_odb_write(resource $odb,  $data,  $type)
 */
PHP_FUNCTION(git_odb_write)
{
	php_git2_t *result = NULL, *_odb = NULL;
	git_oid out = {0};
	zval *odb = NULL;
	zval *data = NULL;
	long type = 0;
	int error = 0, data_len = 0;
	char buf[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &odb, &data, &data_len, &type) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_odb_write(&out, PHP_GIT2_V(_odb, odb), data, data_len, type);
	if (php_git2_check_error(error, "git_odb_write" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto resource git_odb_open_wstream(resource $db, long $size,  $type)
 */
PHP_FUNCTION(git_odb_open_wstream)
{
	php_git2_t *result = NULL, *_db = NULL;
	git_odb_stream *out = NULL;
	zval *db = NULL;
	long size = 0, type = 0;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rll", &db, &size, &type) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_odb_open_wstream(&out, PHP_GIT2_V(_db, odb), size, type);
	if (php_git2_check_error(error, "git_odb_open_wstream" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_STREAM, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_odb_stream_write(resource $stream, string $buffer)
 */
PHP_FUNCTION(git_odb_stream_write)
{
	int result = 0, buffer_len = 0, error = 0;
	zval *stream = NULL;
	php_git2_t *_stream = NULL;
	char *buffer = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &stream, &buffer, &buffer_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_stream, php_git2_t*, &stream, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_stream_write(PHP_GIT2_V(_stream, odb_stream), buffer, buffer_len);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_odb_stream_finalize_write(resource $stream)
 */
PHP_FUNCTION(git_odb_stream_finalize_write)
{
	php_git2_t *result = NULL, *_stream = NULL;
	git_oid out = {0};
	zval *stream = NULL;
	int error = 0;
	char buf[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &stream) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_stream, php_git2_t*, &stream, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_odb_stream_finalize_write(&out, PHP_GIT2_V(_stream, odb_stream));
	if (php_git2_check_error(error, "git_odb_stream_finalize_write" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto long git_odb_stream_read(resource $stream, string $buffer, long $len)
 */
PHP_FUNCTION(git_odb_stream_read)
{
	int result = 0, buffer_len = 0, error = 0;
	zval *stream = NULL;
	php_git2_t *_stream = NULL;
	char *buffer = NULL;
	long len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &stream, &buffer, &buffer_len, &len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_stream, php_git2_t*, &stream, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_stream_read(PHP_GIT2_V(_stream, odb_stream), buffer, len);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_odb_stream_free(resource $stream)
 */
PHP_FUNCTION(git_odb_stream_free)
{
	zval *stream = NULL;
	php_git2_t *_stream = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &stream) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_stream, php_git2_t*, &stream, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_stream)) {
		git_odb_stream_free(PHP_GIT2_V(_stream, odb_stream));
		GIT2_SHOULD_FREE(_stream) = 0;
	};
	zval_ptr_dtor(&stream);
}
/* }}} */

/* {{{ proto resource git_odb_open_rstream(resource $db, string $oid)
 */
PHP_FUNCTION(git_odb_open_rstream)
{
	php_git2_t *result = NULL, *_db = NULL;
	git_odb_stream *out = NULL;
	zval *db = NULL;
	char *oid = NULL;
	int oid_len = 0, error = 0;
	git_oid __oid = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &db, &oid, &oid_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__oid, oid, oid_len)) {
		RETURN_FALSE;
	}
	error = git_odb_open_rstream(&out, PHP_GIT2_V(_db, odb), &__oid);
	if (php_git2_check_error(error, "git_odb_open_rstream" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_STREAM, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_odb_write_pack(resource $db,  $progress_cb,  $progress_payload)
 */
PHP_FUNCTION(git_odb_write_pack)
{
	php_git2_t *result = NULL, *_db = NULL;
	git_odb_writepack *out = NULL;
	zval *db = NULL, *progress_cb = NULL, *progress_payload = NULL;
	int error = 0;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r<git_transfer_progress_callback>z", &db, &progress_cb, &progress_payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_db, php_git2_t*, &db, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, progress_payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	error = git_odb_write_pack(&out, PHP_GIT2_V(_db, odb), progress_cb, cb);
	if (php_git2_check_error(error, "git_odb_write_pack" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_WRITEPACK, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_odb_hash(string $data, long $type)
 */
PHP_FUNCTION(git_odb_hash)
{
	php_git2_t *result = NULL;
	git_oid out = {0};
	zval *data = NULL;
	int error = 0, data_len = 0;
	long type = 0;
	char buf[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &data, &data_len, &type) == FAILURE) {
		return;
	}
	error = git_odb_hash(&out, data, data_len, type);
	if (php_git2_check_error(error, "git_odb_hash" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto resource git_odb_hashfile(string $path,  $type)
 */
PHP_FUNCTION(git_odb_hashfile)
{
	php_git2_t *result = NULL;
	git_oid out = {0};
	char *path = NULL;
	int path_len = 0, error = 0;
	char buf[GIT2_OID_HEXSIZE] = {0};
	long type = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &path, &path_len, &type) == FAILURE) {
		return;
	}
	error = git_odb_hashfile(&out, path, type);
	if (php_git2_check_error(error, "git_odb_hashfile" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto long git_odb_object_dup(resource $source)
 */
PHP_FUNCTION(git_odb_object_dup)
{
	int result = 0, error = 0;
	git_odb_object *dest = NULL;
	zval *source = NULL;
	php_git2_t *_source = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &source) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_source, php_git2_t*, &source, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_object_dup(&dest, PHP_GIT2_V(_source, odb_object));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_odb_object_free(resource $object)
 */
PHP_FUNCTION(git_odb_object_free)
{
	zval *object = NULL;
	php_git2_t *_object = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_object)) {
		git_odb_object_free(PHP_GIT2_V(_object, odb_object));
		GIT2_SHOULD_FREE(_object) = 0;
	};
	zval_ptr_dtor(&object);
}
/* }}} */

/* {{{ proto resource git_odb_object_id(resource $object)
 */
PHP_FUNCTION(git_odb_object_id)
{
	const git_oid  *result = NULL;
	zval *object = NULL;
	php_git2_t *_object = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_object_id(PHP_GIT2_V(_object, odb_object));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto void git_odb_object_data(resource $object)
 */
PHP_FUNCTION(git_odb_object_data)
{
	zval *object = NULL;
	php_git2_t *_object = NULL;
	const char *buffer;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	buffer = git_odb_object_data(PHP_GIT2_V(_object, odb_object));
	RETURN_STRINGL(buffer, git_odb_object_size(PHP_GIT2_V(_object, odb_object)), 1);
}
/* }}} */

/* {{{ proto long git_odb_object_size(resource $object)
 */
PHP_FUNCTION(git_odb_object_size)
{
	size_t result = 0;
	zval *object = NULL;
	php_git2_t *_object = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_object_size(PHP_GIT2_V(_object, odb_object));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_odb_object_type(resource $object)
 */
PHP_FUNCTION(git_odb_object_type)
{
	git_otype *result = NULL;
	zval *object = NULL;
	php_git2_t *_object = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &object) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_object, php_git2_t*, &object, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_object_type(PHP_GIT2_V(_object, odb_object));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_odb_add_backend(resource $odb, resource $backend, long $priority)
 */
PHP_FUNCTION(git_odb_add_backend)
{
	int result = 0, error = 0;
	zval *odb = NULL, *backend = NULL;
	php_git2_t *_odb = NULL, *_backend = NULL;
	long priority = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrl", &odb, &backend, &priority) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_backend, php_git2_t*, &backend, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_add_backend(PHP_GIT2_V(_odb, odb), PHP_GIT2_V(_backend, odb_backend), priority);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_odb_add_alternate(resource $odb, resource $backend, long $priority)
 */
PHP_FUNCTION(git_odb_add_alternate)
{
	int result = 0, error = 0;
	zval *odb = NULL, *backend = NULL;
	php_git2_t *_odb = NULL, *_backend = NULL;
	long priority = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrl", &odb, &backend, &priority) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_backend, php_git2_t*, &backend, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_add_alternate(PHP_GIT2_V(_odb, odb), PHP_GIT2_V(_backend, odb_backend), priority);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_odb_num_backends(resource $odb)
 */
PHP_FUNCTION(git_odb_num_backends)
{
	size_t result = 0;
	zval *odb = NULL;
	php_git2_t *_odb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &odb) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_odb_num_backends(PHP_GIT2_V(_odb, odb));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_odb_get_backend(resource $odb, long $pos)
 */
PHP_FUNCTION(git_odb_get_backend)
{
	php_git2_t *result = NULL, *_odb = NULL;
	git_odb_backend *out = NULL;
	zval *odb = NULL;
	long pos = 0;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &odb, &pos) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_odb_get_backend(&out, PHP_GIT2_V(_odb, odb), pos);
	if (php_git2_check_error(error, "git_odb_get_backend" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_BACKEND, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

static int php_git2_odb_backend_read(void **buffer, size_t *size, git_otype *type, git_odb_backend *backend, const git_oid *oid)
{
	php_git2_t *result;
	php_git2_odb_backend *php_backend = (php_git2_odb_backend*)backend;
	zval *param_oid = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = php_backend->multi;
	int i = 0, retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls);
	char buf[41] = {0};

	git_oid_fmt(buf, oid);
	MAKE_STD_ZVAL(param_oid);
	ZVAL_STRING(param_oid, buf, 1);

	if (php_git2_call_function_v(&p->callbacks[0].fci, &p->callbacks[0].fcc TSRMLS_CC, &retval_ptr, 1, &param_oid)) {
		return GIT_EUSER;
	}
	if (Z_TYPE_P(retval_ptr) == IS_ARRAY) {
		zval **value, **otype;
		char *pp;

		if (zend_hash_num_elements(Z_ARRVAL_P(retval_ptr)) != 2) {
			return GIT_ENOTFOUND;
		}

		zend_hash_get_current_data(Z_ARRVAL_P(retval_ptr), (void **)&value);
		pp = git_odb_backend_malloc(backend, Z_STRLEN_PP(value));
		memset(pp, '\0', Z_STRLEN_PP(value));
		memcpy(pp, Z_STRVAL_PP(value), Z_STRLEN_PP(value));

		*buffer = pp;
		*size = Z_STRLEN_PP(value);

		zend_hash_move_forward(Z_ARRVAL_P(retval_ptr));
		zend_hash_get_current_data(Z_ARRVAL_P(retval_ptr), (void **)&otype);
		*type = Z_LVAL_PP(otype);
	} else {
		retval = GIT_ENOTFOUND;
	}

	zval_ptr_dtor(&retval_ptr);
	return retval;
}
static int php_git2_odb_backend_write(git_odb_backend *backend, const git_oid *oid, const void *buffer, size_t size, git_otype type)
{
	php_git2_t *result;
	php_git2_odb_backend *php_backend = (php_git2_odb_backend*)backend;
	zval *param_oid = NULL, *param_buffer = NULL, *param_otype = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = php_backend->multi;
	int i = 0, retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls);
	char buf[41] = {0};

	git_oid_fmt(buf, oid);
	MAKE_STD_ZVAL(param_oid);
	MAKE_STD_ZVAL(param_buffer);
	MAKE_STD_ZVAL(param_otype);

	ZVAL_STRING(param_oid, buf, 1);
	ZVAL_STRINGL(param_buffer, buffer, size, 1);
	ZVAL_LONG(param_otype, type);

	if (php_git2_call_function_v(&p->callbacks[1].fci, &p->callbacks[1].fcc TSRMLS_CC, &retval_ptr, 3,
		&param_oid, &param_buffer, &param_otype)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}
static int php_git2_odb_backend_read_prefix(git_oid *out_oid,
                                                    void **buffer_p,
                                                    size_t *len_p,
                                                    git_otype *type_p,
                                                    git_odb_backend *backend,
                                                    const git_oid *short_oid,
                                                    size_t len)
{
	fprintf(stderr, "READ_PREFIX");
}

static int php_git2_odb_backend_read_header(size_t *len_p, git_otype *type_p, git_odb_backend *backend, const git_oid *oid)
{
}
static int php_git2_odb_backend_writestream(git_odb_stream **stream_out, git_odb_backend *_backend, size_t length, git_otype type)
{
	fprintf(stderr, "WRITES");
}
static int php_git2_odb_backend_exists(git_odb_backend *backend, const git_oid *oid)
{
	php_git2_t *result;
	php_git2_odb_backend *php_backend = (php_git2_odb_backend*)backend;
	zval *param_oid = NULL, *retval_ptr = NULL;
	php_git2_multi_cb_t *p = php_backend->multi;
	int i = 0, retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls);
	char buf[41] = {0};

	git_oid_fmt(buf, oid);
	MAKE_STD_ZVAL(param_oid);
	ZVAL_STRING(param_oid, buf, 1);

	if (php_git2_call_function_v(&p->callbacks[5].fci, &p->callbacks[5].fcc TSRMLS_CC, &retval_ptr, 1,
		&param_oid)) {
		return GIT_EUSER;
	}

	retval = Z_LVAL_P(retval_ptr);
	if (retval == 1) {
		retval = 0;
	} else {
		retval = GIT_ENOTFOUND;
	}
	zval_ptr_dtor(&retval_ptr);
	return !retval;

}
static int php_git2_odb_backend_foreach(git_odb_backend *_backend, git_odb_foreach_cb cb, void *data)
{
}
static void php_git2_odb_backend_free(git_odb_backend *_backend)
{
}

PHP_FUNCTION(git_odb_backend_new)
{
	php_git2_odb_backend *backend;
	php_git2_t *result;
	zval *callbacks, *tmp;
	zend_fcall_info read_fci, write_fci, read_prefix_fci, read_header_fci, writestream_fci,
		exists_fci, foreach_fci, free_fci;
	zend_fcall_info_cache read_fcc, write_fcc, read_prefix_fcc, read_header_fcc, writestream_fcc,
		exists_fcc, foreach_fcc, free_fcc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &callbacks) == FAILURE) {
		return;
	}

	backend = ecalloc(1, sizeof(php_git2_odb_backend));

	backend->parent.version = GIT_ODB_BACKEND_VERSION;
	backend->parent.read = &php_git2_odb_backend_read;
	backend->parent.write = &php_git2_odb_backend_write;
	backend->parent.read_prefix = &php_git2_odb_backend_read_prefix;
	backend->parent.read_header = &php_git2_odb_backend_read_header;
	backend->parent.writestream = &php_git2_odb_backend_writestream;
	backend->parent.exists = &php_git2_odb_backend_exists;
	backend->parent.foreach = &php_git2_odb_backend_foreach;
	backend->parent.free = &php_git2_odb_backend_free;

	tmp = php_git2_read_arrval(callbacks, ZEND_STRS("read") TSRMLS_CC);
	if (tmp) {
		php_git2_fcall_info_wrapper2(tmp, &read_fci, &read_fcc TSRMLS_CC);
	}
	tmp = php_git2_read_arrval(callbacks, ZEND_STRS("write") TSRMLS_CC);
	if (tmp) {
		php_git2_fcall_info_wrapper2(tmp, &write_fci, &write_fcc TSRMLS_CC);
	}

	tmp = php_git2_read_arrval(callbacks, ZEND_STRS("exists") TSRMLS_CC);
	if (tmp) {
		php_git2_fcall_info_wrapper2(tmp, &exists_fci, &exists_fcc TSRMLS_CC);
	}


	Z_ADDREF_P(callbacks);
	php_git2_multi_cb_init(&backend->multi, callbacks TSRMLS_CC, 8,
		&read_fci, &read_fcc,
		&write_fci, &write_fcc,
		&read_prefix_fci, &read_prefix_fcc,
		&read_header_fci, &read_header_fcc,
		&writestream_fci, &writestream_fcc,
		&exists_fci, &exists_fcc,
		&foreach_fci, &foreach_fcc,
		&free_fci, &free_fcc
	);

	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_ODB_BACKEND, backend, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}

	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}