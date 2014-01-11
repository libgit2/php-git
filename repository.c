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

/* {{{ proto resource git_repository_wrap_odb(odb)
*/
PHP_FUNCTION(git_repository_wrap_odb)
{
	zval *odb;
	php_git2_t *_odb;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_wrap_odb not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &odb) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_odb, php_git2_t*, &odb, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_discover(path_size, start_path, across_fs, ceiling_dirs)
*/
PHP_FUNCTION(git_repository_discover)
{
	char *start_path = {0};
	int start_path_len;
	long across_fs;
	char *ceiling_dirs = {0};
	int ceiling_dirs_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_discover not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"sls", &path_size, &start_path, &start_path_len, &across_fs, &ceiling_dirs, &ceiling_dirs_len) == FAILURE) {
//		return;
//	}
}

/* {{{ proto resource git_repository_open_ext(path, flags, ceiling_dirs)
*/
PHP_FUNCTION(git_repository_open_ext)
{
	char *path = {0};
	int path_len;
	long flags;
	char *ceiling_dirs = {0};
	int ceiling_dirs_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_open_ext not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sls", &path, &path_len, &flags, &ceiling_dirs, &ceiling_dirs_len) == FAILURE) {
		return;
	}
}

/* {{{ proto void git_repository_free(repo)
*/
PHP_FUNCTION(git_repository_free)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_init_ext(repo_path, opts)
*/
PHP_FUNCTION(git_repository_init_ext)
{
	char *repo_path = {0};
	int repo_path_len;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_init_ext not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"sr", &repo_path, &repo_path_len, &opts) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_repo_path, php_git2_t*, &repo_path, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_head(repo)
*/
PHP_FUNCTION(git_repository_head)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_head not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_head_detached(repo)
*/
PHP_FUNCTION(git_repository_head_detached)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_head_detached not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_head_unborn(repo)
*/
PHP_FUNCTION(git_repository_head_unborn)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_head_unborn not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_is_empty(repo)
*/
PHP_FUNCTION(git_repository_is_empty)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_is_empty not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_path(repo)
*/
PHP_FUNCTION(git_repository_path)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_path not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_set_workdir(repo, workdir, update_gitlink)
*/
PHP_FUNCTION(git_repository_set_workdir)
{
	zval *repo;
	php_git2_t *_repo;
	char *workdir = {0};
	int workdir_len;
	long update_gitlink;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_set_workdir not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &workdir, &workdir_len, &update_gitlink) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_is_bare(repo)
*/
PHP_FUNCTION(git_repository_is_bare)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_is_bare not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_config(repo)
*/
PHP_FUNCTION(git_repository_config)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_config not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_odb(repo)
*/
PHP_FUNCTION(git_repository_odb)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_odb not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_refdb(repo)
*/
PHP_FUNCTION(git_repository_refdb)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_refdb not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_index(repo)
*/
PHP_FUNCTION(git_repository_index)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_index not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_message(len, repo)
*/
PHP_FUNCTION(git_repository_message)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_message not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_message_remove(repo)
*/
PHP_FUNCTION(git_repository_message_remove)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_message_remove not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_merge_cleanup(repo)
*/
PHP_FUNCTION(git_repository_merge_cleanup)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_merge_cleanup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_fetchhead_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_repository_fetchhead_foreach)
{
	zval *repo;
	php_git2_t *_repo;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_fetchhead_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &repo, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_mergehead_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_repository_mergehead_foreach)
{
	zval *repo;
	php_git2_t *_repo;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_mergehead_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &repo, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_repository_hashfile(repo, path, type, as_path)
*/
PHP_FUNCTION(git_repository_hashfile)
{
	zval *repo;
	php_git2_t *_repo;
	char *path = {0};
	int path_len;
	zval *type;
	php_git2_t *_type;
	char *as_path = {0};
	int as_path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_hashfile not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrs", &repo, &path, &path_len, &type, &as_path, &as_path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_set_head(repo, refname)
*/
PHP_FUNCTION(git_repository_set_head)
{
	zval *repo;
	php_git2_t *_repo;
	char *refname = {0};
	int refname_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_set_head not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &refname, &refname_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_set_head_detached(repo, commitish)
*/
PHP_FUNCTION(git_repository_set_head_detached)
{
	zval *repo;
	php_git2_t *_repo;
	char *commitish = {0};
	int commitish_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_set_head_detached not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &commitish, &commitish_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_detach_head(repo)
*/
PHP_FUNCTION(git_repository_detach_head)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_detach_head not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_state(repo)
*/
PHP_FUNCTION(git_repository_state)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_state not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_set_namespace(repo, nmspace)
*/
PHP_FUNCTION(git_repository_set_namespace)
{
	zval *repo;
	php_git2_t *_repo;
	char *nmspace = {0};
	int nmspace_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_set_namespace not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &nmspace, &nmspace_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_repository_is_shallow(repo)
*/
PHP_FUNCTION(git_repository_is_shallow)
{
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_repository_is_shallow not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}