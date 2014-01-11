#include "php_git2.h"
#include "php_git2_priv.h"
#include "merge.h"

/* {{{ proto resource git_merge_base(repo, one, two)
*/
PHP_FUNCTION(git_merge_base)
{
	zval *repo;
	php_git2_t *_repo;
	char *one = {0};
	int one_len;
	char *two = {0};
	int two_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_base not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &one, &one_len, &two, &two_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge_base_many(repo, length, input_array[])
*/
PHP_FUNCTION(git_merge_base_many)
{
//	zval *repo;
//	php_git2_t *_repo;
//	char *input_array[] = {0};
//	int input_array[]_len;
//
//	/* TODO(chobie): implement this */
//	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_base_many not implemented yet");
//	return;
//
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rs", &repo, &length, &input_array[], &input_array[]_len) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge_head_from_ref(repo, ref)
*/
PHP_FUNCTION(git_merge_head_from_ref)
{
	zval *repo;
	php_git2_t *_repo;
	zval *ref;
	php_git2_t *_ref;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_head_from_ref not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge_head_from_fetchhead(repo, branch_name, remote_url, oid)
*/
PHP_FUNCTION(git_merge_head_from_fetchhead)
{
	zval *repo;
	php_git2_t *_repo;
	char *branch_name = {0};
	int branch_name_len;
	char *remote_url = {0};
	int remote_url_len;
	char *oid = {0};
	int oid_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_head_from_fetchhead not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsss", &repo, &branch_name, &branch_name_len, &remote_url, &remote_url_len, &oid, &oid_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge_head_from_oid(repo, oid)
*/
PHP_FUNCTION(git_merge_head_from_oid)
{
	zval *repo;
	php_git2_t *_repo;
	char *oid = {0};
	int oid_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_head_from_oid not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &oid, &oid_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_merge_head_free(head)
*/
PHP_FUNCTION(git_merge_head_free)
{
	zval *head;
	php_git2_t *_head;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_head_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &head) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_head, php_git2_t*, &head, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge_trees(repo, ancestor_tree, our_tree, their_tree, opts)
*/
PHP_FUNCTION(git_merge_trees)
{
	zval *repo;
	php_git2_t *_repo;
	zval *ancestor_tree;
	php_git2_t *_ancestor_tree;
	zval *our_tree;
	php_git2_t *_our_tree;
	zval *their_tree;
	php_git2_t *_their_tree;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_trees not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrrrr", &repo, &ancestor_tree, &our_tree, &their_tree, &opts) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge(repo, their_heads, their_heads_len, opts)
*/
PHP_FUNCTION(git_merge)
{
	zval *repo;
	php_git2_t *_repo;
	zval *their_heads;
	php_git2_t *_their_heads;
	zval *opts;
	php_git2_t *_opts;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rrr", &repo, &their_heads, &their_heads_len, &opts) == FAILURE) {
//		return;
//	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_merge_result_is_uptodate(merge_result)
*/
PHP_FUNCTION(git_merge_result_is_uptodate)
{
	zval *merge_result;
	php_git2_t *_merge_result;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_result_is_uptodate not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_merge_result_is_fastforward(merge_result)
*/
PHP_FUNCTION(git_merge_result_is_fastforward)
{
	zval *merge_result;
	php_git2_t *_merge_result;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_result_is_fastforward not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_merge_result_fastforward_oid(merge_result)
*/
PHP_FUNCTION(git_merge_result_fastforward_oid)
{
	zval *merge_result;
	php_git2_t *_merge_result;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_result_fastforward_oid not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_merge_result_free(merge_result)
*/
PHP_FUNCTION(git_merge_result_free)
{
	zval *merge_result;
	php_git2_t *_merge_result;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_merge_result_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

