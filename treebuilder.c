#include "php_git2.h"
#include "php_git2_priv.h"
#include "revwalk.h"

/* {{{ proto resource git_treebuilder_create([resource $source])
*/
PHP_FUNCTION(git_treebuilder_create)
{
	zval *source = NULL;
	php_git2_t *_source, *result;
	git_treebuilder *builder;
	git_tree *tree = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|r", &source) == FAILURE) {
		return;
	}

	if (source != NULL) {
		ZEND_FETCH_RESOURCE(_source, php_git2_t*, &source, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
		tree = PHP_GIT2_V(_source, tree);
	}

	error = git_treebuilder_create(&builder, tree);
	if (php_git2_check_error(error, "git_treebuilder_create" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, treebuilder) = builder;
	result->type = PHP_GIT2_TYPE_TREEBUILDER;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto void git_treebuilder_clear(bld)
*/
PHP_FUNCTION(git_treebuilder_clear)
{
	zval *bld;
	php_git2_t *_bld;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &bld) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_treebuilder_clear(PHP_GIT2_V(_bld, treebuilder));
}

/* {{{ proto resource git_treebuilder_entrycount(bld)
*/
PHP_FUNCTION(git_treebuilder_entrycount)
{
	zval *bld;
	php_git2_t *_bld;
	int count;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &bld) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	count = git_treebuilder_entrycount(PHP_GIT2_V(_bld, treebuilder));
	RETURN_LONG(count);
}

/* {{{ proto void git_treebuilder_free(bld)
*/
PHP_FUNCTION(git_treebuilder_free)
{
	zval *bld;
	php_git2_t *_bld;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &bld) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	git_treebuilder_free(PHP_GIT2_V(_bld, treebuilder));
}

/* {{{ proto resource git_treebuilder_get(bld, filename)
*/
PHP_FUNCTION(git_treebuilder_get)
{
	zval *bld;
	php_git2_t *_bld, *result;
	char *filename = {0};
	int filename_len;
	const git_tree_entry *entry = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &bld, &filename, &filename_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	entry = git_treebuilder_get(PHP_GIT2_V(_bld, treebuilder), filename);
	if (entry != NULL) {
		PHP_GIT2_MAKE_RESOURCE(result);
		PHP_GIT2_V(result, tree_entry) = entry;
		result->type = PHP_GIT2_TYPE_TREE_ENTRY;
		result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
		result->should_free_v = 0;

		ZVAL_RESOURCE(return_value, result->resource_id);
	} else {
		RETURN_FALSE;
	}
}

/* {{{ proto resource git_treebuilder_insert(bld, filename, id, filemode)
*/
PHP_FUNCTION(git_treebuilder_insert)
{
	zval *bld;
	php_git2_t *_bld, *result;
	char *filename = {0};
	int filename_len;
	char *id = {0};
	int id_len;
	long filemode;
	const git_tree_entry *entry;
	int error = 0;
	git_oid oid;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssl", &bld, &filename, &filename_len, &id, &id_len, &filemode) == FAILURE) {
		return;
	}

	if (git_oid_fromstrn(&oid, id, id_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_treebuilder_insert(&entry, PHP_GIT2_V(_bld, treebuilder), filename, &oid, filemode);

	if (php_git2_check_error(error, "git_treebuilder_write" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, tree_entry) = entry;
	result->type = PHP_GIT2_TYPE_TREE_ENTRY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto long git_treebuilder_remove(bld, filename)
*/
PHP_FUNCTION(git_treebuilder_remove)
{
	zval *bld;
	php_git2_t *_bld;
	char *filename = {0};
	int filename_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &bld, &filename, &filename_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_treebuilder_remove(PHP_GIT2_V(_bld, treebuilder), filename);

	if (php_git2_check_error(error, "git_treebuilder_remove" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

/* {{{ proto void git_treebuilder_filter(bld, filter, payload)
*/
PHP_FUNCTION(git_treebuilder_filter)
{
	zval *bld;
	php_git2_t *_bld;
	zval *filter;
	php_git2_t *_filter;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_treebuilder_filter not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrz", &bld, &filter, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_treebuilder_write(repo, bld)
*/
PHP_FUNCTION(git_treebuilder_write)
{
	zval *repo;
	php_git2_t *_repo;
	zval *bld;
	php_git2_t *_bld;
	git_oid id;
	int error = 0;
	char out[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &repo, &bld) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_treebuilder_write(&id, PHP_GIT2_V(_repo, repository), PHP_GIT2_V(_bld, treebuilder));
	if (php_git2_check_error(error, "git_treebuilder_write" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);

}

