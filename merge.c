#include "php_git2.h"
#include "php_git2_priv.h"
#include "merge.h"

/* {{{ proto resource git_merge_base(resource $repo, string $one, string $two)
 */
PHP_FUNCTION(git_merge_base)
{
	git_oid out = {0};
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *one = NULL;
	int one_len = 0;
	git_oid __one;
	char *two = NULL;
	int two_len = 0;
	git_oid __two;
	int error = 0;
	char result[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &one, &one_len, &two, &two_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__one, one, one_len)) {
		RETURN_FALSE;
	}
	if (git_oid_fromstrn(&__two, two, two_len)) {
		RETURN_FALSE;
	}
	error = git_merge_base(&out, PHP_GIT2_V(_repo, repository), &__one, &__two);
	if (php_git2_check_error(error, "git_merge_base" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(result, &out);
	RETURN_STRING(result, 1);
}
/* }}} */


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

/* {{{ proto resource git_merge_head_from_ref(resource $repo, resource $ref)
 */
PHP_FUNCTION(git_merge_head_from_ref)
{
	php_git2_t *result = NULL;
	git_merge_head *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *ref = NULL;
	php_git2_t *_ref = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &ref) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_merge_head_from_ref(&out, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_ref, reference));
	if (php_git2_check_error(error, "git_merge_head_from_ref" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, merge_head) = out;
	result->type = PHP_GIT2_TYPE_MERGE_HEAD;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto resource git_merge_head_from_fetchhead(resource $repo, string $branch_name, string $remote_url, string $oid)
 */
PHP_FUNCTION(git_merge_head_from_fetchhead)
{
	php_git2_t *result = NULL;
	git_merge_head *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *branch_name = NULL;
	int branch_name_len = 0;
	char *remote_url = NULL;
	int remote_url_len = 0;
	char *oid = NULL;
	int oid_len = 0;
	git_oid __oid;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsss", &repo, &branch_name, &branch_name_len, &remote_url, &remote_url_len, &oid, &oid_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__oid, oid, oid_len)) {
		RETURN_FALSE;
	}
	error = git_merge_head_from_fetchhead(&out, PHP_GIT2_V(_repo, repository), branch_name, remote_url, &__oid);
	if (php_git2_check_error(error, "git_merge_head_from_fetchhead" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, merge_head) = out;
	result->type = PHP_GIT2_TYPE_MERGE_HEAD;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto resource git_merge_head_from_oid(resource $repo, string $oid)
 */
PHP_FUNCTION(git_merge_head_from_oid)
{
	php_git2_t *result = NULL;
	git_merge_head *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *oid = NULL;
	int oid_len = 0;
	git_oid __oid;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &oid, &oid_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__oid, oid, oid_len)) {
		RETURN_FALSE;
	}
	error = git_merge_head_from_oid(&out, PHP_GIT2_V(_repo, repository), &__oid);
	if (php_git2_check_error(error, "git_merge_head_from_oid" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, merge_head) = out;
	result->type = PHP_GIT2_TYPE_MERGE_HEAD;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto void git_merge_head_free(resource $head)
 */
PHP_FUNCTION(git_merge_head_free)
{
	zval *head = NULL;
	php_git2_t *_head = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &head) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_head, php_git2_t*, &head, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_head->should_free_v) {
		git_merge_head_free(PHP_GIT2_V(_head, merge_head));
	};
	zval_ptr_dtor(&head);
}
/* }}} */


/* {{{ proto resource git_merge_trees(resource $repo, resource $ancestor_tree, resource $our_tree, resource $their_tree,  $opts)
 */
PHP_FUNCTION(git_merge_trees)
{
	php_git2_t *result = NULL;
	git_index *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	zval *ancestor_tree = NULL;
	php_git2_t *_ancestor_tree = NULL;
	zval *our_tree = NULL;
	php_git2_t *_our_tree = NULL;
	zval *their_tree = NULL;
	php_git2_t *_their_tree = NULL;
	zval *opts = NULL;
	int error = 0;

	/* TODO(chobie): create array converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrrra", &repo, &ancestor_tree, &our_tree, &their_tree, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_ancestor_tree, php_git2_t*, &ancestor_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_our_tree, php_git2_t*, &our_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_their_tree, php_git2_t*, &their_tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_merge_trees(&out, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_ancestor_tree, tree), PHP_GIT2_V(_our_tree, tree), PHP_GIT2_V(_their_tree, tree), opts);
	if (php_git2_check_error(error, "git_merge_trees" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, index) = out;
	result->type = PHP_GIT2_TYPE_INDEX;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */



/* {{{ proto resource git_merge(resource $repo, long $their_heads_len,  $opts)
 */
PHP_FUNCTION(git_merge)
{
	php_git2_t *result = NULL;
	git_merge_result *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	git_merge_head *their_heads = NULL;
	long their_heads_len = 0;
	zval *opts = NULL;
	int error = 0;

	/* TODO(chobie): implement converter */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rla", &repo, &their_heads_len, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	//error = git_merge(&out, PHP_GIT2_V(_repo, repository), &their_heads, their_heads_len, opts);
	if (php_git2_check_error(error, "git_merge" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, merge_result) = out;
	result->type = PHP_GIT2_TYPE_MERGE_RESULT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */


/* {{{ proto long git_merge_result_is_uptodate(resource $merge_result)
 */
PHP_FUNCTION(git_merge_result_is_uptodate)
{
	int result = 0;
	zval *merge_result = NULL;
	php_git2_t *_merge_result = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_merge_result_is_uptodate(PHP_GIT2_V(_merge_result, merge_result));
	RETURN_BOOL(result);
}
/* }}} */


/* {{{ proto long git_merge_result_is_fastforward(resource $merge_result)
 */
PHP_FUNCTION(git_merge_result_is_fastforward)
{
	int result = 0;
	zval *merge_result = NULL;
	php_git2_t *_merge_result = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_merge_result_is_fastforward(PHP_GIT2_V(_merge_result, merge_result));
	RETURN_BOOL(result);
}
/* }}} */


/* {{{ proto resource git_merge_result_fastforward_oid(resource $merge_result)
 */
PHP_FUNCTION(git_merge_result_fastforward_oid)
{
	php_git2_t *result = NULL;
	git_oid out = {0};
	zval *merge_result = NULL;
	php_git2_t *_merge_result = NULL;
	int error = 0;
	char buffer[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_merge_result_fastforward_oid(&out, PHP_GIT2_V(_merge_result, merge_result));
	if (php_git2_check_error(error, "git_merge_result_fastforward_oid" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buffer, &out);
	RETURN_STRING(buffer, 1);
}
/* }}} */

/* {{{ proto void git_merge_result_free(resource $merge_result)
 */
PHP_FUNCTION(git_merge_result_free)
{
	zval *merge_result = NULL;
	php_git2_t *_merge_result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_merge_result->should_free_v) {
		git_merge_result_free(PHP_GIT2_V(_merge_result, merge_result));
	};
	zval_ptr_dtor(&merge_result);
}
/* }}} */

