#include "php_git2.h"
#include "php_git2_priv.h"
#include "reset.h"

/* {{{ proto long git_reset(resource $repo, resource $target,  $reset_type)
 */
PHP_FUNCTION(git_reset)
{
	int result = 0, error = 0;
	zval *repo = NULL, *target = NULL;
	php_git2_t *_repo = NULL, *_target = NULL;
	long reset_type = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrl", &repo, &target, &reset_type) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_target, php_git2_t*, &target, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reset(PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_target, object), reset_type);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reset_default(resource $repo, resource $target, array $pathspecs)
 */
PHP_FUNCTION(git_reset_default)
{
	int result = 0, error = 0;
	zval *repo = NULL, *target = NULL, *pathspecs = NULL;
	php_git2_t *_repo = NULL, *_target = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &target, &pathspecs) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_target, php_git2_t*, &target, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reset_default(PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_target, object), pathspecs);
	RETURN_LONG(result);
}
/* }}} */

