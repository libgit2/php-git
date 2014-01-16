ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_open, 0, 0, 1)
	ZEND_ARG_INFO(0, index_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_new, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_free, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_owner, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_caps, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_set_caps, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, caps)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_read, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_write, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_path, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_read_tree, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, tree)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_write_tree, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_write_tree_to, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, repo)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_entrycount, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_clear, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_get_byindex, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, n)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_get_bypath, 0, 0, 3)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, stage)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_remove, 0, 0, 3)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, stage)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_remove_directory, 0, 0, 3)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, dir)
	ZEND_ARG_INFO(0, stage)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_add, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, source_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_entry_stage, 0, 0, 1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_add_bypath, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_remove_bypath, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_add_all, 0, 0, 5)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, pathspec)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_remove_all, 0, 0, 4)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, pathspec)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_update_all, 0, 0, 4)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, pathspec)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(1, payload)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_find, 0, 0, 3)
	ZEND_ARG_INFO(0, at_pos)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_add, 0, 0, 4)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, ancestor_entry)
	ZEND_ARG_INFO(0, our_entry)
	ZEND_ARG_INFO(0, their_entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_get, 0, 0, 4)
	ZEND_ARG_INFO(0, our_out)
	ZEND_ARG_INFO(0, their_out)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_remove, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_cleanup, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_has_conflicts, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_iterator_new, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_next, 0, 0, 3)
	ZEND_ARG_INFO(0, our_out)
	ZEND_ARG_INFO(0, their_out)
	ZEND_ARG_INFO(0, iterator)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_conflict_iterator_free, 0, 0, 1)
	ZEND_ARG_INFO(0, iterator)
ZEND_END_ARG_INFO()

/* {{{ proto resource git_index_open(index_path)
*/
PHP_FUNCTION(git_index_open);

/* {{{ proto resource git_index_new()
*/
PHP_FUNCTION(git_index_new);

/* {{{ proto void git_index_free(index)
*/
PHP_FUNCTION(git_index_free);

/* {{{ proto resource git_index_owner(index)
*/
PHP_FUNCTION(git_index_owner);

/* {{{ proto resource git_index_caps(index)
*/
PHP_FUNCTION(git_index_caps);

/* {{{ proto long git_index_set_caps(index, caps)
*/
PHP_FUNCTION(git_index_set_caps);

/* {{{ proto long git_index_read(index, force)
*/
PHP_FUNCTION(git_index_read);

/* {{{ proto resource git_index_write()
*/
PHP_FUNCTION(git_index_write);

/* {{{ proto resource git_index_path(index)
*/
PHP_FUNCTION(git_index_path);

/* {{{ proto long git_index_read_tree(index, tree)
*/
PHP_FUNCTION(git_index_read_tree);

/* {{{ proto resource git_index_write_tree(index)
*/
PHP_FUNCTION(git_index_write_tree);

/* {{{ proto resource git_index_write_tree_to(index, repo)
*/
PHP_FUNCTION(git_index_write_tree_to);

/* {{{ proto resource git_index_entrycount(index)
*/
PHP_FUNCTION(git_index_entrycount);

/* {{{ proto void git_index_clear(index)
*/
PHP_FUNCTION(git_index_clear);

/* {{{ proto resource git_index_get_byindex(index, n)
*/
PHP_FUNCTION(git_index_get_byindex);

/* {{{ proto resource git_index_get_bypath(index, path, stage)
*/
PHP_FUNCTION(git_index_get_bypath);

/* {{{ proto long git_index_remove(index, path, stage)
*/
PHP_FUNCTION(git_index_remove);

/* {{{ proto long git_index_remove_directory(index, dir, stage)
*/
PHP_FUNCTION(git_index_remove_directory);

/* {{{ proto long git_index_add(index, source_entry)
*/
PHP_FUNCTION(git_index_add);

/* {{{ proto long git_index_entry_stage(entry)
*/
PHP_FUNCTION(git_index_entry_stage);

/* {{{ proto long git_index_add_bypath(index, path)
*/
PHP_FUNCTION(git_index_add_bypath);

/* {{{ proto long git_index_remove_bypath(index, path)
*/
PHP_FUNCTION(git_index_remove_bypath);

/* {{{ proto long git_index_add_all(index, pathspec, flags, callback, payload)
*/
PHP_FUNCTION(git_index_add_all);

/* {{{ proto long git_index_remove_all(index, pathspec, callback, payload)
*/
PHP_FUNCTION(git_index_remove_all);

/* {{{ proto long git_index_update_all(index, pathspec, callback, payload)
*/
PHP_FUNCTION(git_index_update_all);

/* {{{ proto long git_index_find(at_pos, index, path)
*/
PHP_FUNCTION(git_index_find);

/* {{{ proto long git_index_conflict_add(index, ancestor_entry, our_entry, their_entry)
*/
PHP_FUNCTION(git_index_conflict_add);

/* {{{ proto resource git_index_conflict_get(our_out, their_out, index, path)
*/
PHP_FUNCTION(git_index_conflict_get);

/* {{{ proto long git_index_conflict_remove(index, path)
*/
PHP_FUNCTION(git_index_conflict_remove);

/* {{{ proto void git_index_conflict_cleanup(index)
*/
PHP_FUNCTION(git_index_conflict_cleanup);

/* {{{ proto long git_index_has_conflicts(index)
*/
PHP_FUNCTION(git_index_has_conflicts);

/* {{{ proto resource git_index_conflict_iterator_new(index)
*/
PHP_FUNCTION(git_index_conflict_iterator_new);

/* {{{ proto resource git_index_conflict_next(our_out, their_out, iterator)
*/
PHP_FUNCTION(git_index_conflict_next);

/* {{{ proto void git_index_conflict_iterator_free(iterator)
*/
PHP_FUNCTION(git_index_conflict_iterator_free);

