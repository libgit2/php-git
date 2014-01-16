#include "php_git2.h"
#include "php_git2_priv.h"
#include "helper.h"

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

int php_git2_check_error(int error_code, const char *action TSRMLS_DC)
{
	int result = 0;
	const git_error * error;
	if (!error_code) {
		return result;
	}

	error = giterr_last();
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "WARNING %d %s - %s",
		error_code, action, (error && error->message) ? error->message : "???");

	result = 1;
	return result;
}


zval* php_git2_read_arrval(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *result = NULL, **element;

	if (zend_hash_find(Z_ARRVAL_P(array), name, name_len, (void**)&element) == SUCCESS) {
		result = *element;
	}

	return result;
}

long php_git2_read_arrval_long(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *tmp;
	long result = 0;

	tmp = php_git2_read_arrval(array, name, name_len TSRMLS_CC);
	if (tmp) {
		result = Z_LVAL_P(tmp);
	}

	return result;
}

const char* php_git2_read_arrval_string(zval *array, char *name, size_t name_len TSRMLS_DC)
{
	zval *tmp;
	const char *result = NULL;

	tmp = php_git2_read_arrval(array, name, name_len TSRMLS_CC);
	if (tmp) {
		result = Z_STRVAL_P(tmp);
	}

	return result;
}

void php_git2_array_to_signature(git_signature *signature, zval *author TSRMLS_DC)
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

void php_git2_signature_to_array(const git_signature *signature, zval **out TSRMLS_DC)
{
	zval *result, *datetime, *timezone;
	php_timezone_obj *tzobj;
	char time_str[12] = {0};

	MAKE_STD_ZVAL(result);
	array_init(result);

	MAKE_STD_ZVAL(datetime);
	MAKE_STD_ZVAL(timezone);

	datetime_instantiate(php_date_get_date_ce(), datetime TSRMLS_CC);
	snprintf(time_str,12,"%c%ld",'@', signature->when.time);

	datetime_instantiate(php_date_get_timezone_ce(), timezone TSRMLS_CC);
	tzobj = (php_timezone_obj *) zend_object_store_get_object(timezone TSRMLS_CC);
	tzobj->initialized = 1;
	tzobj->type = TIMELIB_ZONETYPE_OFFSET;
	tzobj->tzi.utc_offset = -signature->when.offset; // doesn't work

	/* TODO(chobie): how do i set offset? */
	php_date_initialize(zend_object_store_get_object(datetime TSRMLS_CC), time_str, strlen(time_str), NULL, timezone, 0 TSRMLS_CC);

	add_assoc_string_ex(result, ZEND_STRS("name"), signature->name, 1);
	add_assoc_string_ex(result, ZEND_STRS("email"), signature->email, 1);
	add_assoc_zval_ex(result, ZEND_STRS("time"), datetime);

	zval_ptr_dtor(&timezone);

	*out = result;
}

void php_git2_strarray_to_array(git_strarray *array, zval **out TSRMLS_DC)
{
	zval *result;
	int i = 0;

	MAKE_STD_ZVAL(result);
	array_init(result);

	for (i = 0; i < array->count; i++) {
		add_next_index_string(result, array->strings[i], 1);
	}
	*out = result;
}

int php_git2_call_function_v(
	zend_fcall_info *fci, zend_fcall_info_cache *fcc TSRMLS_DC, zval **retval_ptr_ptr, zend_uint param_count, ...)
{
	zval **params = NULL;
	va_list ap;
	int i = 0;

	if (param_count > 0) {
		params = emalloc(sizeof(zval*) * param_count);
		va_start(ap, param_count);
		for (i = 0; i < param_count; i++) {
			params[i] = va_arg(ap, zval**);
		}
		va_end(ap);
	} else {
		params = NULL;
	}

	if (ZEND_FCI_INITIALIZED(*fci)) {
		fci->params         = params;
		fci->retval_ptr_ptr = retval_ptr_ptr;
		fci->param_count    = param_count;
		fci->no_separation  = 1;

		if (zend_call_function(fci, fcc TSRMLS_CC) != SUCCESS) {
			if (param_count > 0) {
				for (i = 0; i < param_count; i++) {
					zval_ptr_dtor(params[i]);
				}
				efree(params);
			}
			return 1;
		}
		zend_fcall_info_args_clear(fci, 0);
	}

	if (param_count > 0) {
		for (i = 0; i < param_count; i++) {
			zval_ptr_dtor(params[i]);
		}
		efree(params);
	}
	return 0;
}

