#include "php_git2.h"
#include "php_git2_priv.h"
#include "repository.h"

/* {{{ proto resource git_repository_new()
*/
PHP_FUNCTION(git_repository_new)
{
	git_repository *repository;
	int error;
	php_git2_t *git2;

	error = git_repository_new(&repository);
	if (php_git2_check_error(error, "git_repository_new" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(git2);

	git2->type = PHP_GIT2_TYPE_REPOSITORY;
	git2->resource_id = PHP_GIT2_LIST_INSERT(git2, git2_resource_handle);
	git2->should_free_v = 0;

	ZVAL_RESOURCE(return_value, git2->resource_id);
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

/* {{{ proto resource git_repository_discover(start_path, across_fs, ceiling_dirs)
*/
PHP_FUNCTION(git_repository_discover)
{
	char *start_path = {0};
	int start_path_len;
	long across_fs;
	char *ceiling_dirs = {0};
	int ceiling_dirs_len;
	int error = 0;
	char buffer[512];
	size_t buffer_len = 512;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sls", &start_path, &start_path_len, &across_fs, &ceiling_dirs, &ceiling_dirs_len) == FAILURE) {
		return;
	}

	error = git_repository_discover(buffer, buffer_len, start_path, across_fs, ceiling_dirs);
	if (php_git2_check_error(error, "git_repository_discover" TSRMLS_CC)) {
		RETURN_FALSE
	}

	RETURN_STRING(buffer, 1);
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
	int error = 0;
	git_repository *repository;
	php_git2_t *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sls", &path, &path_len, &flags, &ceiling_dirs, &ceiling_dirs_len) == FAILURE) {
		return;
	}
	error = git_repository_open_ext(&repository, path, flags, ceiling_dirs);
	if (php_git2_check_error(error, "git_repository_open_ext" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto void git_repository_free(repo)
*/
PHP_FUNCTION(git_repository_free)
{
	zval *repo;
	php_git2_t *_repo;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_repo->should_free_v) {
		git_repository_free(PHP_GIT2_V(_repo, repository));
		_repo->should_free_v = 0;
	}
	zval_ptr_dtor(&repo);
}

/* {{{ proto resource git_repository_init_ext(repo_path, opts)
*/
PHP_FUNCTION(git_repository_init_ext)
{
	char *repo_path = {0};
	int repo_path_len;
	zval *opts;
	php_git2_t *_opts;
// TODO
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
	php_git2_t *_repo, *result;
	git_reference *reference;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_head(&reference, PHP_GIT2_V(_repo, repository));

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = reference;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto long git_repository_head_detached(repo)
*/
PHP_FUNCTION(git_repository_head_detached)
{
	zval *repo;
	php_git2_t *_repo;
	int result = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_repository_head_detached(PHP_GIT2_V(_repo, repository));
	RETURN_BOOL(result);
}

/* {{{ proto long git_repository_head_unborn(repo)
*/
PHP_FUNCTION(git_repository_head_unborn)
{
	zval *repo;
	php_git2_t *_repo;
	int unborn = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	unborn = git_repository_head_unborn(PHP_GIT2_V(_repo, repository));
	RETURN_BOOL(unborn);
}

/* {{{ proto long git_repository_is_empty(repo)
*/
PHP_FUNCTION(git_repository_is_empty)
{
	zval *repo;
	php_git2_t *_repo;
	int empty;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	empty = git_repository_is_empty(PHP_GIT2_V(_repo, repository));
	RETURN_BOOL(empty);
}

/* {{{ proto resource git_repository_path(repo)
*/
PHP_FUNCTION(git_repository_path)
{
	zval *repo;
	php_git2_t *_repo;
	const char *path;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	path = git_repository_path(PHP_GIT2_V(_repo, repository));
	RETURN_STRING(path, 1);
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
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &workdir, &workdir_len, &update_gitlink) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_set_workdir(PHP_GIT2_V(_repo, repository), workdir, update_gitlink);
	if (php_git2_check_error(error, "git_repository_set_workdir" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_repository_is_bare(repo)
*/
PHP_FUNCTION(git_repository_is_bare)
{
	zval *repo;
	php_git2_t *_repo;
	int is_bare = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	is_bare = git_repository_is_bare(PHP_GIT2_V(_repo, repository));

	RETURN_BOOL(is_bare);
}

/* {{{ proto resource git_repository_config(repo)
*/
PHP_FUNCTION(git_repository_config)
{
	zval *repo;
	php_git2_t *_repo, *result;
	git_config *config;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_config(&config, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_repository_config" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, config) = config;
	result->type = PHP_GIT2_TYPE_CONFIG;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_repository_odb(repo)
*/
PHP_FUNCTION(git_repository_odb)
{
	zval *repo;
	php_git2_t *_repo, *result;
	git_odb *odb;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_odb(&odb, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_repository_odb" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, odb) = odb;
	result->type = PHP_GIT2_TYPE_ODB;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_repository_refdb(repo)
*/
PHP_FUNCTION(git_repository_refdb)
{
	zval *repo;
	php_git2_t *_repo, *result;
	git_refdb *refdb;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_refdb(&refdb, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_repository_refdb" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, refdb) = refdb;
	result->type = PHP_GIT2_TYPE_REFDB;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_repository_index(repo)
*/
PHP_FUNCTION(git_repository_index)
{
	zval *repo;
	php_git2_t *_repo, *result;
	git_index *index;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_index(&index, PHP_GIT2_V(_repo, repository));
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, index) = index;
	result->type = PHP_GIT2_TYPE_INDEX;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;
	
	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_repository_message(len, repo)
*/
PHP_FUNCTION(git_repository_message)
{
	zval *repo;
	php_git2_t *_repo;
	char buffer[512];
	size_t buffer_len = 512;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_message(buffer, buffer_len, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_repository_message" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_STRING(buffer, 1);
}

/* {{{ proto long git_repository_message_remove(repo)
*/
PHP_FUNCTION(git_repository_message_remove)
{
	zval *repo;
	php_git2_t *_repo;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_message_remove(PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_repository_message_remove" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
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
	git_oid oid;
	int error = 0;
	char out[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrs", &repo, &path, &path_len, &type, &as_path, &as_path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_hashfile(&out, PHP_GIT2_V(_repo, repository), path, type, as_path);
	if (php_git2_check_error(error, "git_repository_hashfile" TSRMLS_CC)) {
		RETURN_FALSE
	}
	git_oid_fmt(out, &oid);

}

/* {{{ proto long git_repository_set_head(repo, refname)
*/
PHP_FUNCTION(git_repository_set_head)
{
	zval *repo;
	php_git2_t *_repo;
	char *refname = {0};
	int refname_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &refname, &refname_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_set_head(PHP_GIT2_V(_repo, repository), refname);
	if (php_git2_check_error(error, "git_repository_set_head" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_repository_set_head_detached(repo, commitish)
*/
PHP_FUNCTION(git_repository_set_head_detached)
{
	zval *repo;
	php_git2_t *_repo;
	char *commitish = {0};
	int commitish_len;
	int error = 0;
	git_oid id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &commitish, &commitish_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&id, commitish, commitish_len) != GIT_OK) {
		return;
	}

	error = git_repository_set_head_detached(PHP_GIT2_V(_repo, repository), &id);
	if (php_git2_check_error(error, "git_repository_set_head_detached" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_repository_detach_head(repo)
*/
PHP_FUNCTION(git_repository_detach_head)
{
	zval *repo;
	php_git2_t *_repo;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_detach_head(PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_repository_detach_head" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_repository_state(repo)
*/
PHP_FUNCTION(git_repository_state)
{
	zval *repo;
	php_git2_t *_repo;
	int state = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	state = git_repository_state(PHP_GIT2_V(_repo, repository));

	RETURN_LONG(state);
}

/* {{{ proto long git_repository_set_namespace(repo, nmspace)
*/
PHP_FUNCTION(git_repository_set_namespace)
{
	zval *repo;
	php_git2_t *_repo;
	char *nmspace = {0};
	int nmspace_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &nmspace, &nmspace_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_repository_set_namespace(PHP_GIT2_V(_repo, repository), nmspace);
	if (php_git2_check_error(error, "git_repository_set_namespace" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_repository_is_shallow(repo)
*/
PHP_FUNCTION(git_repository_is_shallow)
{
	zval *repo;
	php_git2_t *_repo;
	int is_shallow;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	is_shallow = git_repository_is_shallow(PHP_GIT2_V(_repo, repository));
	RETURN_LONG(is_shallow);
}