#include "php_git2.h"
#include "php_git2_priv.h"
#include "revparse.h"

/* {{{ proto resource git_revparse_single(repo, spec)
*/
PHP_FUNCTION(git_revparse_single)
{
	zval *repo;
	php_git2_t *_repo;
	char *spec = {0};
	int spec_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revparse_single not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &spec, &spec_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_revparse_ext(reference_out, repo, spec)
*/
PHP_FUNCTION(git_revparse_ext)
{
	zval *reference_out;
	php_git2_t *_reference_out;
	zval *repo;
	php_git2_t *_repo;
	char *spec = {0};
	int spec_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revparse_ext not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrs", &reference_out, &repo, &spec, &spec_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_reference_out, php_git2_t*, &reference_out, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_revparse(revspec, repo, spec)
*/
PHP_FUNCTION(git_revparse)
{
	zval *revspec;
	php_git2_t *_revspec;
	zval *repo;
	php_git2_t *_repo;
	char *spec = {0};
	int spec_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_revparse not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrs", &revspec, &repo, &spec, &spec_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_revspec, php_git2_t*, &revspec, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

