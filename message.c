#include "php_git2.h"
#include "php_git2_priv.h"
#include "message.h"

/* {{{ proto resource git_message_prettify(string $message, long $strip_comments)
 */
PHP_FUNCTION(git_message_prettify)
{
	char *out = NULL, *message = NULL;
	long out_size = 0, strip_comments = 0;
	int message_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &message, &message_len, &strip_comments) == FAILURE) {
		return;
	}

	out_size = git_message_prettify(NULL, NULL, message, strip_comments);
	out = (char*)emalloc(sizeof(char) * out_size);
	error = git_message_prettify(out, out_size, message, strip_comments);
	RETURN_STRING(out, 0);
}
/* }}} */