int php_git2_cb_init(php_git2_cb_t **out, zend_fcall_info *fci, zend_fcall_info_cache *fcc, void *payload TSRMLS_DC)
{
	php_git2_cb_t *cb;

	cb = (struct php_git2_cb_t*)emalloc(sizeof(php_git2_cb_t));
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

void php_git2_cb_free(php_git2_cb_t *target)
{
	efree(target);
}

void php_git2_array_to_strarray(git_strarray *out, zval *array TSRMLS_DC)
{
	int elements = 0, i;
	HashPosition pos;
	zval **value;

	if (Z_TYPE_P(array) != IS_ARRAY){
		return;
	}
	if (zend_hash_num_elements(Z_ARRVAL_P(array)) == 0) {
		return;
	}

	elements = zend_hash_num_elements(Z_ARRVAL_P(array));
	out->strings = (char**)emalloc(sizeof(char*) * elements);
	out->count = elements;
	for (i = 0, zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(array), &pos);
		zend_hash_get_current_data_ex(Z_ARRVAL_P(array), (void **)&value, &pos) == SUCCESS;
		zend_hash_move_forward_ex(Z_ARRVAL_P(array), &pos), i++) {
		char *buffer;

		Z_STRVAL_PP(value);
		buffer = emalloc(sizeof(char*) * Z_STRLEN_PP(value) + 1);
		memcpy(buffer, Z_STRVAL_PP(value), Z_STRLEN_PP(value));
		buffer[Z_STRLEN_PP(value)] = '\0';
		out->strings[i] = buffer;
	}
}

void php_git2_strarray_free(git_strarray *out)
{
	int i = 0;
	for (i = 0; i < out->count; i++) {
		efree(out->strings[i]);
	}
	efree(out->strings);
}

void php_git2_git_checkout_opts_to_array(git_checkout_opts *opts, zval **out TSRMLS_DC)
{
	zval *result;
	git_checkout_opts tmp = GIT_CHECKOUT_OPTS_INIT;
	opts = &tmp;

	MAKE_STD_ZVAL(result);
	array_init(result);

	add_assoc_long_ex(result, ZEND_STRS("version"), opts->version);
	add_assoc_long_ex(result, ZEND_STRS("checkout_strategy"), opts->checkout_strategy);
	add_assoc_long_ex(result, ZEND_STRS("disable_filters"), opts->disable_filters);
	add_assoc_long_ex(result, ZEND_STRS("dir_mode"), opts->dir_mode);
	add_assoc_long_ex(result, ZEND_STRS("file_mode"), opts->file_mode);
	add_assoc_long_ex(result, ZEND_STRS("file_open_flags"), opts->file_open_flags);
	add_assoc_long_ex(result, ZEND_STRS("notify_flags"), opts->notify_flags);

	if (opts->notify_payload != NULL) {

	} else {
		add_assoc_null_ex(result, ZEND_STRS("notify_cb"));
	}

	if (opts->notify_payload != NULL) {

	} else {
		add_assoc_null_ex(result, ZEND_STRS("notify_payload"));
	}

	if (opts->progress_cb != NULL) {

	} else {
		add_assoc_null_ex(result, ZEND_STRS("progress_cb"));
	}

	if (opts->progress_payload != NULL) {

	} else {
		add_assoc_null_ex(result, ZEND_STRS("progress_payload"));
	}

	if (opts->paths.count > 0) {
		zval *paths;
		php_git2_strarray_to_array(&opts->paths, &paths TSRMLS_CC);
		add_assoc_zval_ex(result, ZEND_STRS("paths"), paths);
	} else {
		zval *paths;
		MAKE_STD_ZVAL(paths);
		array_init(paths);
		add_assoc_zval_ex(result, ZEND_STRS("paths"), paths);
	}

	if (opts->baseline != NULL) {
		// git_tree

	} else {
		add_assoc_null_ex(result, ZEND_STRS("baseline"));
	}
	add_assoc_string_ex(result, ZEND_STRS("target_directory"), (opts->target_directory) ? opts->target_directory : "", 1);
	add_assoc_string_ex(result, ZEND_STRS("our_label"), (opts->our_label) ? opts->our_label : "", 1);
	add_assoc_string_ex(result, ZEND_STRS("their_label"), (opts->their_label) ? opts->their_label : "", 1);

	*out = result;
}

