#include "php_git2.h"
#include "php_git2_priv.h"
#include "blame.h"

static void php_git2_array_to_git_blame_options(git_blame_options *options, zval *array TSRMLS_DC)
{
	zval *tmp;

	options->version = php_git2_read_arrval_long(array, ZEND_STRS("version") TSRMLS_CC);
	options->flags = php_git2_read_arrval_long(array, ZEND_STRS("flags") TSRMLS_CC);
	options->min_match_characters = php_git2_read_arrval_long(array, ZEND_STRS("min_match_characters") TSRMLS_CC);
	tmp = php_git2_read_arrval(array, ZEND_STRS("newest_commit") TSRMLS_CC);
	if (Z_TYPE_P(tmp) != NULL) {
		if (Z_TYPE_P(tmp) != IS_STRING) {
			convert_to_string(tmp);
		}
		if (git_oid_fromstrn(&options->newest_commit, Z_STRVAL_P(tmp), Z_STRLEN_P(tmp)) != GIT_OK) {
			return;
		}
	}

	tmp = php_git2_read_arrval(array, ZEND_STRS("oldest_commit") TSRMLS_CC);
	if (Z_TYPE_P(tmp) != NULL) {
		if (Z_TYPE_P(tmp) != IS_STRING) {
			convert_to_string(tmp);
		}
		if (git_oid_fromstrn(&options->newest_commit, Z_STRVAL_P(tmp), Z_STRLEN_P(tmp)) != GIT_OK) {
			return;
		}
	}

	options->min_line = php_git2_read_arrval_long(array, ZEND_STRS("min_line") TSRMLS_CC);
	options->max_line = php_git2_read_arrval_long(array, ZEND_STRS("max_line") TSRMLS_CC);

}

static void php_git2_git_blame_options_to_array(git_blame_options *options, zval **out TSRMLS_DC)
{
	zval *result = NULL;
	char buf[41] = {0};

	MAKE_STD_ZVAL(result);
	array_init(result);

	add_assoc_long_ex(result, ZEND_STRS("version"), options->version);
	add_assoc_long_ex(result, ZEND_STRS("flags"), options->flags);
	add_assoc_long_ex(result, ZEND_STRS("min_match_characters"), options->min_match_characters);

	if (git_oid_iszero(&options->newest_commit) != 1) {
		git_oid_fmt(buf, &options->newest_commit);
		add_assoc_string_ex(result, ZEND_STRS("newest_commit"), out, 1);
	} else {
		add_assoc_null_ex(result, ZEND_STRS("newest_commit"));
	}

	if (git_oid_iszero(&options->oldest_commit) != 1) {
		git_oid_fmt(buf, &options->oldest_commit);
		add_assoc_string_ex(result, ZEND_STRS("oldest_commit"), out, 1);
	} else {
		add_assoc_null_ex(result, ZEND_STRS("oldest_commit"));
	}

	add_assoc_long_ex(result, ZEND_STRS("min_line"), options->min_line);
	add_assoc_long_ex(result, ZEND_STRS("max_line"), options->max_line);
	*out = result;
}

static void php_git2_git_blame_hunk_to_array(git_blame_hunk *hunk, zval **out TSRMLS_DC)
{
	zval *result = NULL, *final = NULL, *orig = NULL;
	char buf[41] = {0};

	MAKE_STD_ZVAL(result);
	array_init(result);

	add_assoc_long_ex(result, ZEND_STRS("lines_in_hunk"), hunk->lines_in_hunk);

	git_oid_fmt(buf, &hunk->final_commit_id);
	add_assoc_string_ex(result, ZEND_STRS("final_commit_id"), buf, 1);

	php_git2_signature_to_array(hunk->final_signature, &final TSRMLS_CC);
	add_assoc_zval_ex(result, ZEND_STRS("final_signature"), final);

	add_assoc_long_ex(result, ZEND_STRS("final_start_line_number"), hunk->final_start_line_number);

	git_oid_fmt(buf, &hunk->orig_commit_id);
	add_assoc_string_ex(result, ZEND_STRS("orig_commit_id"), buf, 1);
	add_assoc_string_ex(result, ZEND_STRS("orig_path"), hunk->orig_path, 1);

	add_assoc_long_ex(result, ZEND_STRS("orig_start_line_number"), hunk->orig_start_line_number);
	if (hunk->orig_signature) {
		php_git2_signature_to_array(hunk->orig_signature, &orig TSRMLS_CC);
	} else {
		MAKE_STD_ZVAL(orig);
		ZVAL_NULL(orig);
	}
	add_assoc_zval_ex(result, ZEND_STRS("orig_signature"), orig);

	add_assoc_stringl_ex(result, ZEND_STRS("boundary"), &hunk->boundary, 1, 1);

	*out = result;
}

