#include "php_git2.h"
#include "php_git2_priv.h"
#include "reference.h"

static int php_git2_reference_foreach_cb(git_reference *reference, void *payload)
{
	php_git2_t *result;
	zval *param_reference, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_reference);

	php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, reference, 0 TSRMLS_CC);
	zend_list_addref(result->resource_id);
	ZVAL_RESOURCE(param_reference, result->resource_id);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 2, &param_reference, &p->payload)) {
		zval_ptr_dtor(&retval_ptr);
		zend_list_delete(result->resource_id);
		return GIT_EUSER;
	}
	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	zend_list_delete(result->resource_id);

	return retval;
}

static int php_git2_reference_foreach_name_cb(const char *name, void *payload)
{
	php_git2_t *result;
	zval *param_name, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	int i = 0;
	long retval = 0;
	GIT2_TSRMLS_SET(p->tsrm_ls)

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_name);
	ZVAL_STRING(param_name, name, 1);

	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 2, &param_name, &p->payload)) {
		zval_ptr_dtor(&retval_ptr);
		zend_list_delete(result->resource_id);
		return GIT_EUSER;
	}
	retval = Z_LVAL_P(retval_ptr);
	zval_ptr_dtor(&retval_ptr);
	zend_list_delete(result->resource_id);

	return retval;
}


