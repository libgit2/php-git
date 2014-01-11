#include "php_git2.h"
#include "php_git2_priv.h"
#include "index.h"
/* {{{ proto resource git_index_open(index_path)
*/
PHP_FUNCTION(git_index_open)
{
	char *index_path = {0};
	int index_path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_open not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &index_path, &index_path_len) == FAILURE) {
		return;
	}
}

/* {{{ proto resource git_index_new()
*/
PHP_FUNCTION(git_index_new)
{
	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_new not implemented yet");
	return;
}

/* {{{ proto void git_index_free(index)
*/
PHP_FUNCTION(git_index_free)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_free not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_owner(index)
*/
PHP_FUNCTION(git_index_owner)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_owner not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_caps(index)
*/
PHP_FUNCTION(git_index_caps)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_caps not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_set_caps(index, caps)
*/
PHP_FUNCTION(git_index_set_caps)
{
	zval *index;
	php_git2_t *_index;
	long caps;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_set_caps not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &index, &caps) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_read(index, force)
*/
PHP_FUNCTION(git_index_read)
{
	zval *index;
	php_git2_t *_index;
	long force;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_read not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &index, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_write()
*/
PHP_FUNCTION(git_index_write)
{
	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_write not implemented yet");
	return;
}

/* {{{ proto resource git_index_path(index)
*/
PHP_FUNCTION(git_index_path)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_path not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_read_tree(index, tree)
*/
PHP_FUNCTION(git_index_read_tree)
{
	zval *index;
	php_git2_t *_index;
	zval *tree;
	php_git2_t *_tree;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_read_tree not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &index, &tree) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_write_tree(index)
*/
PHP_FUNCTION(git_index_write_tree)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_write_tree not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_write_tree_to(index, repo)
*/
PHP_FUNCTION(git_index_write_tree_to)
{
	zval *index;
	php_git2_t *_index;
	zval *repo;
	php_git2_t *_repo;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_write_tree_to not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &index, &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_entrycount(index)
*/
PHP_FUNCTION(git_index_entrycount)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_entrycount not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto void git_index_clear(index)
*/
PHP_FUNCTION(git_index_clear)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_clear not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_get_byindex(index, n)
*/
PHP_FUNCTION(git_index_get_byindex)
{
	zval *index;
	php_git2_t *_index;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_get_byindex not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"r", &index, &n) == FAILURE) {
//		return;
//	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_index_get_bypath(index, path, stage)
*/
PHP_FUNCTION(git_index_get_bypath)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	long stage;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_get_bypath not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &index, &path, &path_len, &stage) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_remove(index, path, stage)
*/
PHP_FUNCTION(git_index_remove)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;
	long stage;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_remove not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &index, &path, &path_len, &stage) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_remove_directory(index, dir, stage)
*/
PHP_FUNCTION(git_index_remove_directory)
{
	zval *index;
	php_git2_t *_index;
	char *dir = {0};
	int dir_len;
	long stage;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_remove_directory not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &index, &dir, &dir_len, &stage) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_add(index, source_entry)
*/
PHP_FUNCTION(git_index_add)
{
	zval *index;
	php_git2_t *_index;
	zval *source_entry;
	php_git2_t *_source_entry;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_add not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rr", &index, &source_entry) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_entry_stage(entry)
*/
PHP_FUNCTION(git_index_entry_stage)
{
	zval *entry;
	php_git2_t *_entry;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_entry_stage not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &entry) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_entry, php_git2_t*, &entry, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_add_bypath(index, path)
*/
PHP_FUNCTION(git_index_add_bypath)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_add_bypath not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_remove_bypath(index, path)
*/
PHP_FUNCTION(git_index_remove_bypath)
{
	zval *index;
	php_git2_t *_index;
	char *path = {0};
	int path_len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_remove_bypath not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &index, &path, &path_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
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

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_find not implemented yet");
	return;

//	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
//		"rs", &at_pos, &index, &path, &path_len) == FAILURE) {
//		return;
//	}
//	ZEND_FETCH_RESOURCE(_at_pos, php_git2_t*, &at_pos, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_index_conflict_add(index, ancestor_entry, our_entry, their_entry)
*/
PHP_FUNCTION(git_index_conflict_add)
{
	zval *index;
	php_git2_t *_index;
	zval *ancestor_entry;
	php_git2_t *_ancestor_entry;
	zval *our_entry;
	php_git2_t *_our_entry;
	zval *their_entry;
	php_git2_t *_their_entry;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_conflict_add not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rrrr", &index, &ancestor_entry, &our_entry, &their_entry) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
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

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_index_has_conflicts not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &index) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_index, php_git2_t*, &index, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
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

