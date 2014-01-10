#include "php_git2.h"
#include "php_git2_priv.h"
#include "repository.h"

/* {{{ proto resource git_repository_new()
*/
PHP_FUNCTION(git_repository_new)
{
//	git_repository *repository;
//	int error;
//	php_git2_t *git2;
//
//	error = git_repository_new(&repository);
//	if (php_git2_check_error(error, "git_repository_new" TSRMLS_CC)) {
//		RETURN_FALSE
//	}
//
//	PHP_GIT2_MAKE_RESOURCE(git2);
//
//	git2->type = PHP_GIT2_TYPE_REPOSITORY;
//	git2->resource_id = PHP_GIT2_LIST_INSERT(git2, git2_resource_handle);
//	git2->should_free_v = 0;
//
//	ZVAL_RESOURCE(return_value, git2->resource_id);
}

/* {{{ proto resource git_repository_init(string $path, long is_bare = 0)
*/
PHP_FUNCTION(git_repository_init)
{
	git_repository *repository;
	int error;
	php_git2_t *git2;
	char *path;
	int path_len, is_bare = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s|l", &path, &path_len, &is_bare) == FAILURE) {
		return;
	}

	error = git_repository_init(&repository, path, is_bare);
	if (php_git2_check_error(error, "git_repository_init" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(git2);
	PHP_GIT2_V(git2, repository) = repository;
	git2->type = PHP_GIT2_TYPE_REPOSITORY;
	git2->resource_id = PHP_GIT2_LIST_INSERT(git2, git2_resource_handle);
	git2->should_free_v = 1;

	ZVAL_RESOURCE(return_value, git2->resource_id);
}

/* {{{ proto resource git_repository_open(string $path)
*/
PHP_FUNCTION(git_repository_open_bare)
{
	char *path;
	int path_len;
	git_repository *repository;
	int error = 0;
	php_git2_t *git2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}

	error = git_repository_open_bare(&repository, path);
	if (php_git2_check_error(error, "git_repository_open_bare" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(git2);
	PHP_GIT2_V(git2, repository) = repository;
	git2->type = PHP_GIT2_TYPE_REPOSITORY;
	git2->resource_id = PHP_GIT2_LIST_INSERT(git2, git2_resource_handle);
	git2->should_free_v = 1;

	ZVAL_RESOURCE(return_value, git2->resource_id);
}

/* {{{ proto resource git_repository_open(string $path)
*/
PHP_FUNCTION(git_repository_open)
{
	char *path;
	int path_len;
	git_repository *repository;
	int error = 0;
	php_git2_t *git2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}

	PHP_GIT2_MAKE_RESOURCE(git2);
	error = git_repository_open(&repository, path);
	if (php_git2_check_error(error, "git_repository_open" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_V(git2, repository) = repository;
	git2->type = PHP_GIT2_TYPE_REPOSITORY;
	git2->resource_id = PHP_GIT2_LIST_INSERT(git2, git2_resource_handle);
	git2->should_free_v = 1;

	ZVAL_RESOURCE(return_value, git2->resource_id);
}
/* }}} */

/* {{{ proto string git_repository_get_namespace(resource $repository)
*/
PHP_FUNCTION(git_repository_get_namespace)
{
	zval *repository;
	php_git2_t *git2;
	const char *ns;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repository) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ns = git_repository_get_namespace(PHP_GIT2_V(git2, repository));
	if (ns != NULL) {
		RETURN_STRING(ns, 1);
	} else {
		RETURN_STRING("", 1);
	}
}
/* }}} */

/* {{{ proto string git_repository_workdir(resource $repository)
*/
PHP_FUNCTION(git_repository_workdir)
{
	zval *repository;
	php_git2_t *git2;
	const char *workdir;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repository) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	workdir = git_repository_workdir(PHP_GIT2_V(git2, repository));

	if (workdir != NULL) {
		RETURN_STRING(workdir, 1);
	} else {
		RETURN_STRING("", 1);
	}
}
/* }}} */