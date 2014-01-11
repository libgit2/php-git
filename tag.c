#include "php_git2.h"
#include "php_git2_priv.h"
#include "tag.h"

/* {{{ proto resource git_tag_lookup(repo, id)
*/
PHP_FUNCTION(git_tag_lookup)
{
	zval *repo;
	php_git2_t *_repo;
	char *id = {0};
	int id_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_lookup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &id, &id_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_lookup_prefix(repo, id, len)
*/
PHP_FUNCTION(git_tag_lookup_prefix)
{
	zval *repo;
	php_git2_t *_repo;
	char *id = {0};
	int id_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_lookup_prefix not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rs", &repo, &id, &id_len, &len) == FAILURE) {
//		return;
//	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_tag_free(tag)
*/
PHP_FUNCTION(git_tag_free)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_id(tag)
*/
PHP_FUNCTION(git_tag_id)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_id not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_owner(tag)
*/
PHP_FUNCTION(git_tag_owner)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_owner not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_target(tag)
*/
PHP_FUNCTION(git_tag_target)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_target not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_target_id(tag)
*/
PHP_FUNCTION(git_tag_target_id)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_target_id not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_target_type(tag)
*/
PHP_FUNCTION(git_tag_target_type)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_target_type not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_name(tag)
*/
PHP_FUNCTION(git_tag_name)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_name not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_tagger(tag)
*/
PHP_FUNCTION(git_tag_tagger)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_tagger not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_message(tag)
*/
PHP_FUNCTION(git_tag_message)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_message not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_create(repo, tag_name, target, tagger, message, force)
*/
PHP_FUNCTION(git_tag_create)
{
	zval *repo;
	php_git2_t *_repo;
	char *tag_name = {0};
	int tag_name_len;
	zval *target;
	php_git2_t *_target;
	zval *tagger;
	php_git2_t *_tagger;
	char *message = {0};
	int message_len;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_create not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrrsl", &repo, &tag_name, &tag_name_len, &target, &tagger, &message, &message_len, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_annotation_create(repo, tag_name, target, tagger, message)
*/
PHP_FUNCTION(git_tag_annotation_create)
{
	zval *repo;
	php_git2_t *_repo;
	char *tag_name = {0};
	int tag_name_len;
	zval *target;
	php_git2_t *_target;
	zval *tagger;
	php_git2_t *_tagger;
	char *message = {0};
	int message_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_annotation_create not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrrs", &repo, &tag_name, &tag_name_len, &target, &tagger, &message, &message_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_create_frombuffer(repo, buffer, force)
*/
PHP_FUNCTION(git_tag_create_frombuffer)
{
	zval *repo;
	php_git2_t *_repo;
	char *buffer = {0};
	int buffer_len;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_create_frombuffer not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &buffer, &buffer_len, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_create_lightweight(repo, tag_name, target, force)
*/
PHP_FUNCTION(git_tag_create_lightweight)
{
	zval *repo;
	php_git2_t *_repo;
	char *tag_name = {0};
	int tag_name_len;
	zval *target;
	php_git2_t *_target;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_create_lightweight not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrl", &repo, &tag_name, &tag_name_len, &target, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_tag_delete(repo, tag_name)
*/
PHP_FUNCTION(git_tag_delete)
{
	zval *repo;
	php_git2_t *_repo;
	char *tag_name = {0};
	int tag_name_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_delete not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &tag_name, &tag_name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_tag_list(tag_names, repo)
*/
PHP_FUNCTION(git_tag_list)
{
	zval *tag_names;
	php_git2_t *_tag_names;
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_list not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &tag_names, &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag_names, php_git2_t*, &tag_names, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_tag_list_match(tag_names, pattern, repo)
*/
PHP_FUNCTION(git_tag_list_match)
{
	zval *tag_names;
	php_git2_t *_tag_names;
	char *pattern = {0};
	int pattern_len;
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_list_match not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsr", &tag_names, &pattern, &pattern_len, &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag_names, php_git2_t*, &tag_names, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_tag_foreach(repo, callback, payload)
*/
PHP_FUNCTION(git_tag_foreach)
{
	zval *repo;
	php_git2_t *_repo;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_foreach not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &repo, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_tag_peel(tag)
*/
PHP_FUNCTION(git_tag_peel)
{
	zval *tag;
	php_git2_t *_tag;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_tag_peel not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tag) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_tag, php_git2_t*, &tag, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