/* {{{ proto resource git_reference_lookup(repo, name)
*/
PHP_FUNCTION(git_reference_lookup)
{
	zval *repo;
	php_git2_t *_repo, *result;
	char *name = {0};
	int name_len;
	git_reference *out;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_reference_lookup(&out, PHP_GIT2_V(_repo, repository), name);
	if (php_git2_check_error(error, "git_reference_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_name_to_id(repo, name)
*/
PHP_FUNCTION(git_reference_name_to_id)
{
	zval *repo;
	php_git2_t *_repo;
	char *name = {0};
	int name_len;
	git_oid id;
	char out[GIT2_OID_HEXSIZE] = {0};
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &name, &name_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_name_to_id(&id, PHP_GIT2_V(_repo, repository), name);
	if (php_git2_check_error(error, "git_reference_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}

	git_oid_fmt(out, &id);
	RETURN_STRING(out, 1);
}

/* {{{ proto resource git_reference_dwim(repo, shorthand)
*/
PHP_FUNCTION(git_reference_dwim)
{
	zval *repo;
	php_git2_t *_repo, *result;
	char *shorthand = {0};
	int shorthand_len;
	git_reference *out;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &shorthand, &shorthand_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_dwim(&out, PHP_GIT2_V(_repo, repository), shorthand);
	if (php_git2_check_error(error, "git_reference_dwim" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_symbolic_create(repo, name, target, force)
*/
PHP_FUNCTION(git_reference_symbolic_create)
{
	zval *repo;
	php_git2_t *_repo, *result;
	char *name = {0};
	int name_len;
	char *target = {0};
	int target_len;
	long force = 0;
	int error;
	git_reference *out;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssl", &repo, &name, &name_len, &target, &target_len, &force) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_symbolic_create(&out, PHP_GIT2_V(_repo, repository), name, target, force);
	if (php_git2_check_error(error, "git_reference_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_create(repo, name, id, force)
*/
PHP_FUNCTION(git_reference_create)
{
	zval *repo;
	php_git2_t *_repo, *result;
	char *name = {0};
	int name_len;
	char *id = {0};
	int id_len;
	long force = 0;
	git_reference *out;
	git_oid oid;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rssl", &repo, &name, &name_len, &id, &id_len, &force) == FAILURE) {
		return;
	}
	if (git_oid_fromstrn(&oid, id, id_len) != GIT_OK) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_create(&out, PHP_GIT2_V(_repo, repository), name, &oid, force);
	if (php_git2_check_error(error, "git_reference_lookup" TSRMLS_CC)) {
		RETURN_FALSE;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_target(ref)
*/
PHP_FUNCTION(git_reference_target)
{
	zval *ref;
	php_git2_t *_ref, *result;
	const git_reference *out = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	out = git_reference_target(PHP_GIT2_V(_ref, reference));
	if (out = NULL) {
		RETURN_FALSE;
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_target_peel(ref)
*/
PHP_FUNCTION(git_reference_target_peel)
{
	zval *ref;
	php_git2_t *_ref;
	git_oid *oid;
	char out[GIT2_OID_HEXSIZE] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	oid = git_reference_target_peel(PHP_GIT2_V(_ref, reference));

	git_oid_fmt(out, oid);
	RETURN_STRING(out, 1);
}

/* {{{ proto resource git_reference_symbolic_target(ref)
*/
PHP_FUNCTION(git_reference_symbolic_target)
{
	zval *ref;
	php_git2_t *_ref;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_reference_symbolic_target not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_reference_type(ref)
*/
PHP_FUNCTION(git_reference_type)
{
	zval *ref;
	php_git2_t *_ref;
	git_ref_t type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	type = git_tree_entry_type(PHP_GIT2_V(_ref, reference));

	RETURN_LONG(type);
}

/* {{{ proto resource git_reference_name(ref)
*/
PHP_FUNCTION(git_reference_name)
{
	zval *ref;
	php_git2_t *_ref;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	name = git_reference_name(PHP_GIT2_V(_ref, reference));

	RETURN_STRING(name, 1);
}

/* {{{ proto resource git_reference_resolve(ref)
*/
PHP_FUNCTION(git_reference_resolve)
{
	zval *ref;
	php_git2_t *_ref, *result;
	git_reference *out;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_reference_resolve(&out, PHP_GIT2_V(_ref, reference));
	if (php_git2_check_error(error, "git_reference_resolve" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_owner(ref)
*/
PHP_FUNCTION(git_reference_owner)
{
	zval *ref;
	php_git2_t *_ref, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);


	PHP_GIT2_MAKE_RESOURCE(result);
	repository = git_reference_owner(PHP_GIT2_V(_ref, reference));

	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_symbolic_set_target(ref, target)
*/
PHP_FUNCTION(git_reference_symbolic_set_target)
{
	zval *ref;
	php_git2_t *_ref, *result;
	char *target = {0};
	int target_len;
	git_reference *out;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &ref, &target, &target_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_symbolic_set_target(&out, PHP_GIT2_V(_ref, reference), target);
	if (php_git2_check_error(error, "git_reference_symbolic_set_target" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_set_target(ref, id)
*/
PHP_FUNCTION(git_reference_set_target)
{
	zval *ref;
	php_git2_t *_ref, *result;
	char *id = {0};
	int id_len;
	git_oid oid;
	int error;
	git_reference *out;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &ref, &id, &id_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&oid, id, id_len) != GIT_OK) {
		return;
	}
	error = git_reference_set_target(&out, PHP_GIT2_V(_ref, reference), &oid);
	if (php_git2_check_error(error, "git_reference_set_target" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_reference_rename(ref, new_name, force)
*/
PHP_FUNCTION(git_reference_rename)
{
	zval *ref;
	php_git2_t *_ref, *result;
	char *new_name = {0};
	int new_name_len;
	long force = 0;
	git_reference *out;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &ref, &new_name, &new_name_len, &force) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_rename(&out, PHP_GIT2_V(_ref, reference), new_name, force);

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, reference) = out;
	result->type = PHP_GIT2_TYPE_REFERENCE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto long git_reference_delete(ref)
*/
PHP_FUNCTION(git_reference_delete)
{
	zval *ref;
	php_git2_t *_ref;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_delete(PHP_GIT2_V(_ref, reference));
	if (php_git2_check_error(error, "git_reference_delete" TSRMLS_CC)) {
		RETURN_FALSE
	}
	zval_ptr_dtor(&ref);
}

/* {{{ proto long git_reference_list(repo)
*/
PHP_FUNCTION(git_reference_list)
{
	zval *repo;
	php_git2_t *_repo;
	git_strarray list;
	zval *result;
	int error, i;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_reference_list(&list, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_reference_list" TSRMLS_CC)) {
		RETURN_FALSE
	}

	php_git2_strarray_to_array(&list, &result TSRMLS_CC);
	git_strarray_free(&list);

	RETURN_ZVAL(result, 0, 1);
}

/* {{{ proto long git_reference_foreach(resource $repo,  $callback,  $payload)
 */
PHP_FUNCTION(git_reference_foreach)
{
	int result = 0, error = 0;
	zval *repo = NULL, *callback = NULL;
	php_git2_t *_repo = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb;
	zval *payload;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &repo, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_reference_foreach(PHP_GIT2_V(_repo, repository), php_git2_reference_foreach_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto long git_reference_foreach_name(resource $repo,  $callback,  $payload)
 */
PHP_FUNCTION(git_reference_foreach_name)
{
	int result = 0, error = 0;
	zval *repo = NULL, *callback = NULL;
	php_git2_t *_repo = NULL;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fcc = empty_fcall_info_cache;
	php_git2_cb_t *cb;
	zval *payload;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rfz", &repo, &fci, &fcc, &payload) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (php_git2_cb_init(&cb, &fci, &fcc, payload TSRMLS_CC)) {
		RETURN_FALSE;
	}
	result = git_reference_foreach_name(PHP_GIT2_V(_repo, repository), php_git2_reference_foreach_name_cb, cb);
	php_git2_cb_free(cb);
	RETURN_LONG(result);
}
/* }}} */

/* {{{ proto void git_reference_free(ref)
*/
PHP_FUNCTION(git_reference_free)
{
	zval *ref;
	php_git2_t *_ref;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (_ref->should_free_v) {
		git_reference_free(PHP_GIT2_V(_ref, reference));
		_ref->should_free_v = 0;
	}
	zval_ptr_dtor(&ref);
}

/* {{{ proto long git_reference_cmp(ref1, ref2)
*/
PHP_FUNCTION(git_reference_cmp)
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

	result = git_reference_cmp(PHP_GIT2_V(g_e1, reference), PHP_GIT2_V(g_e2, reference));
	RETURN_LONG(result);
}

/* {{{ proto resource git_reference_iterator_new(resource $repo)
 */
PHP_FUNCTION(git_reference_iterator_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_reference_iterator *out = NULL;
	zval *repo = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &repo) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_iterator_new(&out, PHP_GIT2_V(_repo, repository));
	if (php_git2_check_error(error, "git_reference_iterator_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_reference_iterator_glob_new(resource $repo, string $glob)
 */
PHP_FUNCTION(git_reference_iterator_glob_new)
{
	php_git2_t *result = NULL, *_repo = NULL;
	git_reference_iterator *out = NULL;
	zval *repo = NULL;
	char *glob = NULL;
	int glob_len = 0, error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rs", &repo, &glob, &glob_len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_iterator_glob_new(&out, PHP_GIT2_V(_repo, repository), glob);
	if (php_git2_check_error(error, "git_reference_iterator_glob_new" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE_ITERATOR, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_reference_next(resource $iter)
 */
PHP_FUNCTION(git_reference_next)
{
	php_git2_t *result = NULL, *_iter = NULL;
	git_reference *out = NULL;
	zval *iter = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_next(&out, PHP_GIT2_V(_iter, reference_iterator));
	if (error == GIT_ITEROVER || php_git2_check_error(error, "git_reference_next" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_REFERENCE, out, 0 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */


/* {{{ proto resource git_reference_next_name(resource $iter)
 */
PHP_FUNCTION(git_reference_next_name)
{
	php_git2_t *result = NULL, *_iter = NULL;
	const char *out = NULL;
	zval *iter = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_next_name(&out, PHP_GIT2_V(_iter, reference_iterator));
	if (php_git2_check_error(error, "git_reference_next_name" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	RETURN_STRING(out, 1);
}
/* }}} */


/* {{{ proto void git_reference_iterator_free(resource $iter)
 */
PHP_FUNCTION(git_reference_iterator_free)
{
	zval *iter = NULL;
	php_git2_t *_iter = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &iter) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_iter, php_git2_t*, &iter, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (GIT2_SHOULD_FREE(_iter)) {
		git_reference_iterator_free(PHP_GIT2_V(_iter, reference_iterator));
		GIT2_SHOULD_FREE(_iter) = 0;
	};
	zval_ptr_dtor(&iter);
}
/* }}} */


/* {{{ proto long git_reference_foreach_glob(repo, glob, callback, payload)
*/
PHP_FUNCTION(git_reference_foreach_glob)
{
	zval *repo;
	php_git2_t *_repo;
	char *glob = {0};
	int glob_len;
	zval *callback;
	php_git2_t *_callback;
	zval *payload;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_reference_foreach_glob not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsrz", &repo, &glob, &glob_len, &callback, &payload) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto long git_reference_has_log(ref)
*/
PHP_FUNCTION(git_reference_has_log)
{
	zval *ref;
	php_git2_t *_ref;
	int has = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	has = git_reference_has_log(PHP_GIT2_V(_ref, reference));

	RETURN_LONG(has);
}

/* {{{ proto long git_reference_is_branch(ref)
*/
PHP_FUNCTION(git_reference_is_branch)
{
	zval *ref;
	php_git2_t *_ref;
	int is_branch = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	is_branch = git_reference_is_branch(PHP_GIT2_V(_ref, reference));

	RETURN_LONG(is_branch);
}

/* {{{ proto long git_reference_is_remote(ref)
*/
PHP_FUNCTION(git_reference_is_remote)
{
	zval *ref;
	php_git2_t *_ref;
	int is_remote = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	is_remote = git_reference_is_remote(PHP_GIT2_V(_ref, reference));
	RETURN_LONG(is_remote);
}

/* {{{ proto long git_reference_is_tag(ref)
*/
PHP_FUNCTION(git_reference_is_tag)
{
	zval *ref;
	php_git2_t *_ref;
	int is_tag = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	is_tag = git_reference_is_tag(PHP_GIT2_V(_ref, reference));
	RETURN_LONG(is_tag);
}

/* {{{ proto resource git_reference_normalize_name(name, flags)
*/
PHP_FUNCTION(git_reference_normalize_name)
{
	char *name = {0};
	int name_len;
	long flags;
	char buffer[512] = {0};
	size_t buffer_sz = 512;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sl", &name, &name_len, &flags) == FAILURE) {
		return;
	}
	error = git_reference_normalize_name(buffer, buffer_sz, name, flags);
	if (php_git2_check_error(error, "git_reference_normalize_name" TSRMLS_CC)) {
		RETURN_FALSE
	}
	RETURN_STRING(buffer, 1);
}

/* {{{ proto resource git_reference_peel(resource $ref,  $type)
 */
PHP_FUNCTION(git_reference_peel)
{
	php_git2_t *result = NULL, *_ref = NULL;
	git_object *out = NULL;
	zval *ref = NULL, *type = NULL;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r<git_otype>", &ref, &type) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_reference_peel(&out, PHP_GIT2_V(_ref, reference), type);
	if (php_git2_check_error(error, "git_reference_peel" TSRMLS_CC)) {
		RETURN_FALSE;
	}
	if (php_git2_make_resource(&result, PHP_GIT2_TYPE_OBJECT, out, 1 TSRMLS_CC)) {
		RETURN_FALSE;
	}
	ZVAL_RESOURCE(return_value, GIT2_RVAL_P(result));
}
/* }}} */

/* {{{ proto long git_reference_is_valid_name(refname)
*/
PHP_FUNCTION(git_reference_is_valid_name)
{
	char *refname = {0};
	int refname_len;
	int acceptable = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &refname, &refname_len) == FAILURE) {
		return;
	}
	acceptable = git_reference_is_valid_name(refname);
	RETURN_BOOL(acceptable);
}

/* {{{ proto resource git_reference_shorthand(ref)
*/
PHP_FUNCTION(git_reference_shorthand)
{
	zval *ref;
	php_git2_t *_ref;
	const char *name;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &ref) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_ref, php_git2_t*, &ref, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	name = git_reference_shorthand(PHP_GIT2_V(_ref, reference));
	RETURN_STRING(name, 1);
}

