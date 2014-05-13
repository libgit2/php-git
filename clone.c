#include "php_git2.h"
#include "php_git2_priv.h"
#include "clone.h"

static void php_git2_git_clone_options_to_array(git_clone_options *options, zval **out TSRMLS_DC)
{
    zval *result, *pathspec;

    MAKE_STD_ZVAL(result);
    array_init(result);

    add_assoc_long_ex(result, ZEND_STRS("version"), options->version);
    add_assoc_long_ex(result, ZEND_STRS("bare"), options->bare);
    add_assoc_long_ex(result, ZEND_STRS("ignore_cert_errors"), options->ignore_cert_errors);
    /* TODO: make other options available */ 
    *out = result;
}

static void php_git2_array_to_git_clone_options(git_clone_options *options, zval *array TSRMLS_DC)
{
    options->version = php_git2_read_arrval_long2(array, ZEND_STRS("version"), 1 TSRMLS_CC);
    options->bare = php_git2_read_arrval_long2(array, ZEND_STRS("bare"), 0 TSRMLS_CC);
    options->ignore_cert_errors = php_git2_read_arrval_long2(array, ZEND_STRS("ignore_cert_errors"), 0 TSRMLS_CC);
}

/* {{{ proto resource git_clone(string $url, string $localpath[, array $options])
*/
PHP_FUNCTION(git_clone)
{
	char *url, *localpath;
	int url_len, localpath_len;
	zval *opts = NULL;// = GIT_OPTIONS_INIT;
	php_git2_t *git2;
	git_repository *repository;
	int error;
	git_clone_options options = GIT_CLONE_OPTIONS_INIT;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss|a", &url, &url_len, &localpath, &localpath_len, &opts) == FAILURE) {
		return;
	}

	/* TODO(chobie): convert options to git_clone_options */

    php_git2_array_to_git_clone_options(&options, opts TSRMLS_CC);
    

	error = git_clone(&repository, url, localpath, &options);
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
