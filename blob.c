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

/* {{{ proto resource git_blob_create_fromchunks(resource $repository, string $hintpath, Callable $callback, mixed payload)
*/
PHP_FUNCTION(git_blob_create_fromchunks)
{
}

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

/* {{{ proto resource git_blob_filtered_content($blob, $as_path, $check_for_binary_data)
*/
PHP_FUNCTION(git_blob_filtered_content)
{
}

/* {{{ proto resource git_blob_free(resource $blob)
*/
PHP_FUNCTION(git_blob_free)
{
	zval *blob;
	php_git2_t *git2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git2->should_free_v) {
		git_blob_free(PHP_GIT2_V(git2, blob));
		git2->should_free_v = 0;
	}
	zval_ptr_dtor(&blob);
}

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

/* {{{ proto resource git_blob_lookup(resource $repository, string $oid)
*/
PHP_FUNCTION(git_blob_lookup)
{
	zval *repository;
	php_git2_t *git2, *result;
	git_blob *blob;
	char *hash;
	int hash_len;
	int error;
	git_oid id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repository, &hash, &hash_len) == FAILURE) {
		return;
	}

	if (git_oid_fromstrn(&id, hash, hash_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_blob_lookup(&blob, PHP_GIT2_V(git2, repository), &id);
	if (php_git2_check_error(error, "git_blob_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, blob) = blob;
	result->type = PHP_GIT2_TYPE_BLOB;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_blob_lookup_prefix(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_lookup_prefix)
{
}

/* {{{ proto resource git_blob_owner(resource $blob, string $oid)
*/
PHP_FUNCTION(git_blob_owner)
{
	zval *blob;
	php_git2_t *git2, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blob) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &blob, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	PHP_GIT2_MAKE_RESOURCE(result);
	repository = git_blob_owner(PHP_GIT2_V(git2, blob));

	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

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