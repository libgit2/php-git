#include "php_git2.h"
#include "php_git2_priv.h"
#include "branch.h"

/* {{{ proto resource git_branch_create(repo, branch_name, target, force)
*/
PHP_FUNCTION(git_branch_create)
{
	zval *repo;
	php_git2_t *_repo;
	char *branch_name = {0};
	int branch_name_len;
	zval *target;
	php_git2_t *_target;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_create not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrl", &repo, &branch_name, &branch_name_len, &target, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_branch_delete(branch)
*/
PHP_FUNCTION(git_branch_delete)
{
	zval *branch;
	php_git2_t *_branch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_delete not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &branch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_iterator_new(repo, list_flags)
*/
PHP_FUNCTION(git_branch_iterator_new)
{
	zval *repo;
	php_git2_t *_repo;
	zval *list_flags;
	php_git2_t *_list_flags;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_iterator_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &list_flags) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_next(out_type, iter)
*/
PHP_FUNCTION(git_branch_next)
{
	zval *out_type;
	php_git2_t *_out_type;
	zval *iter;
	php_git2_t *_iter;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_next not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &out_type, &iter) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_out_type, php_git2_t*, &out_type, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_branch_iterator_free(iter)
*/
PHP_FUNCTION(git_branch_iterator_free)
{
	zval *iter;
	php_git2_t *_iter;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_iterator_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_move(branch, new_branch_name, force)
*/
PHP_FUNCTION(git_branch_move)
{
	zval *branch;
	php_git2_t *_branch;
	char *new_branch_name = {0};
	int new_branch_name_len;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_move not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &branch, &new_branch_name, &new_branch_name_len, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_lookup(repo, branch_name, branch_type)
*/
PHP_FUNCTION(git_branch_lookup)
{
	zval *repo;
	php_git2_t *_repo;
	char *branch_name = {0};
	int branch_name_len;
	zval *branch_type;
	php_git2_t *_branch_type;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_lookup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsr", &repo, &branch_name, &branch_name_len, &branch_type) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_name(ref)
*/
PHP_FUNCTION(git_branch_name)
{
	zval *ref;
	php_git2_t *_ref;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_name not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_upstream(branch)
*/
PHP_FUNCTION(git_branch_upstream)
{
	zval *branch;
	php_git2_t *_branch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_upstream not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &branch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_branch_set_upstream(branch, upstream_name)
*/
PHP_FUNCTION(git_branch_set_upstream)
{
	zval *branch;
	php_git2_t *_branch;
	char *upstream_name = {0};
	int upstream_name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_set_upstream not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &branch, &upstream_name, &upstream_name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_upstream_name(buffer_size, repo, canonical_branch_name)
*/
PHP_FUNCTION(git_branch_upstream_name)
{
	zval *repo;
	php_git2_t *_repo;
	char *canonical_branch_name = {0};
	int canonical_branch_name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_upstream_name not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rs", &buffer_size, &repo, &canonical_branch_name, &canonical_branch_name_len) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_buffer_size, php_git2_t*, &buffer_size, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_branch_is_head(branch)
*/
PHP_FUNCTION(git_branch_is_head)
{
	zval *branch;
	php_git2_t *_branch;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_is_head not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &branch) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_branch_remote_name(buffer_size, repo, canonical_branch_name)
*/
PHP_FUNCTION(git_branch_remote_name)
{
	zval *repo;
	php_git2_t *_repo;
	char *canonical_branch_name = {0};
	int canonical_branch_name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_branch_remote_name not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rs", &buffer_size, &repo, &canonical_branch_name, &canonical_branch_name_len) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_buffer_size, php_git2_t*, &buffer_size, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

