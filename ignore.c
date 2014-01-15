#include "php_git2.h"
#include "php_git2_priv.h"
#include "ignore.h"

/* {{{ proto long git_ignore_add_rule(resource $repo, string $rules)
 */
PHP_FUNCTION(git_ignore_add_rule)
{
	int result = 0, rules_len = 0, error = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *rules = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &rules, &rules_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_ignore_add_rule(PHP_GIT2_V(_repo, repository), rules);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_ignore_clear_internal_rules(resource $repo)
 */
PHP_FUNCTION(git_ignore_clear_internal_rules)
{
	int result = 0, error = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_ignore_clear_internal_rules(PHP_GIT2_V(_repo, repository));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_ignore_path_is_ignored(long $ignored, resource $repo, string $path)
 */
PHP_FUNCTION(git_ignore_path_is_ignored)
{
	int result = 0, path_len = 0, error = 0;
	long ignored = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *path = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &ignored, &repo, &path, &path_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_ignore_path_is_ignored(ignored, PHP_GIT2_V(_repo, repository), path);
	RETURN_BOOL(result);
}
/* }}} */

