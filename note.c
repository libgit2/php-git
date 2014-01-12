#include "php_git2.h"
#include "php_git2_priv.h"
#include "note.h"

/* {{{ proto resource git_note_iterator_new(resource $repo, string $notes_ref)
 */
PHP_FUNCTION(git_note_iterator_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_note_iterator *out = NULL;
	zval *repo = NULL;
	char *notes_ref = NULL;
	int notes_ref_len = 0, error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &notes_ref, &notes_ref_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_note_iterator_new(&out, PHP_GIT2_V(_repo, repository), notes_ref);
	if (php_git2_check_error(error, "git_note_iterator_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_NOTE_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto void git_note_iterator_free(resource $it)
 */
PHP_FUNCTION(git_note_iterator_free)
{
	zval *it = NULL;
	php_git2_t *_it = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &it) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_it, php_git2_t*, &it, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_it)) {
		git_note_iterator_free(PHP_GIT2_V(_it, note_iterator));
		GIT2_SHOULD_FREE(_it) = 0;
	};
	zval_ptr_dtor(&it);
}
/* }}} */

/* {{{ proto long git_note_next(string $note_id, string $annotated_id, resource $it)
 */
PHP_FUNCTION(git_note_next)
{
	int result = 0, note_id_len = 0, annotated_id_len = 0, error = 0;
	char *note_id = NULL, *annotated_id = NULL;
	zval *it = NULL;
	php_git2_t *_it = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ssr", &note_id, &note_id_len, &annotated_id, &annotated_id_len, &it) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_it, php_git2_t*, &it, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_note_next(note_id, annotated_id, PHP_GIT2_V(_it, note_iterator));
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_note_read(resource $repo, string $notes_ref, string $oid)
 */
PHP_FUNCTION(git_note_read)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_note *out = NULL;
	zval *repo = NULL;
	char *notes_ref = NULL, *oid = NULL;
	int notes_ref_len = 0, oid_len = 0, error = 0;
	git_oid __oid = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &repo, &notes_ref, &notes_ref_len, &oid, &oid_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__oid, oid, oid_len)) {
		RETURN_FALSE;
	}
	error = git_note_read(&out, PHP_GIT2_V(_repo, repository), notes_ref, &__oid);
	if (php_git2_check_error(error, "git_note_read" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_NOTE, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto string git_note_message(resource $note)
 */
PHP_FUNCTION(git_note_message)
{
	const char  *result = NULL;
	zval *note = NULL;
	php_git2_t *_note = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &note) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_note, php_git2_t*, &note, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_note_message(PHP_GIT2_V(_note, note));
	RETURN_STRING(result, 1);
}
/* }}} */

/* {{{ proto resource git_note_oid(resource $note)
 */
PHP_FUNCTION(git_note_oid)
{
	const git_oid  *result = NULL;
	zval *note = NULL;
	php_git2_t *_note = NULL;
	char __result[GIT2_OID_HEXSIZE] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &note) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_note, php_git2_t*, &note, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_note_oid(PHP_GIT2_V(_note, note));
	git_oid_fmt(__result, result);
	RETURN_STRING(__result, 1);
}
/* }}} */

/* {{{ proto resource git_note_create(resource $repo, array $author, array $committer, string $notes_ref, string $oid, string $note, long $force)
 */
PHP_FUNCTION(git_note_create)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_oid out = {0}, __oid = {0};
	zval *repo = NULL, *author = NULL, *committer = NULL;
	char *notes_ref = NULL, *oid = NULL, *note = NULL;
	int notes_ref_len = 0, oid_len = 0, note_len = 0, error = 0;
	long force = 0;
	char buf[41] = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"raasssl", &repo, &author, &committer, &notes_ref, &notes_ref_len, &oid, &oid_len, &note, &note_len, &force) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__oid, oid, oid_len)) {
		RETURN_FALSE;
	}
	error = git_note_create(&out, PHP_GIT2_V(_repo, repository), author, committer, notes_ref, &__oid, note, force);
	if (php_git2_check_error(error, "git_note_create" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_oid_fmt(buf, &out);
	RETURN_STRING(buf, 1);
}
/* }}} */

/* {{{ proto long git_note_remove(resource $repo, string $notes_ref, array $author, array $committer, string $oid)
 */
PHP_FUNCTION(git_note_remove)
{
	int result = 0, notes_ref_len = 0, oid_len = 0, error = 0;
	zval *repo = NULL, *author = NULL, *committer = NULL;
	php_git2_t *_repo = NULL;
	char *notes_ref = NULL, *oid = NULL;
	git_oid __oid = {0};
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsaas", &repo, &notes_ref, &notes_ref_len, &author, &committer, &oid, &oid_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__oid, oid, oid_len)) {
		RETURN_FALSE;
	}
	result = git_note_remove(PHP_GIT2_V(_repo, repository), notes_ref, author, committer, &__oid);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_note_free(resource $note)
 */
PHP_FUNCTION(git_note_free)
{
	zval *note = NULL;
	php_git2_t *_note = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &note) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_note, php_git2_t*, &note, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_note)) {
		git_note_free(PHP_GIT2_V(_note, note));
		GIT2_SHOULD_FREE(_note) = 0;
	};
	zval_ptr_dtor(&note);
}
/* }}} */

/* {{{ proto resource git_note_default_ref(resource $repo)
 */
PHP_FUNCTION(git_note_default_ref)
{
	php_git2_t *result = NULL, *_repo = NULL;
	char *out = NULL;
	zval *repo = NULL;
	int error = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_note_default_ref(&out, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_note_default_ref" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(out, 1);
}
/* }}} */

/* {{{ proto long git_note_foreach(resource $repo, string $notes_ref, Callable $note_cb,  $payload)
 */
PHP_FUNCTION(git_note_foreach)
{
	int result = 0, notes_ref_len = 0, error = 0;
	zval *repo = NULL, *note_cb = NULL, *payload = NULL;
	php_git2_t *_repo = NULL;
	char *notes_ref = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsfz", &repo, &notes_ref, &notes_ref_len, &fci, &fcc, &payload) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	//result = git_note_foreach(PHP_GIT2_V(_repo, repository), notes_ref, <CHANGEME>, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

