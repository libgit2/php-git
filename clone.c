#include "php_git2.h"
#include "php_git2_priv.h"
#include "clone.h"

/* {{{ proto resource git_clone(string $url, string $localpath[, array $options])
*/
PHP_FUNCTION(git_clone)
{
	char *url, *localpath;
	int url_len, localpath_len;
	zval *options;// = GIT_OPTIONS_INIT;
	php_git2_t *git2;
	git_repository *repository;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss|a", &url, &url_len, &localpath, &localpath_len, &options) == FAILURE) {
		return;
	}

	/* TODO(chobie): convert options to git_clone_options */

	error = git_clone(&repository, url, localpath, NULL);
	if (php_git2_check_error(error, "git_clone" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(git2);

	PHP_GIT2_V(git2, repository) = repository;
	git2->type = PHP_GIT2_TYPE_REPOSITORY;
	git2->resource_id = PHP_GIT2_LIST_INSERT(git2, git2_resource_handle);
	git2->should_free_v = 1;

	ZVAL_RESOURCE(return_value, git2->resource_id);
}

/* {{{ proto int git_clone_into(resource $repository, resource $remote, long $co_opts, string $branch)
*/
PHP_FUNCTION(git_clone_into)
{
	/* TODO(chobie): implement this*/
}
