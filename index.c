#include "php_git2.h"
#include "php_git2_priv.h"
#include "index.h"

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

/* {{{ proto long git_index_add_all(index, pathspec, flags, callback, payload)
*/
PHP_FUNCTION(git_index_add_all)
{
	zval *index;
	php_git2_t *_index;
	zval *pathspec;
	php_git2_t *_pathspec;
	long flags;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_add_all not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrlr", &index, &pathspec, &flags, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_remove_all(index, pathspec, callback, payload)
*/
PHP_FUNCTION(git_index_remove_all)
{
	zval *index;
	php_git2_t *_index;
	zval *pathspec;
	php_git2_t *_pathspec;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_remove_all not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrr", &index, &pathspec, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_update_all(index, pathspec, callback, payload)
*/
PHP_FUNCTION(git_index_update_all)
{
	zval *index;
	php_git2_t *_index;
	zval *pathspec;
	php_git2_t *_pathspec;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_update_all not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrr", &index, &pathspec, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

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

/* {{{ proto long git_index_conflict_add(index, ancestor_entry, our_entry, their_entry)
*/
PHP_FUNCTION(git_index_conflict_add)
{
//	zval *index;
//	php_git2_t *_index;
//	zval *ancestor_entry;
//	php_git2_t *_ancestor_entry;
//	zval *our_entry;
//	php_git2_t *_our_entry;
//	zval *their_entry;
//	php_git2_t *_their_entry;
//
//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rrrr", &index, &ancestor_entry, &our_entry, &their_entry) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_conflict_get(our_out, their_out, index, path)
*/
PHP_FUNCTION(git_index_conflict_get)
{
	zval *our_out;
	php_git2_t *_our_out;
	zval *their_out;
	php_git2_t *_their_out;
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_get not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrrs", &our_out, &their_out, &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_our_out, php_git2_t*, &our_out, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_conflict_remove(index, path)
*/
PHP_FUNCTION(git_index_conflict_remove)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_remove not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_index_conflict_cleanup(index)
*/
PHP_FUNCTION(git_index_conflict_cleanup)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_cleanup not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

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

/* {{{ proto resource git_index_conflict_iterator_new(index)
*/
PHP_FUNCTION(git_index_conflict_iterator_new)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_iterator_new not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_conflict_next(our_out, their_out, iterator)
*/
PHP_FUNCTION(git_index_conflict_next)
{
	zval *our_out;
	php_git2_t *_our_out;
	zval *their_out;
	php_git2_t *_their_out;
	zval *iterator;
	php_git2_t *_iterator;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_next not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrr", &our_out, &their_out, &iterator) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_our_out, php_git2_t*, &our_out, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_index_conflict_iterator_free(iterator)
*/
PHP_FUNCTION(git_index_conflict_iterator_free)
{
	zval *iterator;
	php_git2_t *_iterator;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_iterator_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iterator) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_iterator, php_git2_t*, &iterator, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

