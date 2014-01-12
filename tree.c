#include "php_git2.h"
#include "php_git2_priv.h"
#include "tree.h"

typedef struct tree_walk_cb_t {
	zval *payload;
	zend_fcall_info *fci;
	zend_fcall_info_cache *fcc;
	GIT2_TSRMLS_DECL
};

static int tree_walk_cb(const char *root, const git_tree_entry *entry, void *payload)
{
	php_git2_t *result;
	zval *param_root, *param_rsrc, *retval_ptr = NULL;
	struct tree_walk_cb_t *p = (struct tree_walk_cb_t*)payload;
	int i = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_root);
	MAKE_STD_ZVAL(param_rsrc);

	ZVAL_STRING(param_root, root, 1);
	php_git2_make_resource(&result, PHP_GIT2_TYPE_TREE_ENTRY, entry, 0 TSRMLS_CC);
	zend_list_addref(result->resource_id);
	ZVAL_RESOURCE(param_rsrc, result->resource_id);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 3, &param_root, &param_rsrc, &p->payload)) {
		zend_list_delete(result->resource_id);
		return 0;
	}
	zval_ptr_dtor(&retval_ptr);
	zend_list_delete(result->resource_id);

	return 1;
}

static int php_git2_tree_walk_cb_init(struct tree_walk_cb **out, zend_fcall_info *fci, zend_fcall_info_cache *fcc, void *payload TSRMLS_DC)
{
	struct tree_walk_cb_t *cb;

	cb = (struct tree_walk_cb_t*)emalloc(sizeof(struct tree_walk_cb_t));
	if (cb == NULL) {
		return 1;
	}

	cb->payload = payload;
	cb->fci = fci;
	cb->fcc = fcc;
	GIT2_TSRMLS_SET2(cb, TSRMLS_C);

	*out = cb;
	return 0;
}

static void php_git2_tree_walk_cb_free(struct tree_walk_cb *target)
{
	efree(target);
}

/* {{{ proto resource git_tree_entry_byindex(resource $tree, string $name)
*/
PHP_FUNCTION(git_tree_entry_byindex)
{
	zval *tree;
	php_git2_t *git2, *result;
	long index;
	const git_tree_entry *entry;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &tree, &index) == FAILURE) {
		return;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	entry = git_tree_entry_byindex(PHP_GIT2_V(git2, tree), index);

	PHP_GIT2_V(result, tree_entry) = entry;
	result->type = PHP_GIT2_TYPE_TREE_ENTRY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_tree_entry_byoid(resource $tree, string $oid)
*/
PHP_FUNCTION(git_tree_entry_byoid)
{
	zval *tree;
	php_git2_t *git2, *result;
	char *hash;
	int hash_len;
	git_oid id;
	const git_tree_entry *entry;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &tree, &hash, &hash_len) == FAILURE) {
		return;
	}

	if (git_oid_fromstrn(&id, hash, hash_len) != GIT_OK) {
		return;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	entry = git_tree_entry_byoid(PHP_GIT2_V(git2, tree), &id);

	PHP_GIT2_V(result, tree_entry) = entry;
	result->type = PHP_GIT2_TYPE_TREE_ENTRY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}


/* {{{ proto resource git_tree_entry_byname(resource $tree, string $name)
*/
PHP_FUNCTION(git_tree_entry_byname)
{
	zval *tree;
	php_git2_t *git2, *result;
	char *name;
	int name_len;
	const git_tree_entry *entry;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &tree, &name, &name_len) == FAILURE) {
		return;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	entry = git_tree_entry_byname(PHP_GIT2_V(git2, tree), name);


	PHP_GIT2_V(result, tree_entry) = entry;
	result->type = PHP_GIT2_TYPE_TREE_ENTRY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto array git_tree_entry_bypath(resource $tree, string $path)
*/
PHP_FUNCTION(git_tree_entry_bypath)
{
	zval *tree;
	php_git2_t *git2, *result;
	char *path;
	int path_len;
	const git_tree_entry *entry;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &tree, &path, &path_len) == FAILURE) {
		return;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_tree_entry_bypath(&entry, PHP_GIT2_V(git2, tree), path);

	PHP_GIT2_V(result, tree_entry) = entry;
	result->type = PHP_GIT2_TYPE_TREE_ENTRY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto string git_tree_entry_id(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_id)
{
	zval *tree_entry;
	php_git2_t *git2;
	char out[GIT2_OID_HEXSIZE] = {0};
	const git_oid *id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree_entry) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree_entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	id = git_tree_entry_id(PHP_GIT2_V(git2, tree_entry));
	git_oid_fmt(out, id);
	RETURN_STRING(out, 1);
}


