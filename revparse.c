#include "php_git2.h"
#include "php_git2_priv.h"
#include "revparse.h"

/* {{{ proto resource git_revparse_single(resource $repo, string $spec)
 */
PHP_FUNCTION(git_revparse_single)
{
	php_git2_t *result = NULL;
	git_object *out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *spec = NULL;
	int spec_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &spec, &spec_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revparse_single(&out, PHP_GIT2_V(_repo, repository), spec);
	if (php_git2_check_error(error, "git_revparse_single" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, object) = out;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto array git_revparse_ext(resource $repo, string $spec)
 */
PHP_FUNCTION(git_revparse_ext)
{
	zval *array, *a, *b;
	php_git2_t *result = NULL, *result2 = NULL;
	git_object *object_out = NULL;
	git_reference *reference_out = NULL;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *spec = NULL;
	int spec_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &spec, &spec_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_revparse_ext(&object_out, &reference_out, PHP_GIT2_V(_repo, repository), spec);
	if (php_git2_check_error(error, "git_revparse_ext" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_MAKE_RESOURCE(result2);
	MAKE_STD_ZVAL(array);
	MAKE_STD_ZVAL(a);
	MAKE_STD_ZVAL(b);

	PHP_GIT2_V(result, object) = object_out;
	result->type = PHP_GIT2_TYPE_OBJECT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;
	ZVAL_RESOURCE(a, result->resource_id);

	PHP_GIT2_V(result2, reference) = reference_out;
	result2->type = PHP_GIT2_TYPE_REFERENCE;
	result2->resource_id = PHP_GIT2_LIST_INSERT(result2, git2_resource_handle);
	result2->should_free_v = 0;
	ZVAL_RESOURCE(b, result->resource_id);

	array_init(array);
	add_next_index_zval(array, a);
	add_next_index_zval(array, b);
	RETURN_ZVAL(array, 0, 1);
}
/* }}} */

/* {{{ proto array git_revparse(resource $repo, string $spec)
 */
PHP_FUNCTION(git_revparse)
{
	git_revspec revspec;
	zval *repo = NULL;
	php_git2_t *_repo = NULL, *_from = NULL, *_to = NULL;
	zval *result = NULL, *from, *to;
	char *spec = NULL;
	int spec_len = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &spec, &spec_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	memset(&revspec, '\0', sizeof(revspec));
	error = git_revparse(&revspec, PHP_GIT2_V(_repo, repository), spec);
	if (php_git2_check_error(error, "git_revparse" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	MAKE_STD_ZVAL(result);
	MAKE_STD_ZVAL(from);
	MAKE_STD_ZVAL(to);

	PHP_GIT2_V(_from, object) = revspec.from;
	_from->type = PHP_GIT2_TYPE_OBJECT;
	_from->resource_id = PHP_GIT2_LIST_INSERT(_from, git2_resource_handle);
	_from->should_free_v = 0;
	ZVAL_RESOURCE(from, _from->resource_id);

	PHP_GIT2_V(_to, object) = revspec.to;
	_to->type = PHP_GIT2_TYPE_OBJECT;
	_to->resource_id = PHP_GIT2_LIST_INSERT(_to, git2_resource_handle);
	_to->should_free_v = 0;
	ZVAL_RESOURCE(to, _to->resource_id);

	array_init(result);
	add_assoc_zval_ex(result, ZEND_STRS("from"), from);
	add_assoc_zval_ex(result, ZEND_STRS("to"), to);
	add_assoc_long_ex(result, ZEND_STRS("flags"), revspec.flags);

	RETURN_ZVAL(result, 0, 1);
}
/* }}} */

