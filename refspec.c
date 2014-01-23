#include "php_git2.h"
#include "php_git2_priv.h"
#include "refspec.h"

/* {{{ proto string git_refspec_src(resource $refspec)
 */
PHP_FUNCTION(git_refspec_src)
{
	const char  *result = NULL;
	zval *refspec = NULL;
	php_git2_t *_refspec = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &refspec) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_refspec, php_git2_t*, &refspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_src(PHP_GIT2_V(_refspec, refspec));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_refspec_dst(resource $refspec)
 */
PHP_FUNCTION(git_refspec_dst)
{
	const char  *result = NULL;
	zval *refspec = NULL;
	php_git2_t *_refspec = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &refspec) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_refspec, php_git2_t*, &refspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_dst(PHP_GIT2_V(_refspec, refspec));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto string git_refspec_string(resource $refspec)
 */
PHP_FUNCTION(git_refspec_string)
{
	const char  *result = NULL;
	zval *refspec = NULL;
	php_git2_t *_refspec = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &refspec) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_refspec, php_git2_t*, &refspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_string(PHP_GIT2_V(_refspec, refspec));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto long git_refspec_force(resource $refspec)
 */
PHP_FUNCTION(git_refspec_force)
{
	int result = 0;
	zval *refspec = NULL;
	php_git2_t *_refspec = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &refspec) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_refspec, php_git2_t*, &refspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_force(PHP_GIT2_V(_refspec, refspec));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_refspec_direction(resource $spec)
 */
PHP_FUNCTION(git_refspec_direction)
{
	git_direction *result = NULL;
	zval *spec = NULL;
	php_git2_t *_spec = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &spec) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_spec, php_git2_t*, &spec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_direction(PHP_GIT2_V(_spec, refspec));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_refspec_src_matches(resource $refspec, string $refname)
 */
PHP_FUNCTION(git_refspec_src_matches)
{
	int result = 0, refname_len = 0;
	zval *refspec = NULL;
	php_git2_t *_refspec = NULL;
	char *refname = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &refspec, &refname, &refname_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_refspec, php_git2_t*, &refspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_src_matches(PHP_GIT2_V(_refspec, refspec), refname);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_refspec_dst_matches(resource $refspec, string $refname)
 */
PHP_FUNCTION(git_refspec_dst_matches)
{
	int result = 0, refname_len = 0;
	zval *refspec = NULL;
	php_git2_t *_refspec = NULL;
	char *refname = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &refspec, &refname, &refname_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_refspec, php_git2_t*, &refspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_refspec_dst_matches(PHP_GIT2_V(_refspec, refspec), refname);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto string git_refspec_transform(long $outlen, resource $spec, string $name)
 */
PHP_FUNCTION(git_refspec_transform)
{
	// TODO(chobie): fix this implementation
	php_git2_t *_spec = NULL;
	char out = NULL, *name = NULL;
	long outlen = 0;
	zval *spec = NULL;
	int name_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &outlen, &spec, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_spec, php_git2_t*, &spec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_refspec_transform(&out, outlen, PHP_GIT2_V(_spec, refspec), name);
	if (php_git2_check_error(error, "git_refspec_transform" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto string git_refspec_rtransform(long $outlen, resource $spec, string $name)
 */
PHP_FUNCTION(git_refspec_rtransform)
{
	// TODO(chobie): fix this implementation
	php_git2_t *_spec = NULL;
	char out = NULL, *name = NULL;
	long outlen = 0;
	zval *spec = NULL;
	int name_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &outlen, &spec, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_spec, php_git2_t*, &spec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_refspec_rtransform(&out, outlen, PHP_GIT2_V(_spec, refspec), name);
	if (php_git2_check_error(error, "git_refspec_rtransform" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(out, 1);
}
/* }}} */

