#include "php_git2.h"
#include "php_git2_priv.h"
#include "branch.h"

/* {{{ proto resource git_branch_create(resource $repo, string $branch_name, resource $target, long $force)
 */
PHP_FUNCTION(git_branch_create)
{
	php_git2_t *result = NULL, *_repo = NULL, *_target = NULL;
	git_reference *out = NULL;
	zval *repo = NULL, *target = NULL;
	char *branch_name = NULL;
	int branch_name_len = 0, error = 0;
	long force = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrl", &repo, &branch_name, &branch_name_len, &target, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_target, php_git2_t*, &target, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_create(&out, PHP_GIT2_V(_repo, repository), branch_name, PHP_GIT2_V(_target, commit), force);
	if (php_git2_check_error(error, "git_branch_create" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto long git_branch_delete(resource $branch)
 */
PHP_FUNCTION(git_branch_delete)
{
	int result = 0;
	zval *branch = NULL;
	php_git2_t *_branch = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &branch) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_branch_delete(PHP_GIT2_V(_branch, reference));
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto resource git_branch_iterator_new(resource $repo,  $list_flags)
 */
PHP_FUNCTION(git_branch_iterator_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_branch_iterator *out = NULL;
	zval *repo = NULL;
	int error = 0;
	long list_flags = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &repo, &list_flags) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_iterator_new(&out, PHP_GIT2_V(_repo, repository), list_flags);
	if (php_git2_check_error(error, "git_branch_iterator_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_BRANCH_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_branch_next(long $out_type, resource $iter)
 */
PHP_FUNCTION(git_branch_next)
{
	php_git2_t *result = NULL, *_iter = NULL;
	git_reference *out = NULL;
	zval *iter = NULL;
	long out_type = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lr", &out_type, &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_next(&out, out_type, PHP_GIT2_V(_iter, branch_iterator));
	if (php_git2_check_error(error, "git_branch_next" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto void git_branch_iterator_free(resource $iter)
 */
PHP_FUNCTION(git_branch_iterator_free)
{
	zval *iter = NULL;
	php_git2_t *_iter = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_iter)) {
		git_branch_iterator_free(PHP_GIT2_V(_iter, branch_iterator));
		GIT2_SHOULD_FREE(_iter) = 0;
	};
	zval_ptr_dtor(&iter);
}
/* }}} */

/* {{{ proto resource git_branch_move(resource $branch, string $new_branch_name, long $force)
 */
PHP_FUNCTION(git_branch_move)
{
	php_git2_t *result = NULL, *_branch = NULL;
	git_reference *out = NULL;
	zval *branch = NULL;
	char *new_branch_name = NULL;
	int new_branch_name_len = 0, error = 0;
	long force = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &branch, &new_branch_name, &new_branch_name_len, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_move(&out, PHP_GIT2_V(_branch, reference), new_branch_name, force);
	if (php_git2_check_error(error, "git_branch_move" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_branch_lookup(resource $repo, string $branch_name,  $branch_type)
 */
PHP_FUNCTION(git_branch_lookup)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_reference *out = NULL;
	zval *repo = NULL;
	char *branch_name = NULL;
	int branch_name_len = 0, error = 0;
	long branch_type = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &branch_name, &branch_name_len, &branch_type) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_lookup(&out, PHP_GIT2_V(_repo, repository), branch_name, branch_type);
	if (php_git2_check_error(error, "git_branch_lookup" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_branch_name(resource $ref)
 */
PHP_FUNCTION(git_branch_name)
{
	php_git2_t *result = NULL;
	char out[GIT2_BUFFER_SIZE] = {0};
	zval *ref = NULL;
	php_git2_t *_ref = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_name(&out, PHP_GIT2_V(_ref, reference));
	if (php_git2_check_error(error, "git_branch_name" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto resource git_branch_upstream(resource $branch)
 */
PHP_FUNCTION(git_branch_upstream)
{
	php_git2_t *result = NULL, *_branch = NULL;
	git_reference *out = NULL;
	zval *branch = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &branch) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_upstream(&out, PHP_GIT2_V(_branch, reference));
	if (php_git2_check_error(error, "git_branch_upstream" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_branch_upstream_name(resource $repo, string $canonical_branch_name)
 */
PHP_FUNCTION(git_branch_upstream_name)
{
	php_git2_t *result = NULL;
	char tracking_branch_name_out[GIT2_BUFFER_SIZE] = {0};
	long buffer_size = GIT2_BUFFER_SIZE;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *canonical_branch_name = NULL;
	int canonical_branch_name_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &canonical_branch_name, &canonical_branch_name_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_upstream_name(&tracking_branch_name_out, buffer_size, PHP_GIT2_V(_repo, repository), canonical_branch_name);
	if (php_git2_check_error(error, "git_branch_upstream_name" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(tracking_branch_name_out, 1);
}
/* }}} */

/* {{{ proto long git_branch_is_head(resource $branch)
 */
PHP_FUNCTION(git_branch_is_head)
{
	int result = 0;
	zval *branch = NULL;
	php_git2_t *_branch = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &branch) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_branch, php_git2_t*, &branch, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_branch_is_head(PHP_GIT2_V(_branch, reference));
	RETURN_BOOL(result);
}
/* }}} */

/* {{{ proto resource git_branch_remote_name(resource $repo, string $canonical_branch_name)
 */
PHP_FUNCTION(git_branch_remote_name)
{
	php_git2_t *result = NULL;
	char remote_name_out[GIT2_BUFFER_SIZE] = {0};
	long buffer_size = GIT2_BUFFER_SIZE;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *canonical_branch_name = NULL;
	int canonical_branch_name_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &canonical_branch_name, &canonical_branch_name_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_branch_remote_name(&remote_name_out, buffer_size, PHP_GIT2_V(_repo, repository), canonical_branch_name);
	if (php_git2_check_error(error, "git_branch_remote_name" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(remote_name_out, 1);
}
/* }}} */
