#include "php_git2.h"
#include "php_git2_priv.h"
#include "checkout.h"

/* {{{ proto long git_checkout_head(resource $repo,  $opts)
 */
PHP_FUNCTION(git_checkout_head)
{
	int result = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *opts = NULL;
	int error = 0;

	/* TODO(chobie): generate converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &repo, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_checkout_head(PHP_GIT2_V(_repo, repository), opts);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_checkout_index(resource $repo, resource $index,  $opts)
 */
PHP_FUNCTION(git_checkout_index)
{
	int result = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *index = NULL;
	php_git2_t *_index = NULL;
	zval *opts = NULL;
	int error = 0;

	/* TODO(chobie): generate converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &index, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_checkout_index(PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_index, index), opts);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_checkout_tree(resource $repo, resource $treeish,  $opts)
 */
PHP_FUNCTION(git_checkout_tree)
{
	int result = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *treeish = NULL;
	php_git2_t *_treeish = NULL;
	zval *opts = NULL;
	int error = 0;

	/* TODO(chobie): generate converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rra", &repo, &treeish, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_treeish, php_git2_t*, &treeish, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_checkout_tree(PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_treeish, object), opts);
	RETURN_LONG(result);
}
/* }}} */

