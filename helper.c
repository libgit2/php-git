#include "php_git2.h"
#include "helper.h"

int php_git2_check_error(int error_code, const char *action TSRMLS_DC)
{
	int result = 0;
	const git_error * error;
	if (!error_code) {
		return result;
	}

	error = giterr_last();
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "WARNING %d %s - %s",
		error_code, action, (error && error->message) ? error->message : "???");

	result = 1;
	return result;
}


zval* php_git2_read_arrval(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *result = NULL, **element;

	if (zend_hash_find(Z_ARRVAL_P(array), name, name_len, (void**)&element) == SUCCESS) {
		result = *element;
	}

	return result;
}

long php_git2_read_arrval_long(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *tmp;
	long result = 0;

	tmp = php_git2_read_arrval(array, name, name_len TSRMLS_CC);
	if (tmp) {
		result = Z_LVAL_P(tmp);
	}

	return result;
}

const char* php_git2_read_arrval_string(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *tmp;
	const char *result = NULL;

	tmp = php_git2_read_arrval(array, name, name_len TSRMLS_CC);
	if (tmp) {
		result = Z_STRVAL_P(tmp);
	}

	return result;
}