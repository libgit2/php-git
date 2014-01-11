#include "php_git2.h"
#include "php_git2_priv.h"
#include "pathspec.h"

/* {{{ proto resource git_pathspec_new(pathspec)
*/
PHP_FUNCTION(git_pathspec_new)
{
	zval *pathspec;
	php_git2_t *_pathspec;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &pathspec) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_pathspec, php_git2_t*, &pathspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_pathspec_free(ps)
*/
PHP_FUNCTION(git_pathspec_free)
{
	zval *ps;
	php_git2_t *_ps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_pathspec_matches_path(ps, flags, path)
*/
PHP_FUNCTION(git_pathspec_matches_path)
{
	zval *ps;
	php_git2_t *_ps;
	long flags;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_matches_path not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rls", &ps, &flags, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ps, php_git2_t*, &ps, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_workdir(repo, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_workdir)
{
	zval *repo;
	php_git2_t *_repo;
	long flags;
	zval *ps;
	php_git2_t *_ps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_workdir not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &repo, &flags, &ps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_index(index, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_index)
{
	zval *index;
	php_git2_t *_index;
	long flags;
	zval *ps;
	php_git2_t *_ps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_index not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &index, &flags, &ps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_tree(tree, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_tree)
{
	zval *tree;
	php_git2_t *_tree;
	long flags;
	zval *ps;
	php_git2_t *_ps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_tree not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &tree, &flags, &ps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tree, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_diff(diff, flags, ps)
*/
PHP_FUNCTION(git_pathspec_match_diff)
{
	zval *diff;
	php_git2_t *_diff;
	long flags;
	zval *ps;
	php_git2_t *_ps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_diff not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlr", &diff, &flags, &ps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_diff, php_git2_t*, &diff, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_pathspec_match_list_free(m)
*/
PHP_FUNCTION(git_pathspec_match_list_free)
{
	zval *m;
	php_git2_t *_m;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_list_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &m) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_list_entrycount(m)
*/
PHP_FUNCTION(git_pathspec_match_list_entrycount)
{
	zval *m;
	php_git2_t *_m;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_list_entrycount not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &m) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_list_entry(m, pos)
*/
PHP_FUNCTION(git_pathspec_match_list_entry)
{
	zval *m;
	php_git2_t *_m;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_list_entry not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &m, &pos) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_list_diff_entry(m, pos)
*/
PHP_FUNCTION(git_pathspec_match_list_diff_entry)
{
	zval *m;
	php_git2_t *_m;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_list_diff_entry not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &m, &pos) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_list_failed_entrycount(m)
*/
PHP_FUNCTION(git_pathspec_match_list_failed_entrycount)
{
	zval *m;
	php_git2_t *_m;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_list_failed_entrycount not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &m) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_pathspec_match_list_failed_entry(m, pos)
*/
PHP_FUNCTION(git_pathspec_match_list_failed_entry)
{
	zval *m;
	php_git2_t *_m;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_pathspec_match_list_failed_entry not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &m, &pos) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_m, php_git2_t*, &m, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

