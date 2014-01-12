#include "php_git2.h"
#include "php_git2_priv.h"
#include "index.h"

static int php_git2_index_matched_path_cb(const char *path, const char *matched_pathspec, void *payload)
{
	php_git2_t *result;
	zval *param_path, *param_matched_pathspec, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_path);
	MAKE_STD_ZVAL(param_matched_pathspec);
	ZVAL_STRING(param_path, path, 1);
	ZVAL_STRING(param_matched_pathspec, matched_pathspec, 1);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 3, &param_path, &param_matched_pathspec, &p->payload)) {
		zval_ptr_dtor(&param_path);
		zval_ptr_dtor(&param_matched_pathspec);
		zval_ptr_dtor(&p->payload);
		return 0;
	}

	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	return retval;
}


static int php_git2_array_to_index_entry(git_index_entry *entry, zval *array TSRMLS_DC)
{
	zval *ctime, *mtime, *oid;
	memset(entry, '\0', sizeof(git_index_entry));

	ctime = php_git2_read_arrval(array, ZEND_STRS("ctime") TSRMLS_CC);
	mtime = php_git2_read_arrval(array, ZEND_STRS("mtime") TSRMLS_CC);

	oid = php_git2_read_arrval(array, ZEND_STRS("oid") TSRMLS_CC);
	if (git_oid_fromstrn(&entry->oid, Z_STRVAL_P(oid), Z_STRLEN_P(oid)) != GIT_OK) {
		return 0;
	}

	entry->ctime.seconds = php_git2_read_arrval_long(ctime, ZEND_STRS("seconds") TSRMLS_CC);
	entry->ctime.nanoseconds = php_git2_read_arrval_long(ctime, ZEND_STRS("nanoseconds") TSRMLS_CC);
	entry->mtime.seconds = php_git2_read_arrval_long(mtime, ZEND_STRS("seconds") TSRMLS_CC);
	entry->mtime.nanoseconds = php_git2_read_arrval_long(mtime, ZEND_STRS("nanoseconds") TSRMLS_CC);
	entry->dev = php_git2_read_arrval_long(array, ZEND_STRS("dev") TSRMLS_CC);
	entry->ino = php_git2_read_arrval_long(array, ZEND_STRS("ino") TSRMLS_CC);
	entry->mode = php_git2_read_arrval_long(array, ZEND_STRS("mode") TSRMLS_CC);
	entry->uid = php_git2_read_arrval_long(array, ZEND_STRS("uid") TSRMLS_CC);
	entry->gid = php_git2_read_arrval_long(array, ZEND_STRS("gid") TSRMLS_CC);
	entry->file_size = php_git2_read_arrval_long(array, ZEND_STRS("file_size") TSRMLS_CC);
	entry->flags = php_git2_read_arrval_long(array, ZEND_STRS("flags") TSRMLS_CC);
	entry->flags_extended = php_git2_read_arrval_long(array, ZEND_STRS("flags_extended") TSRMLS_CC);
	entry->path = php_git2_read_arrval_string(array, ZEND_STRS("path") TSRMLS_CC);

	return 1;
}