void php_git_git_checkout_opts_free(git_checkout_opts *target TSRMLS_DC)
{
	php_git2_cb_t *tmp;

	if (target->notify_payload) {
		tmp = (php_git2_cb_t*)target->notify_payload;
		if (tmp->fci) {
			efree(tmp->fci);
		}
		if (tmp->fcc) {
			efree(tmp->fcc);
		}
		efree(target->notify_payload);
	}
	if (target->progress_payload) {
		tmp = (php_git2_cb_t*)target->progress_payload;
		if (tmp->fci) {
			efree(tmp->fci);
		}
		if (tmp->fcc) {
			efree(tmp->fcc);
		}
		efree(target->progress_payload);
	}

	php_git2_strarray_free(&target->paths);
	efree(target);
}


static int php_git2_git_checkout_notify_cb(git_checkout_notify_t why,
	const char *path,
	const git_diff_file *baseline,
	const git_diff_file *target,
	const git_diff_file *workdir,
	void *payload)
{
	/* TODO(chobie): implement callback */
}

void php_git2_git_checkout_progress_cb(const char *path,
        size_t completed_steps,
        size_t total_steps,
        void *payload)
{
	php_git2_t *result;
	zval *param_path, *param_completed_steps, *param_total_steps, *retval_ptr = NULL;
	php_git2_cb_t *p = (php_git2_cb_t*)payload;
	GIT2_TSRMLS_SET(p->tsrm_ls);

	Z_ADDREF_P(p->payload);
	MAKE_STD_ZVAL(param_path);
	MAKE_STD_ZVAL(param_completed_steps);
	MAKE_STD_ZVAL(param_total_steps);
	ZVAL_NULL(param_path);
	if (path != NULL) {
		ZVAL_STRING(param_path, path, 1);
	}
	ZVAL_LONG(param_completed_steps, completed_steps);
	ZVAL_LONG(param_total_steps, total_steps);

	SEPARATE_ZVAL_TO_MAKE_IS_REF(&p->payload);
	if (php_git2_call_function_v(p->fci, p->fcc TSRMLS_CC, &retval_ptr, 4, &param_path, &param_completed_steps, &param_total_steps, &p->payload)) {
		return;
	}

	zval_ptr_dtor(&retval_ptr);
}


static void php_git2_fcall_info_wrapper(zval *target, zend_fcall_info **out_fci, zend_fcall_info_cache **out_fcc TSRMLS_DC)
{
	char *is_callable_error = NULL;
	zend_fcall_info *fci = NULL;
	zend_fcall_info_cache *fcc = NULL;

	fci = (zend_fcall_info*)emalloc(sizeof(zend_fcall_info));
	fcc = (zend_fcall_info_cache*)emalloc(sizeof(zend_fcall_info_cache));
	memcpy(fci, &empty_fcall_info, sizeof(zend_fcall_info));
	memcpy(fcc, &empty_fcall_info_cache, sizeof(zend_fcall_info_cache));

	if (zend_fcall_info_init(target, 0, fci, fcc, NULL, &is_callable_error TSRMLS_CC) == SUCCESS) {
		if (is_callable_error) {
			efree(is_callable_error);
		}
	} else {
		fprintf(stderr, "FAILED");
		efree(fci);
		efree(fcc);
		return;
	}

	*out_fci = fci;
	*out_fcc = fcc;
}

