#include "php_git2.h"
#include "php_git2_priv.h"
#include "commit.h"

static zval* datetime_instantiate(zend_class_entry *pce, zval *object TSRMLS_DC)
{
#if PHP_VERSION_ID <= 50304
        Z_TYPE_P(object) = IS_OBJECT;
        object_init_ex(object, pce);
        Z_SET_REFCOUNT_P(object, 1);
        Z_UNSET_ISREF_P(object);
        return object;
#else
        return php_date_instantiate(pce, object TSRMLS_CC);
#endif
}

/* {{{ proto resource git_commit_lookup(resource $repository, mixed $oid)
*/
PHP_FUNCTION(git_commit_lookup)
{
	zval *repository;
	php_git2_t *git2, *result;
	git_commit *commit;
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

	PHP_GIT2_MAKE_RESOURCE(result);
	error = git_commit_lookup(&commit, PHP_GIT2_V(git2, repository), &id);
	if (php_git2_check_error(error, "git_commit_lookup" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_V(result, commit) = commit;
	result->type = PHP_GIT2_TYPE_COMMIT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}
/* }}} */

/* {{{ proto resource git_commit_author(resource $commit)
*/
PHP_FUNCTION(git_commit_author)
{
	zval *repository;
	php_git2_t *git2;
	zval *commit;
	git_signature *author;
	zval *result, *datetime, *timezone;
	php_timezone_obj *tzobj;
	char time_str[12] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	author = git_commit_author(PHP_GIT2_V(git2, commit));

	MAKE_STD_ZVAL(result);
	array_init(result);

	MAKE_STD_ZVAL(datetime);
	MAKE_STD_ZVAL(timezone);

	datetime_instantiate(php_date_get_date_ce(), datetime TSRMLS_CC);
	snprintf(time_str,12,"%c%ld",'@', author->when.time);

	datetime_instantiate(php_date_get_timezone_ce(), timezone TSRMLS_CC);
	tzobj = (php_timezone_obj *) zend_object_store_get_object(timezone TSRMLS_CC);
	tzobj->initialized = 1;
	tzobj->type = TIMELIB_ZONETYPE_OFFSET;
	tzobj->tzi.utc_offset = -author->when.offset; /* NOTE(chobie): probably this fine */

	php_date_initialize(zend_object_store_get_object(datetime TSRMLS_CC), NULL, 0, NULL, timezone, 0 TSRMLS_CC);

	add_assoc_string_ex(result, ZEND_STRS("name"), author->name, 1);
	add_assoc_string_ex(result, ZEND_STRS("email"), author->email, 1);
	add_assoc_zval_ex(result, ZEND_STRS("time"), datetime);

	zval_ptr_dtor(&timezone);

	RETURN_ZVAL(result, 0, 1);
}
/* }}} */

/* {{{ proto resource git_commit_tree(resource $commit)
*/
PHP_FUNCTION(git_commit_tree)
{
	zval *repository;
	php_git2_t *git2, *result;
	git_commit *commit;
	git_tree *tree;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	PHP_GIT2_MAKE_RESOURCE(result);
	error = git_commit_tree(&tree, PHP_GIT2_V(git2, commit));
	if (php_git2_check_error(error, "git_commit_tree" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_V(result, tree) = tree;
	result->type = PHP_GIT2_TYPE_TREE;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_commit_lookup_prefix(repo, id, len)
*/
PHP_FUNCTION(git_commit_lookup_prefix)
{
	zval *repo;
	php_git2_t *_repo;
	char *id = {0};
	int id_len;
	long len;

	/* TODO(chobie): implement this */
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "git_commit_lookup_prefix not implemented yet");
	return;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rsl", &repo, &id, &id_len, &len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
}

/* {{{ proto resource git_commit_id(commit)
*/
PHP_FUNCTION(git_commit_id)
{
	zval *commit;
	php_git2_t *_commit;
	char out[41] = {0};
	const git_oid *id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	id = git_blob_id(PHP_GIT2_V(_commit, commit));

	git_oid_fmt(out, id);
	RETURN_STRING(out, 1);
}

/* {{{ proto resource git_commit_owner(commit)
*/
PHP_FUNCTION(git_commit_owner)
{
	zval *commit;
	php_git2_t *_commit, *result;
	git_repository *repository;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	PHP_GIT2_MAKE_RESOURCE(result);
	repository = git_commit_owner(PHP_GIT2_V(_commit, commit));

	PHP_GIT2_V(result, repository) = repository;
	result->type = PHP_GIT2_TYPE_REPOSITORY;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_commit_message_encoding(commit)
*/
PHP_FUNCTION(git_commit_message_encoding)
{
	zval *commit;
	php_git2_t *_commit;
	const char *encoding;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	encoding = git_commit_message_encoding(PHP_GIT2_V(_commit, commit));
	RETURN_STRING(encoding, 1);
}

/* {{{ proto resource git_commit_message(commit)
*/
PHP_FUNCTION(git_commit_message)
{
	zval *commit;
	php_git2_t *_commit;
	const char *message;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	message = git_commit_message(PHP_GIT2_V(_commit, commit));
	RETURN_STRING(message, 1);
}

/* {{{ proto resource git_commit_message_raw(commit)
*/
PHP_FUNCTION(git_commit_message_raw)
{
	zval *commit;
	php_git2_t *_commit;
	const char *message;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	message = git_commit_message_raw(PHP_GIT2_V(_commit, commit));
	RETURN_STRING(message, 1);
}

/* {{{ proto resource git_commit_time(commit)
*/
PHP_FUNCTION(git_commit_time)
{
	zval *commit;
	php_git2_t *_commit;
	git_time_t time;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	time = git_commit_time(PHP_GIT2_V(_commit, commit));

	/* NOTE(chobie) should this return as a string? */
	RETURN_LONG(time);
}

/* {{{ proto long git_commit_time_offset(commit)
*/
PHP_FUNCTION(git_commit_time_offset)
{
	zval *commit;
	php_git2_t *_commit;
	int result = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	result = git_commit_time_offset(PHP_GIT2_V(_commit, commit));
	RETURN_LONG(result);
}

/* {{{ proto resource git_commit_committer(commit)
*/
PHP_FUNCTION(git_commit_committer)
{
	zval *commit;
	php_git2_t *git2;
	git_signature *committer;
	zval *result, *datetime, *timezone;
	php_timezone_obj *tzobj;
	char time_str[12] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(git2, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	committer = git_commit_committer(PHP_GIT2_V(git2, commit));

	MAKE_STD_ZVAL(result);
	array_init(result);

	MAKE_STD_ZVAL(datetime);
	MAKE_STD_ZVAL(timezone);

	datetime_instantiate(php_date_get_date_ce(), datetime TSRMLS_CC);
	snprintf(time_str,12,"%c%ld",'@', committer->when.time);

	datetime_instantiate(php_date_get_timezone_ce(), timezone TSRMLS_CC);
	tzobj = (php_timezone_obj *) zend_object_store_get_object(timezone TSRMLS_CC);
	tzobj->initialized = 1;
	tzobj->type = TIMELIB_ZONETYPE_OFFSET;
	tzobj->tzi.utc_offset = -committer->when.offset; /* NOTE(chobie): probably this fine */

	php_date_initialize(zend_object_store_get_object(datetime TSRMLS_CC), NULL, 0, NULL, timezone, 0 TSRMLS_CC);

	add_assoc_string_ex(result, ZEND_STRS("name"), committer->name, 1);
	add_assoc_string_ex(result, ZEND_STRS("email"), committer->email, 1);
	add_assoc_zval_ex(result, ZEND_STRS("time"), datetime);

	zval_ptr_dtor(&timezone);

	RETURN_ZVAL(result, 0, 1);
}

/* {{{ proto resource git_commit_raw_header(commit)
*/
PHP_FUNCTION(git_commit_raw_header)
{
	zval *commit;
	php_git2_t *_commit;
	const char *header;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	header = git_commit_raw_header(PHP_GIT2_V(_commit, commit));

	RETURN_STRING(header, 1);
}

/* {{{ proto resource git_commit_tree_id(commit)
*/
PHP_FUNCTION(git_commit_tree_id)
{
	zval *commit;
	php_git2_t *_commit;
	char out[41] = {0};
	const git_oid *id;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	id = git_commit_tree_id(PHP_GIT2_V(_commit, commit));

	git_oid_fmt(out, id);
	RETURN_STRING(out, 1);
}

/* {{{ proto resource git_commit_parentcount(commit)
*/
PHP_FUNCTION(git_commit_parentcount)
{
	zval *commit;
	php_git2_t *_commit;
	unsigned long count;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"r", &commit) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	count = git_commit_parentcount(PHP_GIT2_V(_commit, commit));
	RETURN_LONG(count);
}

/* {{{ proto resource git_commit_parent(commit, n)
*/
PHP_FUNCTION(git_commit_parent)
{
	zval *commit;
	php_git2_t *_commit, *result;
	git_commit *parent;
	long n = 0;
	int error = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &commit, &n) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	error = git_commit_parent(&parent, PHP_GIT2_V(_commit, commit), n);
	if (php_git2_check_error(error, "git_commit_parent" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, commit) = parent;
	result->type = PHP_GIT2_TYPE_COMMIT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);
}

/* {{{ proto resource git_commit_parent_id(commit, n)
*/
PHP_FUNCTION(git_commit_parent_id)
{
	zval *commit;
	php_git2_t *_commit;
	long n;
	git_oid *oid;
	char out[41] = {0};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &commit, &n) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	oid = git_commit_parent_id(PHP_GIT2_V(_commit, commit), n);
	git_oid_fmt(out, oid);

	RETURN_STRING(out, 1);
}

/* {{{ proto resource git_commit_nth_gen_ancestor(commit, n)
*/
PHP_FUNCTION(git_commit_nth_gen_ancestor)
{
	zval *commit;
	php_git2_t *_commit, *result;
	git_commit *ancestor;
	long n;
	int error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rl", &commit, &n) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(_commit, php_git2_t*, &commit, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	error = git_commit_nth_gen_ancestor(&ancestor, PHP_GIT2_V(_commit, commit), n);
	if (php_git2_check_error(error, "git_commit_nth_gen_ancestor" TSRMLS_CC)) {
		RETURN_FALSE
	}

	PHP_GIT2_MAKE_RESOURCE(result);
	PHP_GIT2_V(result, commit) = ancestor;
	result->type = PHP_GIT2_TYPE_COMMIT;
	result->resource_id = PHP_GIT2_LIST_INSERT(result, git2_resource_handle);
	result->should_free_v = 0;

	ZVAL_RESOURCE(return_value, result->resource_id);

}

static zval* php_git2_read_arrval(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *result = NULL, **element;

	if (zend_hash_find(Z_ARRVAL_P(array), name, name_len, (void**)&element) == SUCCESS) {
		result = *element;
	}

	return result;
}

static void php_git2_array_to_signature(git_signature *signature, zval *author TSRMLS_DC)
{
	zval *name = NULL, *email = NULL, *time = NULL;

	name  = php_git2_read_arrval(author, ZEND_STRS("name") TSRMLS_CC);
	email = php_git2_read_arrval(author, ZEND_STRS("email") TSRMLS_CC);
	time  = php_git2_read_arrval(author, ZEND_STRS("time") TSRMLS_CC);

	signature->name = Z_STRVAL_P(name);
	signature->email = Z_STRVAL_P(email);

	//instanceof_function_ex(const zend_class_entry *instance_ce, const zend_class_entry *ce, zend_bool interfaces_only TSRMLS_DC);
	if (time != NULL &&
		Z_TYPE_P(time) == IS_OBJECT &&
		instanceof_function_ex(Z_OBJCE_P(time), php_date_get_date_ce(), 0 TSRMLS_CC)) {
		php_date_obj *date;

		date = (php_date_obj *)zend_object_store_get_object(time TSRMLS_CC);
		signature->when.time = date->time->sse;
		signature->when.offset = date->time->z;
	}
}

/* {{{ proto resource git_commit_create(
	resource $repo, string $update_ref, array $author, array $committer,
	string $message_encoding, string $message, resource $tree, array $parents)
*/
PHP_FUNCTION(git_commit_create)
{
	zval *repo, *tree, *parents, *committer, *author, **element;
	char *update_ref = {0}, *message_encoding = {0}, *message = {0};
	int update_ref_len, message_encoding_len, message_len, parent_count = 0, error = 0, i;
	php_git2_t *_repo, *_author, *_committer, *_tree;
	git_signature __author, __committer;
	char out[41] = {0};
	git_oid oid;
	const git_commit **__parents = NULL;
	HashPosition pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
			"rsaassra", &repo, &update_ref, &update_ref_len, &author,
			&committer, &message_encoding, &message_encoding_len, &message,
			&message_len, &tree, &parents) == FAILURE) {
		return;
	}

	memset(&__author, '\0', sizeof(git_signature));
	memset(&__committer, '\0', sizeof(git_signature));

	if (committer == NULL || Z_TYPE_P(committer) == IS_NULL) {
		committer = author;
	}

	php_git2_array_to_signature(&__author, author TSRMLS_CC);
	php_git2_array_to_signature(&__committer, committer TSRMLS_CC);

	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	ZEND_FETCH_RESOURCE(_tree, php_git2_t*, &tree, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);

	parent_count = zend_hash_num_elements(Z_ARRVAL_P(parents));
	__parents = emalloc(parent_count * sizeof(void *));
	for(i = 0, zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(parents), &pos);
		zend_hash_get_current_data_ex(Z_ARRVAL_P(parents), (void **)&element, &pos) == SUCCESS;
		zend_hash_move_forward_ex(Z_ARRVAL_P(parents), &pos)
	) {
		git_commit *p = NULL;
		git_oid parent_oid;

		if (Z_TYPE_PP(element) == IS_STRING) {
			error = git_oid_fromstr(&oid, Z_STRVAL_PP(element));
			git_commit_lookup(&p, PHP_GIT2_V(_repo, repository), &oid);
		} else if (Z_TYPE_PP(element) == IS_RESOURCE) {
			php_git2_t *t;
			ZEND_FETCH_RESOURCE(t, php_git2_t*, element, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
			p = PHP_GIT2_V(t, commit);
		}

		__parents[i] = p;
		i++;
	}

	error = git_commit_create(
		&oid,
		PHP_GIT2_V(_repo, repository),
		update_ref,
		&__author,
		&__committer,
		message_encoding,
		message,
		PHP_GIT2_V(_tree, tree),
		parent_count,
		__parents
	);

	efree(__parents);

	if (php_git2_check_error(error, "git_commit_create" TSRMLS_CC)) {
		RETURN_FALSE
	}

	git_oid_fmt(out, &oid);
	RETURN_STRING(out, 1);
}