static void php_git2_index_entry_to_array(const git_index_entry *entry, zval **result TSRMLS_DC)
{
	zval *tmp, *ctime, *mtime;
	char buf[GIT2_OID_HEXSIZE] = {0};

	MAKE_STD_ZVAL(tmp);
	MAKE_STD_ZVAL(ctime);
	MAKE_STD_ZVAL(mtime);
	array_init(tmp);
	array_init(ctime);
	array_init(mtime);

	git_oid_fmt(buf, &entry->oid);

	add_assoc_long_ex(ctime, ZEND_STRS("seconds"), entry->ctime.seconds);
	add_assoc_long_ex(ctime, ZEND_STRS("nanoseconds"), entry->ctime.nanoseconds);
	add_assoc_long_ex(mtime, ZEND_STRS("seconds"), entry->mtime.seconds);
	add_assoc_long_ex(mtime, ZEND_STRS("nanoseconds"), entry->mtime.nanoseconds);

	add_assoc_zval_ex(tmp, ZEND_STRS("ctime"), ctime);
	add_assoc_zval_ex(tmp, ZEND_STRS("mtime"), mtime);

	add_assoc_long_ex(tmp, ZEND_STRS("dev"), entry->dev);
	add_assoc_long_ex(tmp, ZEND_STRS("ino"), entry->ino);
	add_assoc_long_ex(tmp, ZEND_STRS("mode"), entry->mode);
	add_assoc_long_ex(tmp, ZEND_STRS("uid"), entry->uid);
	add_assoc_long_ex(tmp, ZEND_STRS("gid"), entry->gid);
	add_assoc_long_ex(tmp, ZEND_STRS("file_size"), entry->file_size);
	add_assoc_string_ex(tmp, ZEND_STRS("oid"), buf, 1);
	add_assoc_long_ex(tmp, ZEND_STRS("flags"), entry->flags);
	add_assoc_long_ex(tmp, ZEND_STRS("flags_extended"), entry->flags_extended);
	add_assoc_string_ex(tmp, ZEND_STRS("path"), entry->path, 1);

	*result = tmp;
}

/* {{{ proto resource git_index_open(index_path)
*/
PHP_FUNCTION(git_index_open)
{
	char *index_path = {0};
	int index_path_len;
	git_index *index;
	php_git2_t *result;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &index_path, &index_path_len) == FAILURE) {
		return;
	}
	error = git_index_open(&index, index_path);
	if (php_git2_check_error(error, "git_index_open" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, index) = index;
	result->type = PHP_GIT2_TYPE_INDEX;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_index_new()
*/
PHP_FUNCTION(git_index_new)
{
	git_index *index;
	php_git2_t *result;
	int error = 0;

	error = git_index_new(&index);
	if (php_git2_check_error(error, "git_index_new" TSRMLS_CC)) {
		RETURN_FALSE
	}
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, index) = index;
	result->type = PHP_GIT2_TYPE_INDEX;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 1;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto void git_index_free(index)
*/
PHP_FUNCTION(git_index_free)
{
	zval *index;
	php_git2_t *_index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_index->should_free_v) {
		git_index_free(PHP_GIT2_V(_index, index));
		_index->should_free_v = 0;
	}
	zval_ptr_dtor(&index);
}

