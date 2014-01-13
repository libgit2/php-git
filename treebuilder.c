#include "php_git2.h"
#include "php_git2_priv.h"
#include "revwalk.h"

static int php_git2_treebuilder_filter_cb(const git_tree_entry *entry, void *payload)
{
	php_git2_t *result;
	zval *param_tree_entry, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	MAKE_STD_ZVAL(param_tree_entry);
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TREE_ENTRY, entry, 0 TSRMLS_CC)) {
		return 0;
	}
	ZVAL_RESOURCE(param_tree_entry, GIT2_RVAL_P(result));
	zend_list_addref(GIT2_RVAL_P(result));
	Z_ADDREF_P(p->payload);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 2, &param_tree_entry, &p->payload)) {
		zval_ptr_dtor(&param_tree_entry);
		zval_ptr_dtor(&p->payload);
		zend_list_delete(result->resource_id);
		retval = 0;
		return 0;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	zend_list_delete(result->resource_id);

	return retval;
}


/* {{{ proto resource git_treebuilder_create([resource $source])
 */
PHP_FUNCTION(git_treebuilder_create)
{
	php_git2_t *result = NULL, *_source = NULL;
	git_treebuilder *out = NULL;
	zval *source = NULL;
	git_tree *tree = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|r", &source) == FAILURE) {
		return;
	}
	if (source != NULL) {
		tree = PHP_GIT2_V(_source, tree);
	}

	ZEND_FETCH_RESOURCE(_source, php_git2_t*, &source, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_treebuilder_create(&out, tree);
	if (php_git2_check_error(error, "git_treebuilder_create" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TREEBUILDER, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


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
		if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TREE_ENTRY, entry, 0 TSRMLS_CC)) {
			RETURN_FALSE;
		}
		ZVAL_RESOURCE(return_value, result->resource_id);
	} else {
		RETURN_FALSE;
	}
}

/* {{{ proto resource git_treebuilder_insert(resource $bld, string $filename, string $id,  $filemode)
 */
PHP_FUNCTION(git_treebuilder_insert)
{
	php_git2_t *result = NULL, *_bld = NULL;
	git_tree_entry *out = NULL;
	zval *bld = NULL;
	char *filename = NULL, *id = NULL;
	int filename_len = 0, id_len = 0, error = 0;
	git_oid __id = {0};
	long filemode = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssl", &bld, &filename, &filename_len, &id, &id_len, &filemode) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__id, id, id_len)) {
		RETURN_FALSE;
	}
	error = git_treebuilder_insert(&out, PHP_GIT2_V(_bld, treebuilder), filename, &__id, filemode);
	if (php_git2_check_error(error, "git_treebuilder_insert" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_TREE_ENTRY, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


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

/* {{{ proto void git_treebuilder_filter(resource $bld,  $filter,  $payload)
 */
PHP_FUNCTION(git_treebuilder_filter)
{
	zval *bld = NULL, *filter = NULL;
	php_git2_t *_bld = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb;
	zval *payload = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &bld, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_bld, php_git2_t*, &bld, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	git_treebuilder_filter(PHP_GIT2_V(_bld, treebuilder), php_git2_treebuilder_filter_cb, cb);
	php_git2_cb_free(cb);
}
/* }}} */


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
	char out[GIT2_OID_HEXSIZE] = {0};

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

