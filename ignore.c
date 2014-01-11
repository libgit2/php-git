#include "php_git2.h"
#include "php_git2_priv.h"
#include "ignore.h"

/* {{{ proto long git_ignore_add_rule(repo, rules)
*/
PHP_FUNCTION(git_ignore_add_rule)
{
	zval *repo;
	php_git2_t *_repo;
	char *rules = {0};
	int rules_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_ignore_add_rule not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &rules, &rules_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_ignore_clear_internal_rules(repo)
*/
PHP_FUNCTION(git_ignore_clear_internal_rules)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_ignore_clear_internal_rules not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_ignore_path_is_ignored(ignored, repo, path)
*/
PHP_FUNCTION(git_ignore_path_is_ignored)
{
	long ignored;
	zval *repo;
	php_git2_t *_repo;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_ignore_path_is_ignored not implemented yet");
	return;
//
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"lrs", &ignored, &repo, &path, &path_len) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_ignored, php_git2_t*, &ignored, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

