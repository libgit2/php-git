#include "php_git2.h"
#include "php_git2_priv.h"
#include "message.h"

/* {{{ proto resource git_message_prettify(long $out_size, string $message, long $strip_comments)
 */
PHP_FUNCTION(git_message_prettify)
{
	php_git2_t *result = NULL;
	char out = NULL, *message = NULL;
	long out_size = 0, strip_comments = 0;
	int message_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lsl", &out_size, &message, &message_len, &strip_comments) == FAILURE) {
		return;
	}
	
	error = git_message_prettify(&out, out_size, message, strip_comments);
	if (php_git2_check_error(error, "git_message_prettify" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(out, 1);
}
/* }}} */