int php_git2_array_to_git_checkout_opts(git_checkout_opts **out, zval *array TSRMLS_DC)
{
	const char *target_directory, *our_label, *their_label;
	git_checkout_opts *opts = NULL, def = GIT_CHECKOUT_OPTS_INIT;
	php_git2_cb_t *notify_payload = NULL, *progress_payload= NULL;
	zval *notify_cb = NULL, *progress_cb = NULL;
	char *tmp;

	opts = (git_checkout_opts*)emalloc(sizeof(struct git_checkout_opts));
	memcpy(opts, &def, sizeof(git_checkout_opts));

	notify_cb = php_git2_read_arrval(array, ZEND_STRS("notify_cb") TSRMLS_CC);
	progress_cb = php_git2_read_arrval(array, ZEND_STRS("progress_cb") TSRMLS_CC);


	opts->notify_cb = php_git2_git_checkout_notify_cb;
	opts->progress_cb = php_git2_git_checkout_progress_cb;
	opts->version = php_git2_read_arrval_long(array, ZEND_STRS("version") TSRMLS_CC);
	opts->checkout_strategy = php_git2_read_arrval_long(array, ZEND_STRS("checkout_strategy") TSRMLS_CC);
	opts->disable_filters = php_git2_read_arrval_long(array, ZEND_STRS("disable_filters") TSRMLS_CC);
	opts->dir_mode = php_git2_read_arrval_long(array, ZEND_STRS("dir_mode") TSRMLS_CC);
	opts->file_mode = php_git2_read_arrval_long(array, ZEND_STRS("file_mode") TSRMLS_CC);
	opts->file_open_flags = php_git2_read_arrval_long(array, ZEND_STRS("file_open_flags") TSRMLS_CC);
	opts->notify_flags = php_git2_read_arrval_long(array, ZEND_STRS("notify_flags") TSRMLS_CC);

	//notify_cb
	if (Z_TYPE_P(notify_cb) != IS_NULL) {
		zend_fcall_info *fci;
		zend_fcall_info_cache *fcc;

		php_git2_fcall_info_wrapper(notify_cb, &fci, &fcc TSRMLS_CC);
		if (php_git2_cb_init(&notify_payload, fci, fcc,
		 	php_git2_read_arrval(array, ZEND_STRS("notify_payload") TSRMLS_CC) TSRMLS_CC)) {
		}
		opts->notify_payload = notify_payload;
	} else {
		opts->notify_cb = NULL;
	}

	//progress_cb
	if (Z_TYPE_P(progress_cb) != IS_NULL) {
		zend_fcall_info *fci;
		zend_fcall_info_cache *fcc;

		php_git2_fcall_info_wrapper(progress_cb, &fci, &fcc TSRMLS_CC);
		if (php_git2_cb_init(&progress_payload, fci, fcc,
		 	php_git2_read_arrval(array, ZEND_STRS("progress_payload") TSRMLS_CC) TSRMLS_CC)) {
		}
		opts->progress_payload = progress_payload;
	} else {
		opts->progress_cb = NULL;
	}


	php_git2_array_to_strarray(&opts->paths, php_git2_read_arrval(array, ZEND_STRS("paths") TSRMLS_CC) TSRMLS_CC);

	// TODO: assign baseline(git_tree)

	target_directory = php_git2_read_arrval_string(array, ZEND_STRS("target_directory") TSRMLS_CC);
	our_label = php_git2_read_arrval_string(array, ZEND_STRS("our_label") TSRMLS_CC);
	their_label = php_git2_read_arrval_string(array, ZEND_STRS("their_label") TSRMLS_CC);
	opts->target_directory = target_directory;
	opts->our_label = our_label;
	opts->their_label = their_label;

	*out = opts;
	return 0;
}

