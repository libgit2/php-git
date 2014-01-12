#include "php_git2.h"
#include "php_git2_priv.h"
#include "signature.h"

/* {{{ proto resource git_signature_new(string $name, string $email,  $time, long $offset)
 */
PHP_FUNCTION(git_signature_new)
{
	php_git2_t *result = NULL;
	git_signature *out = NULL;
	char *name = NULL, *email = NULL;
	int name_len = 0, email_len = 0, error = 0;
	zval *time = NULL;
	long offset = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ssal", &name, &name_len, &email, &email_len, &time, &offset) == FAILURE) {
		return;
	}
	
	error = git_signature_new(&out, name, email, time, offset);
	if (php_git2_check_error(error, "git_signature_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
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
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ss", &name, &name_len, &email, &email_len) == FAILURE) {
		return;
	}
	
	error = git_signature_now(&out, name, email);
	if (php_git2_check_error(error, "git_signature_now" TSRMLS_CC)) {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto resource git_signature_default(resource $repo)
 */
PHP_FUNCTION(git_signature_default)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_signature *out = NULL;
	zval *repo = NULL;
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
}
/* }}} */

/* {{{ proto array git_signature_dup(array $sig)
 */
PHP_FUNCTION(git_signature_dup)
{
	git_signature  *result = NULL;
	zval *__result = NULL, *sig = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &sig) == FAILURE) {
		return;
	}
	
	result = git_signature_dup(sig);
	php_git2_signature_to_array(result, &__result TSRMLS_CC);
	RETURN_ZVAL(__result, 0, 1);
}
/* }}} */

/* {{{ proto void git_signature_free(array $sig)
 */
PHP_FUNCTION(git_signature_free)
{
//	zval *sig = NULL;
//
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"a", &sig) == FAILURE) {
//		return;
//	}
//
//	if (GIT2_SHOULD_FREE(_sig)) {
//		git_signature_free(sig);
//		GIT2_SHOULD_FREE(_sig) = 0;
//	};
//	zval_ptr_dtor(&sig);
}
/* }}} */

