#include "php_git2.h"
#include "php_git2_priv.h"
#include "checkout.h"
/* {{{ proto long git_checkout_head(repo, opts)
*/
PHP_FUNCTION(git_checkout_head)
{
	zval *repo;
	php_git2_t *_repo;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_checkout_head not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_checkout_index(repo, index, opts)
*/
PHP_FUNCTION(git_checkout_index)
{
	zval *repo;
	php_git2_t *_repo;
	zval *index;
	php_git2_t *_index;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_checkout_index not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrr", &repo, &index, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_checkout_tree(repo, treeish, opts)
*/
PHP_FUNCTION(git_checkout_tree)
{
	zval *repo;
	php_git2_t *_repo;
	zval *treeish;
	php_git2_t *_treeish;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_checkout_tree not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrr", &repo, &treeish, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

