#include "php_git2.h"
#include "php_git2_priv.h"
#include "reflog.h"

/* {{{ proto resource git_reflog_read(resource $repo, string $name)
 */
PHP_FUNCTION(git_reflog_read)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_reflog *out = NULL;
	zval *repo = NULL;
	char *name = NULL;
	int name_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reflog_read(&out, PHP_GIT2_V(_repo, repository), name);
	if (php_git2_check_error(error, "git_reflog_read" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFLOG, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_reflog_write(resource $reflog)
 */
PHP_FUNCTION(git_reflog_write)
{
	int result = 0, error = 0;
	zval *reflog = NULL;
	php_git2_t *_reflog = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &reflog) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reflog, php_git2_t*, &reflog, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_write(PHP_GIT2_V(_reflog, reflog));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reflog_append(resource $reflog, string $id, array $committer, string $msg)
 */
PHP_FUNCTION(git_reflog_append)
{
	int result = 0, id_len = 0, msg_len = 0, error = 0;
	zval *reflog = NULL, *committer = NULL;
	php_git2_t *_reflog = NULL;
	char *id = NULL, *msg = NULL;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsas", &reflog, &id, &id_len, &committer, &msg, &msg_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reflog, php_git2_t*, &reflog, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_reflog_append(PHP_GIT2_V(_reflog, reflog), &__id, committer, msg);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reflog_append_to(resource $repo, string $name, string $id, array $committer, string $msg)
 */
PHP_FUNCTION(git_reflog_append_to)
{
	int result = 0, name_len = 0, id_len = 0, msg_len = 0, error = 0;
	zval *repo = NULL, *committer = NULL;
	php_git2_t *_repo = NULL;
	char *name = NULL, *id = NULL, *msg = NULL;
	git_oid __id = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssas", &repo, &name, &name_len, &id, &id_len, &committer, &msg, &msg_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	result = git_reflog_append_to(PHP_GIT2_V(_repo, repository), name, &__id, committer, msg);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reflog_rename(resource $repo, string $old_name, string $name)
 */
PHP_FUNCTION(git_reflog_rename)
{
	int result = 0, old_name_len = 0, name_len = 0, error = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *old_name = NULL, *name = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &old_name, &old_name_len, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_rename(PHP_GIT2_V(_repo, repository), old_name, name);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reflog_delete(resource $repo, string $name)
 */
PHP_FUNCTION(git_reflog_delete)
{
	int result = 0, name_len = 0, error = 0;
	zval *repo = NULL;
	php_git2_t *_repo = NULL;
	char *name = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_delete(PHP_GIT2_V(_repo, repository), name);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reflog_entrycount(resource $reflog)
 */
PHP_FUNCTION(git_reflog_entrycount)
{
	size_t result = 0;
	zval *reflog = NULL;
	php_git2_t *_reflog = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &reflog) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reflog, php_git2_t*, &reflog, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_entrycount(PHP_GIT2_V(_reflog, reflog));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_reflog_entry_byindex(resource $reflog, long $idx)
 */
PHP_FUNCTION(git_reflog_entry_byindex)
{
	const git_reflog_entry  *result = NULL;
	zval *reflog = NULL;
	php_git2_t *_reflog = NULL, *_result;
	long idx = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &reflog, &idx) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reflog, php_git2_t*, &reflog, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_entry_byindex(PHP_GIT2_V(_reflog, reflog), idx);
	if (php_git2_make_resource(&_result, PHP_GIT2_TYPE_REFLOG_ENTRY, result, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(_result));
}
/* }}} */

/* {{{ proto long git_reflog_drop(resource $reflog, long $idx, long $rewrite_previous_entry)
 */
PHP_FUNCTION(git_reflog_drop)
{
	int result = 0, error = 0;
	zval *reflog = NULL;
	php_git2_t *_reflog = NULL;
	long idx = 0, rewrite_previous_entry = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rll", &reflog, &idx, &rewrite_previous_entry) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reflog, php_git2_t*, &reflog, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_drop(PHP_GIT2_V(_reflog, reflog), idx, rewrite_previous_entry);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_reflog_entry_id_old(resource $entry)
 */
PHP_FUNCTION(git_reflog_entry_id_old)
{
	const git_oid  *result = NULL;
	zval *entry = NULL;
	php_git2_t *_entry = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &entry) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_entry, php_git2_t*, &entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_entry_id_old(PHP_GIT2_V(_entry, reflog_entry));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto resource git_reflog_entry_id_new(resource $entry)
 */
PHP_FUNCTION(git_reflog_entry_id_new)
{
	const git_oid  *result = NULL;
	zval *entry = NULL;
	php_git2_t *_entry = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &entry) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_entry, php_git2_t*, &entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_entry_id_new(PHP_GIT2_V(_entry, reflog_entry));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto array git_reflog_entry_committer(resource $entry)
 */
PHP_FUNCTION(git_reflog_entry_committer)
{
	const git_signature  *result = NULL;
	zval *__result = NULL, *entry = NULL;
	php_git2_t *_entry = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &entry) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_entry, php_git2_t*, &entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_entry_committer(PHP_GIT2_V(_entry, reflog_entry));
	php_git2_signature_to_array(result, &__result TSRMLS_CC);
	RETURN_ZVAL(__result, 0, 1);
}
/* }}} */

/* {{{ proto string git_reflog_entry_message(resource $entry)
 */
PHP_FUNCTION(git_reflog_entry_message)
{
	const char  *result = NULL;
	zval *entry = NULL;
	php_git2_t *_entry = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &entry) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_entry, php_git2_t*, &entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_reflog_entry_message(PHP_GIT2_V(_entry, reflog_entry));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto void git_reflog_free(resource $reflog)
 */
PHP_FUNCTION(git_reflog_free)
{
	zval *reflog = NULL;
	php_git2_t *_reflog = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &reflog) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_reflog, php_git2_t*, &reflog, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_reflog)) {
		git_reflog_free(PHP_GIT2_V(_reflog, reflog));
		GIT2_SHOULD_FREE(_reflog) = 0;
	};
	zval_ptr_dtor(&reflog);
}
/* }}} */

