#include "php_git2.h"
#include "php_git2_priv.h"
#include "blob.h"

/* {{{ proto resource git_blob_create_frombuffer(resource $repository, string $buffer)
*/
PHP_FUNCTION(git_blob_create_frombuffer)
{
	zval *repository;
	php_git2_t *git2;
	char *buffer;
	int buffer_len;
	int error;
	git_oid id;
	char out[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repository, &buffer, &buffer_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_blob_create_frombuffer(&id, PHP_GIT2_V(git2, repository), buffer, buffer_len);
	if (php_git2_check_error(error, "git_blob_create_frombuffer" TSRMLS_CC)) {
		RETURN_FALSE
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto long git_blob_create_fromchunks(string $id, resource $repo, string $hintpath, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_blob_create_fromchunks)
{
	int result = 0, id_len = 0, hintpath_len = 0, error = 0;
	char *id = NULL, *hintpath = NULL;
	git_oid __id = {0};
	zval *repo = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_repo = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"srsfz", &id, &id_len, &repo, &hintpath, &hintpath_len, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	// TODO(chobie) implement this */
	//result = git_blob_create_fromchunks(__id, PHP_GIT2_V(_repo, repository), hintpath, <CHANGEME>, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_blob_create_fromdisk(resource $repository, string $path)
*/
PHP_FUNCTION(git_blob_create_fromdisk)
{
	zval *repository;
	php_git2_t *git2;
	char *path;
	int path_len;
	int error;
	git_oid id;
	char out[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repository, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_blob_create_fromdisk(&id, PHP_GIT2_V(git2, repository), path);
	if (php_git2_check_error(error, "git_blob_create_fromdisk" TSRMLS_CC)) {
		RETURN_FALSE
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto resource git_blob_create_fromworkdir(resource $repository, string $relative_path)
*/
PHP_FUNCTION(git_blob_create_fromworkdir)
{
	zval *repository;
	php_git2_t *git2;
	char *path;
	int path_len;
	int error;
	git_oid id;
	char out[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repository, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_blob_create_fromworkdir(&id, PHP_GIT2_V(git2, repository), path);
	if (php_git2_check_error(error, "git_blob_create_fromdisk" TSRMLS_CC)) {
		RETURN_FALSE
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto resource git_blob_filtered_content(resource $blob, string $as_path, long $check_for_binary_data)
 */
PHP_FUNCTION(git_blob_filtered_content)
{
	php_git2_t *result = NULL, *_blob = NULL;
	git_buf out = {0};
	zval *blob = NULL;
	char *as_path = NULL;
	int as_path_len = 0, error = 0;
	long check_for_binary_data = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &blob, &as_path, &as_path_len, &check_for_binary_data) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_blob_filtered_content(&out, PHP_GIT2_V(_blob, blob), as_path, check_for_binary_data);
	if (php_git2_check_error(error, "git_blob_filtered_content" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BUF, &out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto void git_blob_free(resource $blob)
 */
PHP_FUNCTION(git_blob_free)
{
	zval *blob = NULL;
	php_git2_t *_blob = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_blob)) {
		git_blob_free(PHP_GIT2_V(_blob, blob));
		GIT2_SHOULD_FREE(_blob) = 0;
	};
	zval_ptr_dtor(&blob);
}
/* }}} */

/* {{{ proto resource git_blob_id(resource $blob)
*/
PHP_FUNCTION(git_blob_id)
{
	zval *blob;
	php_git2_t *git2;
	char out[GIT2_OID_HEXSIZE] = {0};
	const git_oid *id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	id = git_blob_id(PHP_GIT2_V(git2, blob));

	git_oid_fmt(out, id);
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto resource git_blob_is_binary(resource $blob)
*/
PHP_FUNCTION(git_blob_is_binary)
{
	zval *blob;
	php_git2_t *git2;
	int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_blob_is_binary(PHP_GIT2_V(git2, blob));
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto long git_blob_lookup(resource $repo, string $id)
 */
PHP_FUNCTION(git_blob_lookup)
{
	int result = 0, id_len = 0, error = 0;
	git_blob *blob = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL, *_result = NULL;
	char *id = NULL;
	git_oid __id = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &id, &id_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_blob_lookup(&blob, PHP_GIT2_V(_repo, repository), &__id);
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_BLOB, blob, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */


/* {{{ proto long git_blob_lookup_prefix(resource $repo, string $id, long $len)
 */
PHP_FUNCTION(git_blob_lookup_prefix)
{
	int result = 0, id_len = 0, error = 0;
	git_blob *blob = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL, *_result = NULL;
	char *id = NULL;
	git_oid __id = {0};
	long len = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &id, &id_len, &len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_blob_lookup_prefix(&blob, PHP_GIT2_V(_repo, repository), &__id, len);
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_BLOB, blob, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */


/* {{{ proto resource git_blob_owner(resource $blob)
 */
PHP_FUNCTION(git_blob_owner)
{
	git_repository  *result = NULL;
	zval *blob = NULL;
	php_git2_t *_blob = NULL, *__result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_blob, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_blob_owner(PHP_GIT2_V(_blob, blob));
	if (php_git2_make_resource(&__result, PHP_GIT2_TYPE_BLOB, result, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(__result));
}
/* }}} */


/* {{{ proto resource git_blob_rawcontent(resource $blob)
*/
PHP_FUNCTION(git_blob_rawcontent)
{
	zval *blob;
	php_git2_t *git2;
	const char *buffer = NULL;
	git_off_t size;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	buffer = git_blob_rawcontent(PHP_GIT2_V(git2, blob));
	if (buffer == NULL) {
		RETURN_FALSE;
	}
	size = git_blob_rawsize(PHP_GIT2_V(git2, blob));
	RETURN_STRINGL(buffer, size, 1);
}
/* }}} */

/* {{{ proto resource git_blob_rawsize(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_rawsize)
{
	zval *blob;
	php_git2_t *git2;
	git_off_t size;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	size = git_blob_rawsize(PHP_GIT2_V(git2, blob));
	RETURN_LONG(size);
}
/* }}} */