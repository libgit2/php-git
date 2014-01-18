#include "php_git2.h"
#include "php_git2_priv.h"
#include "merge.h"

/* {{{ proto resource git_merge_base(resource $repo, string $one, string $two)
 */
PHP_FUNCTION(git_merge_base)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_oid out = {0}, __one = {0}, __two = {0};
	zval *repo = NULL;
	char *one = NULL, *two = NULL, oid[41] = {0};
	int one_len = 0, two_len = 0, error = 0;
	
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
	git_oid_fmt(oid, &out);
	RETURN_STRING(oid, 1);
}
/* }}} */

/* {{{ proto resource git_merge_base_many(resource $repo, long $length, string $input_array[])
 */
PHP_FUNCTION(git_merge_base_many)
{
//	php_git2_t *result = NULL, *_repo = NULL;
//	git_oid out = {0}, __input_array[] = {0};
//	zval *repo = NULL;
//	long length = 0;
//	char *input_array[] = NULL;
//	int input_array[]_len = 0, error = 0;
	
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rls", &repo, &length, &input_array[], &input_array[]_len) == FAILURE) {
//		return;
//	}
	
//	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
//	if (git_oid_fromstrn(&__input_array[], input_array[], input_array[]_len)) {
//		RETURN_FALSE;
//	}
//	error = git_merge_base_many(&__out, PHP_GIT2_V(_repo, repository), length, __input_array[]);
//	if (php_git2_check_error(error, "git_merge_base_many" TSRMLS_CC)) {
//		RETURN_FALSE;
//	}
//	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_OID, out, 1 TSRMLS_CC)) {
//		RETURN_FALSE;
//	}
//	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_merge_head_from_ref(resource $repo, resource $ref)
 */
PHP_FUNCTION(git_merge_head_from_ref)
{
	php_git2_t *result = NULL, *_repo = NULL, *_ref = NULL;
	git_merge_head *out = NULL;
	zval *repo = NULL, *ref = NULL;
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_MERGE_HEAD, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_merge_head_from_fetchhead(resource $repo, string $branch_name, string $remote_url, string $oid)
 */
PHP_FUNCTION(git_merge_head_from_fetchhead)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_merge_head *out = NULL;
	zval *repo = NULL;
	char *branch_name = NULL, *remote_url = NULL, *oid = NULL;
	int branch_name_len = 0, remote_url_len = 0, oid_len = 0, error = 0;
	git_oid __oid = {0};
	
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_MERGE_HEAD, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_merge_head_from_oid(resource $repo, string $oid)
 */
PHP_FUNCTION(git_merge_head_from_oid)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_merge_head *out = NULL;
	zval *repo = NULL;
	char *oid = NULL;
	int oid_len = 0, error = 0;
	git_oid __oid = {0};
	
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_MERGE_HEAD, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
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
	if (GIT2_SHOULD_FREE(_head)) {
		git_merge_head_free(PHP_GIT2_V(_head, merge_head));
		GIT2_SHOULD_FREE(_head) = 0;
	};
	zval_ptr_dtor(&head);
}
/* }}} */

/* {{{ proto resource git_merge_trees(resource $repo, resource $ancestor_tree, resource $our_tree, resource $their_tree,  $opts)
 */
PHP_FUNCTION(git_merge_trees)
{
	php_git2_t *result = NULL, *_repo = NULL, *_ancestor_tree = NULL, *_our_tree = NULL, *_their_tree = NULL;
	git_index *out = NULL;
	zval *repo = NULL, *ancestor_tree = NULL, *our_tree = NULL, *their_tree = NULL, *opts = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrrr<git_merge_tree_opts>", &repo, &ancestor_tree, &our_tree, &their_tree, &opts) == FAILURE) {
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
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_INDEX, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_merge(resource $repo, array $their_heads, array $opts)
 */
PHP_FUNCTION(git_merge)
{
	php_git2_t *result = NULL, *_repo = NULL, *_their_head = NULL;
	git_merge_result *out = NULL;
	zval *repo = NULL, *opts = NULL, *theirhead = NULL;
	git_merge_head *their_heads = NULL;
	git_merge_head *heads[1];
	long their_heads_len = 0;
	int error = 0;
	git_merge_opts options = GIT_MERGE_OPTS_INIT;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rza", &repo, &theirhead, &opts) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_their_head, php_git2_t*, &theirhead, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	heads[0] = PHP_GIT2_V(_their_head, merge_head);
	options.merge_flags = GIT_MERGE_NO_FASTFORWARD;

	error = git_merge(&out, PHP_GIT2_V(_repo, repository), heads, 1, &options);
	if (php_git2_check_error(error, "git_merge" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_MERGE_RESULT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_merge_result_is_uptodate(resource $merge_result)
 */
PHP_FUNCTION(git_merge_result_is_uptodate)
{
	int result = 0, error = 0;
	zval *merge_result = NULL;
	php_git2_t *_merge_result = NULL;
	
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
	int result = 0, error = 0;
	zval *merge_result = NULL;
	php_git2_t *_merge_result = NULL;
	
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
	php_git2_t *result = NULL, *_merge_result = NULL;
	git_oid out = {0};
	zval *merge_result = NULL;
	int error = 0;
	char buf[41] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &merge_result) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_merge_result, php_git2_t*, &merge_result, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_merge_result_fastforward_oid(&out, PHP_GIT2_V(_merge_result, merge_result));
	if (php_git2_check_error(error, "git_merge_result_fastforward_oid" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
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
	if (GIT2_SHOULD_FREE(_merge_result)) {
		git_merge_result_free(PHP_GIT2_V(_merge_result, merge_result));
		GIT2_SHOULD_FREE(_merge_result) = 0;
	};
	zval_ptr_dtor(&merge_result);
}
/* }}} */

