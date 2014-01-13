#include "php_git2.h"
#include "php_git2_priv.h"
#include "signature.h"

/* {{{ proto resource git_signature_new(string $name, string $email, array $time, long $offset)
 */
PHP_FUNCTION(git_signature_new)
{
	php_git2_t *result = NULL;
	git_signature *out = NULL;
	char *name = NULL, *email = NULL;
	int name_len = 0, email_len = 0, error = 0;
	long time = 0, offset = 0;
	zval *signature = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ssll", &name, &name_len, &email, &email_len, &time, &offset) == FAILURE) {
		return;
	}
	
	error = git_signature_new(&out, name, email, time, offset);
	if (php_git2_check_error(error, "git_signature_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	php_git2_signature_to_array(out, &signature TSRMLS_CC);
	git_signature_free(out);
	RETURN_ZVAL(signature, 0, 1);
}
/* }}} */

/* {{{ proto resource git_signature_now(string $name, string $email)
 */
PHP_FUNCTION(git_signature_now)
{
	php_git2_t *result = NULL;
	git_signature *out = NULL;
	char *name = NULL, *email = NULL;
	int name_len = 0, email_len = 0, error = 0;
	zval *signature = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss", &name, &name_len, &email, &email_len) == FAILURE) {
		return;
	}
	
	error = git_signature_now(&out, name, email);
	if (php_git2_check_error(error, "git_signature_now" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	php_git2_signature_to_array(out, &signature TSRMLS_CC);
	git_signature_free(out);
	RETURN_ZVAL(signature, 0, 1);
}
/* }}} */

/* {{{ proto resource git_signature_default(resource $repo)
 */
PHP_FUNCTION(git_signature_default)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_signature *out = NULL;
	zval *repo = NULL, *signature = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_signature_default(&out, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_signature_default" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	php_git2_signature_to_array(out, &signature TSRMLS_CC);
	git_signature_free(out);
	RETURN_ZVAL(signature, 0, 1);
}
/* }}} */

/* {{{ proto array git_signature_dup(array $sig)
 */
PHP_FUNCTION(git_signature_dup)
{
	// TODO(chobie): remove later. we don't need to export this function */
	git_signature  *result = NULL;
	zval *__result = NULL, *sig = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &sig) == FAILURE) {
		return;
	}
	
	result = git_signature_dup(sig);
	php_git2_signature_to_array(result, &__result TSRMLS_CC);
	git_signature_free(result);
	RETURN_ZVAL(__result, 0, 1);
}
/* }}} */

/* {{{ proto void git_signature_free(array $sig)
 */
PHP_FUNCTION(git_signature_free)
{
	// TODO(chobie): remove later. we don't need to export this function */
}
/* }}} */