/* {{{ proto long git_tree_entry_type(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_type)
{
	zval *tree;
	php_git2_t *git2;
	git_otype type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	type = git_tree_entry_type(PHP_GIT2_V(git2, tree));
	RETURN_LONG(type);
}

/* {{{ proto string git_tree_entry_name(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_name)
{
	zval *tree_entry;
	php_git2_t *git2;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree_entry) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree_entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	name = git_tree_entry_name(PHP_GIT2_V(git2, tree_entry));
	RETURN_STRING(name, 1);
}

/* {{{ proto long git_tree_entry_count(resource $tree)
*/
PHP_FUNCTION(git_tree_entrycount)
{
	zval *tree;
	php_git2_t *git2;
	size_t count;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	count = git_tree_entrycount(PHP_GIT2_V(git2, tree));
	RETURN_LONG(count);
}

/* {{{ proto long git_tree_entry_filemode(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_filemode)
{
	zval *tree_entry;
	php_git2_t *git2;
	git_filemode_t filemode;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree_entry) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree_entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	filemode = git_tree_entry_filemode(PHP_GIT2_V(git2, tree_entry));
	RETURN_LONG(filemode);
}

/* {{{ proto long git_tree_entry_filemode_raw(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_filemode_raw)
{
	zval *tree_entry;
	php_git2_t *git2;
	git_filemode_t filemode;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree_entry) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree_entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	filemode = git_tree_entry_filemode_raw(PHP_GIT2_V(git2, tree_entry));
	RETURN_LONG(filemode);
}

/* {{{ proto bool git_tree_entry_cmp(resource $e1, resource $e2)
*/
PHP_FUNCTION(git_tree_entry_cmp)
{
	zval *e1, *e2;
	php_git2_t *g_e1, *g_e2;
	int result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &e1, &e2) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(g_e1, php_git2_t*, &e1, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(g_e2, php_git2_t*, &e2, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tree_entry_cmp(PHP_GIT2_V(g_e1, tree_entry), PHP_GIT2_V(g_e2, tree_entry));
	RETURN_LONG(result);
}


/* {{{ proto void git_tree_free(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_free)
{
	zval *tree;
	php_git2_t *git2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git2->should_free_v) {
		git_tree_free(PHP_GIT2_V(git2, tree));
		git2->should_free_v = 0;
	}

	zval_ptr_dtor(&tree);
}

/* {{{ proto void git_tree_entry_free(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_free)
{
	zval *tree_entry;
	php_git2_t *git2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree_entry) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree_entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git2->should_free_v) {
		git_tree_entry_free(PHP_GIT2_V(git2, tree_entry));
		git2->should_free_v = 0;
	}

	zval_ptr_dtor(&tree_entry);
}

/* {{{ proto resource git_tree_entry_dup(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_entry_dup)
{
	zval *tree_entry;
	php_git2_t *git2, *result;
	git_tree_entry *entry;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree_entry) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree_entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	entry = git_tree_entry_dup(PHP_GIT2_V(git2, tree_entry));

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, tree_entry) = entry;
	result->type = PHP_GIT2_TYPE_TREE_ENTRY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto string git_tree_id(resource $tree_entry)
*/
PHP_FUNCTION(git_tree_id)
{
	zval *tree;
	php_git2_t *git2;
	char out[GIT2_OID_HEXSIZE] = {0};
	const git_oid *id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	id = git_tree_id(PHP_GIT2_V(git2, tree));
	git_oid_fmt(out, id);
	RETURN_STRING(out, 1);
}


/* {{{ proto resource git_tree_lookup(resource $repository, mixed $oid)
*/
PHP_FUNCTION(git_tree_lookup)
{
	zval *repository;
	php_git2_t *git2, *result;
	git_tree *tree;
	char *hash;
	int hash_len;
	int error;
	git_oid id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repository, &hash, &hash_len) == FAILURE) {
		return;
	}

	if (git_oid_fromstrn(&id, hash, hash_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &repository, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_tree_lookup(&tree, PHP_GIT2_V(git2, repository), &id);
	if (php_git2_check_error(error, "git_commit_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, tree) = tree;
	result->type = PHP_GIT2_TYPE_TREE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto resource git_tree_owner(resource $tree)
 */
PHP_FUNCTION(git_tree_owner)
{
	git_repository  *result = NULL;
	zval *tree = NULL;
	php_git2_t *_tree = NULL, *__result = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &tree) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_tree, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_tree_owner(PHP_GIT2_V(_tree, tree));
	if (php_git2_make_resource(&__result, PHP_GIT2_TYPE_TREE, result, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(__result));
}
/* }}} */


/* {{{ proto void git_tree_walk(resource $tree, long $mode, Callable $callback, mixed &$payload)
*/
PHP_FUNCTION(git_tree_walk)
{
	zval *tree, *payload;
	php_git2_t *git2, *result;
	zend_fcall_info fci       = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	long mode = GIT_TREEWALK_PRE;
	struct tree_walk_cb_t *cb;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rlf|z", &tree, &mode, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_tree_walk_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	error = git_tree_walk(PHP_GIT2_V(git2, tree), mode, tree_walk_cb, cb);
	php_git2_tree_walk_cb_free(cb);
	if (php_git2_check_error(error, "git_tree_walk" TSRMLS_CC)) {
		RETURN_FALSE
	}

}
/* }}} */