int php_git2_multi_cb_init(php_git2_multi_cb_t **out, void *payload TSRMLS_DC, int num_callbacks, ...)
{
	php_git2_multi_cb_t *cb;
	int i = 0;
	va_list ap;

	cb = (struct php_git2_multi_cb_t*)emalloc(sizeof(php_git2_multi_cb_t));
	if (cb == NULL) {
		return 1;
	}

	cb->payload = payload;
	cb->num_callbacks = num_callbacks;
	GIT2_TSRMLS_SET2(cb, TSRMLS_C);

	cb->callbacks = emalloc(sizeof(php_git2_fcall_t) * num_callbacks);
	memset(cb->callbacks, '\0', sizeof(php_git2_fcall_t) * num_callbacks);
	va_start(ap, num_callbacks * 2);
	for (i = 0; i < num_callbacks; i++) {
		memcpy(&cb->callbacks[i].fci, va_arg(ap, zend_fcall_info*), sizeof(zend_fcall_info));
		memcpy(&cb->callbacks[i].fcc, va_arg(ap, zend_fcall_info_cache*), sizeof(zend_fcall_info_cache));
	}
	va_end(ap);

	*out = cb;
	return 0;
}

void php_git2_multi_cb_free(php_git2_multi_cb_t *target)
{
	efree(target->callbacks);
	efree(target);
}

void php_git2_diff_line_to_array(git_diff_line *line, zval **out TSRMLS_DC)
{
	zval *result;

	MAKE_STD_ZVAL(result);
	array_init(result);
	add_assoc_stringl_ex(result, ZEND_STRS("origin"), &line->origin, 1, 1);
	add_assoc_long_ex(result, ZEND_STRS("old_lineno"), line->old_lineno);
	add_assoc_long_ex(result, ZEND_STRS("new_lineno"), line->new_lineno);
	add_assoc_long_ex(result, ZEND_STRS("num_lines"), line->num_lines);
	add_assoc_long_ex(result, ZEND_STRS("content_len"), line->content_len);
	add_assoc_long_ex(result, ZEND_STRS("content_offset"), line->content_offset);
	add_assoc_stringl_ex(result, ZEND_STRS("content"), line->content, line->content_len, 1);

	*out = result;
}

void php_git2_diff_hunk_to_array(git_diff_hunk *hunk, zval **out TSRMLS_DC)
{
	zval *result;

	MAKE_STD_ZVAL(result);
	if (hunk == NULL) {
		ZVAL_NULL(result);
	} else {
		array_init(result);
		add_assoc_long_ex(result, ZEND_STRS("old_start"), hunk->old_start);
		add_assoc_long_ex(result, ZEND_STRS("old_lines"), hunk->old_lines);
		add_assoc_long_ex(result, ZEND_STRS("new_start"), hunk->new_start);
		add_assoc_long_ex(result, ZEND_STRS("new_lines"), hunk->new_lines);
		add_assoc_stringl_ex(result, ZEND_STRS("header"), hunk->header, 128, 1);
	}

	*out = result;
}

void php_git2_diff_file_to_array(git_diff_file *file, zval **out TSRMLS_DC)
{
	zval *result;
	char buf[41] = {0};

	MAKE_STD_ZVAL(result);
	array_init(result);
	git_oid_fmt(buf, &file->oid);

	add_assoc_string_ex(result, ZEND_STRS("oid"), buf, 1);
	add_assoc_string_ex(result, ZEND_STRS("path"), file->path, 1);
	add_assoc_long_ex(result, ZEND_STRS("size"), file->size);
	add_assoc_long_ex(result, ZEND_STRS("flags"), file->flags);
	add_assoc_long_ex(result, ZEND_STRS("mode"), file->mode);

	*out = result;
}

void php_git2_diff_delta_to_array(git_diff_delta *delta, zval **out TSRMLS_DC)
{
	zval *result, *old, *new;

	MAKE_STD_ZVAL(result);
	array_init(result);

	add_assoc_long_ex(result, ZEND_STRS("status"), delta->status);
	add_assoc_long_ex(result, ZEND_STRS("flags"), delta->flags);
	add_assoc_long_ex(result, ZEND_STRS("similarity"), delta->similarity);
	add_assoc_long_ex(result, ZEND_STRS("nfiles"), delta->nfiles);

	php_git2_diff_file_to_array(&delta->old_file, &old TSRMLS_CC);
	php_git2_diff_file_to_array(&delta->new_file, &new TSRMLS_CC);

	add_assoc_zval_ex(result, ZEND_STRS("old_file"), old);
	add_assoc_zval_ex(result, ZEND_STRS("new_file"), new);

	*out = result;
}