/* {{{ proto resource git_index_owner(index)
*/
PHP_FUNCTION(git_index_owner)
{
	zval *index;
	php_git2_t *_index, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	repository = git_index_owner(PHP_GIT2_V(_index, index));
	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_index_caps(index)
*/
PHP_FUNCTION(git_index_caps)
{
	zval *index;
	php_git2_t *_index;
	unsigned int caps;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	caps = git_index_caps(PHP_GIT2_V(_index, index));
	RETURN_LONG(caps);
}

/* {{{ proto long git_index_set_caps(index, caps)
*/
PHP_FUNCTION(git_index_set_caps)
{
	zval *index;
	php_git2_t *_index;
	long caps;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &index, &caps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_set_caps(PHP_GIT2_V(_index, index), caps);
	RETURN_LONG(error);
}

/* {{{ proto long git_index_read(index, force)
*/
PHP_FUNCTION(git_index_read)
{
	zval *index;
	php_git2_t *_index;
	long force;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &index, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_read(PHP_GIT2_V(_index, index), force);
	if (php_git2_check_error(error, "git_index_read" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto resource git_index_write()
*/
PHP_FUNCTION(git_index_write)
{
	zval *index;
	php_git2_t *_index;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_write(PHP_GIT2_V(_index, index));
	if (php_git2_check_error(error, "git_index_write" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto resource git_index_path(index)
*/
PHP_FUNCTION(git_index_path)
{
	zval *index;
	php_git2_t *_index;
	const char *path;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	path = git_index_path(PHP_GIT2_V(_index, index));
	RETURN_STRING(path, 1);
}

/* {{{ proto long git_index_read_tree(index, tree)
*/
PHP_FUNCTION(git_index_read_tree)
{
	zval *index;
	php_git2_t *_index;
	zval *tree;
	php_git2_t *_tree;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &index, &tree) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_tree, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_read_tree(PHP_GIT2_V(_index, index), PHP_GIT2_V(_tree, tree));
	if (php_git2_check_error(error, "git_index_read_tree" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto resource git_index_write_tree(index)
*/
PHP_FUNCTION(git_index_write_tree)
{
	zval *index;
	php_git2_t *_index;
	int error = 0;
	git_oid id;
	char out[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_write_tree(&id, PHP_GIT2_V(_index, index));
	if (php_git2_check_error(error, "git_index_write_tree" TSRMLS_CC)) {
		RETURN_FALSE
	}
	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);
}

/* {{{ proto resource git_index_write_tree_to(index, repo)
*/
PHP_FUNCTION(git_index_write_tree_to)
{
	zval *index;
	php_git2_t *_index;
	zval *repo;
	php_git2_t *_repo;
	git_oid id;
	char out[GIT2_OID_HEXSIZE]= {0};
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &index, &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_write_tree_to(&id, PHP_GIT2_V(_index, index), PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_index_write_tree_to" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto resource git_index_entrycount(index)
*/
PHP_FUNCTION(git_index_entrycount)
{
	zval *index;
	php_git2_t *_index;
	size_t count;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	count = git_index_entrycount(PHP_GIT2_V(_index, index));
	RETURN_LONG(count);
}

/* {{{ proto void git_index_clear(index)
*/
PHP_FUNCTION(git_index_clear)
{
	zval *index;
	php_git2_t *_index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_index_clear(PHP_GIT2_V(_index, index));
}

/* {{{ proto resource git_index_get_byindex(index, n)
*/
PHP_FUNCTION(git_index_get_byindex)
{
	zval *index;
	php_git2_t *_index;
	long n;
	const git_index_entry *entry;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &index, &n) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	entry = git_index_get_byindex(PHP_GIT2_V(_index, index), n);
	if (entry == NULL) {
		RETURN_FALSE;
	}
	php_git2_index_entry_to_array(entry, &result TSRMLS_CC);
	RETURN_ZVAL(result, 0, 1);
}

/* {{{ proto resource git_index_get_bypath(index, path, stage)
*/
PHP_FUNCTION(git_index_get_bypath)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	long stage = 0;
	const git_index_entry *entry;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs|l", &index, &path, &path_len, &stage) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	entry = git_index_get_bypath(PHP_GIT2_V(_index, index), path, stage);
	if (entry == NULL) {
		RETURN_FALSE;
	}
	php_git2_index_entry_to_array(entry, &result TSRMLS_CC);
	RETURN_ZVAL(result, 0, 1);
}

/* {{{ proto long git_index_remove(index, path, stage)
*/
PHP_FUNCTION(git_index_remove)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	long stage = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &index, &path, &path_len, &stage) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_remove(PHP_GIT2_V(_index, index), path, stage);
	if (php_git2_check_error(error, "git_index_remove" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}

/* {{{ proto long git_index_remove_directory(index, dir, stage)
*/
PHP_FUNCTION(git_index_remove_directory)
{
	zval *index;
	php_git2_t *_index;
	char *dir = {0};
	int dir_len;
	long stage = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &index, &dir, &dir_len, &stage) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_remove_directory(PHP_GIT2_V(_index, index), dir, stage);
	if (php_git2_check_error(error, "git_index_remove_directory" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}

/* {{{ proto long git_index_add(index, source_entry)
*/
PHP_FUNCTION(git_index_add)
{
	zval *index;
	php_git2_t *_index;
	zval *source_entry;
	int error = 0;
	git_index_entry entry;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ra", &index, &source_entry) == FAILURE) {
		return;
	}
	if (!php_git2_array_to_index_entry(&entry, source_entry TSRMLS_CC)) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_add(PHP_GIT2_V(_index, index), &entry);
	if (php_git2_check_error(error, "git_index_add" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_index_entry_stage(entry)
*/
PHP_FUNCTION(git_index_entry_stage)
{
	zval *source;
	git_index_entry entry;
	int result = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"a", &source) == FAILURE) {
		return;
	}
	if (!php_git2_array_to_index_entry(&entry, source TSRMLS_CC)) {
		return;
	}
	result = git_index_entry_stage(&entry);
	RETURN_LONG(result);
}

/* {{{ proto long git_index_add_bypath(index, path)
*/
PHP_FUNCTION(git_index_add_bypath)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_add_bypath(PHP_GIT2_V(_index, index), path);
	if (php_git2_check_error(error, "git_index_add_bypath" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_index_remove_bypath(index, path)
*/
PHP_FUNCTION(git_index_remove_bypath)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_remove_bypath(PHP_GIT2_V(_index, index), path);
	if (php_git2_check_error(error, "git_index_remove_bypath" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_TRUE;
}

/* {{{ proto long git_index_add_all(resource $index, array $pathspec, long $flags, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_index_add_all)
{
	int result = 0, error = 0;
	zval *index = NULL, *pathspec = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_index = NULL;
	git_strarray _pathspec = {0};
	long flags = 0;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"ralfz", &index, &pathspec, &flags, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_strarray(&_pathspec, pathspec TSRMLS_CC);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_index_add_all(PHP_GIT2_V(_index, index), pathspec, flags, php_git2_index_matched_path_cb, cb);
	php_git2_cb_free(cb);
	php_git2_strarray_free(&_pathspec);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_index_remove_all(resource $index, array $pathspec, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_index_remove_all)
{
	int result = 0, error = 0;
	zval *index = NULL, *pathspec = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_index = NULL;
	git_strarray _pathspec = {0};
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rafz", &index, &pathspec, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_strarray(&_pathspec, pathspec TSRMLS_CC);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_index_remove_all(PHP_GIT2_V(_index, index), pathspec, php_git2_index_matched_path_cb, cb);
	php_git2_cb_free(cb);
	php_git2_strarray_free(&_pathspec);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_index_update_all(resource $index, array $pathspec, Callable $callback,  $payload)
 */
PHP_FUNCTION(git_index_update_all)
{
	int result = 0, error = 0;
	zval *index = NULL, *pathspec = NULL, *callback = NULL, *payload = NULL;
	php_git2_t *_index = NULL;
	git_strarray _pathspec = {0};
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rafz", &index, &pathspec, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	php_git2_array_to_strarray(&_pathspec, pathspec TSRMLS_CC);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_index_update_all(PHP_GIT2_V(_index, index), pathspec, php_git2_index_matched_path_cb, cb);
	php_git2_cb_free(cb);
	php_git2_strarray_free(&_pathspec);
	RETURN_LONG(result);
}
/* }}} */


/* {{{ proto long git_index_find(at_pos, index, path)
*/
PHP_FUNCTION(git_index_find)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	long at_pos;
	int result = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"lrs", &at_pos, &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_index_find(at_pos, PHP_GIT2_V(_index, index), path);
	RETURN_LONG(result);
}

/* {{{ proto long git_index_conflict_add(resource $index, $ancestor_entry, $our_entry, $their_entry)
 */
PHP_FUNCTION(git_index_conflict_add)
{
	int result = 0, error = 0;
	zval *index = NULL, *ancestor_entry = NULL, *our_entry = NULL, *their_entry = NULL;
	php_git2_t *_index = NULL;
	git_index_entry ancestor = {0}, our = {0}, their = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"raaa", &index, &ancestor_entry, &our_entry, &their_entry) == FAILURE) {
		return;
	}

	php_git2_array_to_index_entry(&ancestor, ancestor_entry TSRMLS_CC);
	php_git2_array_to_index_entry(&our, our_entry TSRMLS_CC);
	php_git2_array_to_index_entry(&their, their_entry TSRMLS_CC);

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_index_conflict_add(PHP_GIT2_V(_index, index), &ancestor, &our, &their);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto resource git_index_conflict_get(resource $index, string $path)
 */
PHP_FUNCTION(git_index_conflict_get)
{
	php_git2_t *result = NULL, *_index = NULL;
	git_index_entry *ancestor_out = NULL, *our_out = NULL, *their_out = NULL;
	zval *index = NULL, *ancestor, *our, *their, *container;
	char *path = NULL;
	int path_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_conflict_get(&ancestor_out, &our_out, &their_out, PHP_GIT2_V(_index, index), path);
	if (php_git2_check_error(error, "git_index_conflict_get" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	php_git2_index_entry_to_array(ancestor_out, &ancestor TSRMLS_CC);
	php_git2_index_entry_to_array(our_out, &our TSRMLS_CC);
	php_git2_index_entry_to_array(their_out, &their TSRMLS_CC);
	MAKE_STD_ZVAL(container);
	array_init(container);
	add_next_index_zval(container, ancestor);
	add_next_index_zval(container, our);
	add_next_index_zval(container, their);
	RETURN_ZVAL(container, 0, 1);
}
/* }}} */

/* {{{ proto long git_index_conflict_remove(resource $index, string $path)
 */
PHP_FUNCTION(git_index_conflict_remove)
{
	int result = 0, path_len = 0, error = 0;
	zval *index = NULL;
	php_git2_t *_index = NULL;
	char *path = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_index_conflict_remove(PHP_GIT2_V(_index, index), path);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_index_conflict_cleanup(resource $index)
 */
PHP_FUNCTION(git_index_conflict_cleanup)
{
	zval *index = NULL;
	php_git2_t *_index = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	git_index_conflict_cleanup(PHP_GIT2_V(_index, index));
}
/* }}} */

/* {{{ proto long git_index_has_conflicts(index)
*/
PHP_FUNCTION(git_index_has_conflicts)
{
	zval *index;
	php_git2_t *_index;
	int conflict = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	conflict = git_index_has_conflicts(PHP_GIT2_V(_index, index));
	RETURN_LONG(conflict);
}

/* {{{ proto resource git_index_conflict_iterator_new(resource $index)
 */
PHP_FUNCTION(git_index_conflict_iterator_new)
{
	php_git2_t *result = NULL, *_index = NULL;
	git_index_conflict_iterator *iterator_out = NULL;
	zval *index = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_conflict_iterator_new(&iterator_out, PHP_GIT2_V(_index, index));
	if (php_git2_check_error(error, "git_index_conflict_iterator_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_INDEX_CONFLICT_ITERATOR, iterator_out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto resource git_index_conflict_next(resource $iterator)
 */
PHP_FUNCTION(git_index_conflict_next)
{
	php_git2_t *result = NULL, *_iterator = NULL;
	git_index_entry *ancestor_out = NULL, *our_out = NULL, *their_out = NULL;
	zval *iterator = NULL, *ancestor, *our, *their, *container;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iterator) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iterator, php_git2_t*, &iterator, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_index_conflict_next(&ancestor_out, &our_out, &their_out, PHP_GIT2_V(_iterator, index_conflict_iterator));
	if (php_git2_check_error(error, "git_index_conflict_next" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	php_git2_index_entry_to_array(ancestor_out, &ancestor TSRMLS_CC);
	php_git2_index_entry_to_array(our_out, &our TSRMLS_CC);
	php_git2_index_entry_to_array(their_out, &their TSRMLS_CC);
	MAKE_STD_ZVAL(container);
	array_init(container);
	add_next_index_zval(container, ancestor);
	add_next_index_zval(container, our);
	add_next_index_zval(container, their);
	RETURN_ZVAL(container, 0, 1);

}
/* }}} */

/* {{{ proto void git_index_conflict_iterator_free(resource $iterator)
 */
PHP_FUNCTION(git_index_conflict_iterator_free)
{
	zval *iterator = NULL;
	php_git2_t *_iterator = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iterator) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iterator, php_git2_t*, &iterator, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_iterator)) {
		git_index_conflict_iterator_free(PHP_GIT2_V(_iterator, index_conflict_iterator));
		GIT2_SHOULD_FREE(_iterator) = 0;
	};
	zval_ptr_dtor(&iterator);
}
/* }}} */
