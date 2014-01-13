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
	int error = 0, shoud_free = 0;
	git_checkout_opts *options;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r|a", &repo, &opts) == FAILURE) {
		return;
	}

	if (opts != NULL) {
		if (php_git2_array_to_git_checkout_opts(&options, opts TSRMLS_CC)) {
			RETURN_FALSE;
		}
		shoud_free = 1;
	} else {
		//memset(&options, '\0', sizeof(git_checkout_opts));
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_checkout_head(PHP_GIT2_V(_repo, repository), options);
	if (shoud_free) {
		php_git_git_checkout_opts_free(options TSRMLS_CC);
	}
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
	git_checkout_opts options = GIT_CHECKOUT_OPTS_INIT;
	git_object *__treeish = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r|ra", &repo, &treeish, &opts) == FAILURE) {
		return;
	}

	if (opts != NULL && php_git2_array_to_git_checkout_opts(&options, opts TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		memset(&options, '\0', sizeof(git_checkout_opts));
	}

	if (treeish != NULL) {
		ZEND_FETCH_RESOURCE(_treeish, php_git2_t*, &treeish, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
		treeish = PHP_GIT2_V(_treeish, object);
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_checkout_tree(PHP_GIT2_V(_repo, repository), __treeish, &options);
	RETURN_LONG(result);
}
/* }}} */

