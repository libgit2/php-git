#include "php_git2.h"
#include "php_git2_priv.h"
#include "revwalk.h"

/* {{{ proto resource git_revwalk_new(repo)
*/
PHP_FUNCTION(git_revwalk_new)
{
	zval *repo;
	php_git2_t *_repo, *result;
	git_revwalk *walker;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_new(&walker, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_revwalk_new" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, revwalk) = walker;
	result->type = PHP_GIT2_TYPE_REVWALK;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto void git_revwalk_reset(walker)
*/
PHP_FUNCTION(git_revwalk_reset)
{
	zval *walker;
	php_git2_t *_walker;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walker) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walker, php_git2_t*, &walker, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	git_revwalk_reset(PHP_GIT2_V(_walker, revwalk));
}

/* {{{ proto long git_revwalk_push(walk, id)
*/
PHP_FUNCTION(git_revwalk_push)
{
	zval *walk;
	php_git2_t *_walk;
	char *id = {0};
	int id_len;
	git_oid oid;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &id, &id_len) == FAILURE) {
		return;
	}

	if (git_oid_fromstrn(&oid, id, id_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_push(PHP_GIT2_V(_walk, revwalk), &oid);

	if (php_git2_check_error(error, "git_revwalk_push" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}

/* {{{ proto long git_revwalk_push_glob(walk, glob)
*/
PHP_FUNCTION(git_revwalk_push_glob)
{
	zval *walk;
	php_git2_t *_walk;
	char *glob = {0};
	int glob_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revwalk_push_glob not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &glob, &glob_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_revwalk_push_head(walk)
*/
PHP_FUNCTION(git_revwalk_push_head)
{
	zval *walk;
	php_git2_t *_walk;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_revwalk_push_head(PHP_GIT2_V(_walk, revwalk));
	if (php_git2_check_error(error, "git_revwalk_push_head" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}

/* {{{ proto long git_revwalk_hide(walk, commit_id)
*/
PHP_FUNCTION(git_revwalk_hide)
{
	zval *walk;
	php_git2_t *_walk;
	char *commit_id = {0};
	int commit_id_len;
	git_oid oid;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &commit_id, &commit_id_len) == FAILURE) {
		return;
	}
	if (git_oid_fromstrn(&oid, commit_id, commit_id_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_hide(PHP_GIT2_V(_walk, revwalk), &oid);

	if (php_git2_check_error(error, "git_revwalk_hide" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}

}

/* {{{ proto long git_revwalk_hide_glob(walk, glob)
*/
PHP_FUNCTION(git_revwalk_hide_glob)
{
	zval *walk;
	php_git2_t *_walk;
	char *glob = {0};
	int glob_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revwalk_hide_glob not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &glob, &glob_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_revwalk_hide_head(walk)
*/
PHP_FUNCTION(git_revwalk_hide_head)
{
	zval *walk;
	php_git2_t *_walk;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_revwalk_hide_head(PHP_GIT2_V(_walk, revwalk));
	if (php_git2_check_error(error, "git_revwalk_hide_head" TSRMLS_CC)) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}

/* {{{ proto long git_revwalk_push_ref(walk, refname)
*/
PHP_FUNCTION(git_revwalk_push_ref)
{
	zval *walk;
	php_git2_t *_walk;
	char *refname = {0};
	int refname_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revwalk_push_ref not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &refname, &refname_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_revwalk_hide_ref(walk, refname)
*/
PHP_FUNCTION(git_revwalk_hide_ref)
{
	zval *walk;
	php_git2_t *_walk;
	char *refname = {0};
	int refname_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revwalk_hide_ref not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &refname, &refname_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto string git_revwalk_next(walk)
*/
PHP_FUNCTION(git_revwalk_next)
{
	zval *walk;
	php_git2_t *_walk;
	git_oid id = {0};
	char out[41] = {0};
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revwalk_next(&id, PHP_GIT2_V(_walk, revwalk));

	if (error == GIT_ITEROVER) {
		RETURN_FALSE;
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);
}

/* {{{ proto void git_revwalk_sorting(walk, sort_mode)
*/
PHP_FUNCTION(git_revwalk_sorting)
{
	zval *walk;
	php_git2_t *_walk;
	long sort_mode = GIT_SORT_NONE;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &walk, &sort_mode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	git_revwalk_sorting(PHP_GIT2_V(_walk, revwalk), sort_mode);
}

/* {{{ proto long git_revwalk_push_range(walk, range)
*/
PHP_FUNCTION(git_revwalk_push_range)
{
	zval *walk;
	php_git2_t *_walk;
	char *range = {0};
	int range_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revwalk_push_range not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &walk, &range, &range_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_revwalk_simplify_first_parent(walk)
*/
PHP_FUNCTION(git_revwalk_simplify_first_parent)
{
	zval *walk;
	php_git2_t *_walk;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_revwalk_simplify_first_parent(PHP_GIT2_V(_walk, revwalk));
}

/* {{{ proto void git_revwalk_free(walk)
*/
PHP_FUNCTION(git_revwalk_free)
{
	zval *walk;
	php_git2_t *_walk;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	if (_walk->should_free_v) {
		git_revwalk_free(PHP_GIT2_V(_walk, revwalk));
	}
	zval_ptr_dtor(&walk);
}

/* {{{ proto resource git_revwalk_repository(walk)
*/
PHP_FUNCTION(git_revwalk_repository)
{
	zval *walk;
	php_git2_t *_walk, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &walk) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_walk, php_git2_t*, &walk, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	repository = git_revwalk_repository(PHP_GIT2_V(_walk, revwalk));

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