/* {{{ proto long git_blame_get_hunk_count(resource $blame)
 */
PHP_FUNCTION(git_blame_get_hunk_count)
{
	uint32_t result = 0;
	zval *blame = NULL;
	php_git2_t *_blame = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blame) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_blame, php_git2_t*, &blame, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_blame_get_hunk_count(PHP_GIT2_V(_blame, blame));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_blame_get_hunk_byindex(resource $blame, long $index)
 */
PHP_FUNCTION(git_blame_get_hunk_byindex)
{
	const git_blame_hunk *result = NULL;
	zval *blame = NULL, *array = NULL;
	php_git2_t *_blame = NULL;
	long index = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &blame, &index) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_blame, php_git2_t*, &blame, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_blame_get_hunk_byindex(PHP_GIT2_V(_blame, blame), index);
	if (result == NULL) {
		RETURN_FALSE;
	}
	php_git2_git_blame_hunk_to_array(result, &array TSRMLS_CC);
	RETURN_ZVAL(array, 0, 1);
}
/* }}} */

/* {{{ proto resource git_blame_get_hunk_byline(resource $blame, long $lineno)
 */
PHP_FUNCTION(git_blame_get_hunk_byline)
{
	const git_blame_hunk *result = NULL;
	zval *blame = NULL, *array = NULL;
	php_git2_t *_blame = NULL;
	long lineno = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &blame, &lineno) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_blame, php_git2_t*, &blame, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_blame_get_hunk_byline(PHP_GIT2_V(_blame, blame), lineno);
	if (result == NULL) {
		RETURN_FALSE;
	}
	php_git2_git_blame_hunk_to_array(result, &array TSRMLS_CC);
	RETURN_ZVAL(array, 0, 1);
}
/* }}} */

/* {{{ proto resource git_blame_file(resource $repo, string $path,  $options)
 */
PHP_FUNCTION(git_blame_file)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_blame *out = NULL;
	zval *repo = NULL, *options = NULL;
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;
	char *path = NULL;
	int path_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsa", &repo, &path, &path_len, &options) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_git_blame_options(&opts, options TSRMLS_CC);
	error = git_blame_file(&out, PHP_GIT2_V(_repo, repository), path, &opts);
	if (php_git2_check_error(error, "git_blame_file" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BLAME, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_blame_buffer(resource $reference, string $buffer)
 */
PHP_FUNCTION(git_blame_buffer)
{
	php_git2_t *result = NULL, *_reference = NULL;
	git_blame *out = NULL;
	zval *reference = NULL;
	char *buffer = NULL;
	int buffer_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &reference, &buffer, &buffer_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reference, php_git2_t*, &reference, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_blame_buffer(&out, PHP_GIT2_V(_reference, blame), buffer, buffer_len);
	if (php_git2_check_error(error, "git_blame_buffer" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BLAME, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto void git_blame_free(resource $blame)
 */
PHP_FUNCTION(git_blame_free)
{
	zval *blame = NULL;
	php_git2_t *_blame = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &blame) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_blame, php_git2_t*, &blame, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_blame)) {
		git_blame_free(PHP_GIT2_V(_blame, blame));
		GIT2_SHOULD_FREE(_blame) = 0;
	};
	zval_ptr_dtor(&blame);
}
/* }}} */

/* {{{ proto void git_blame_options_new()
 */
PHP_FUNCTION(git_blame_options_new)
{
	zval *result;
	git_blame_options options = GIT_BLAME_OPTIONS_INIT;

	php_git2_git_blame_options_to_array(&options, &result TSRMLS_CC);
	RETURN_ZVAL(result, 0, 1);
}
/* }}} */
