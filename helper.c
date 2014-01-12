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
	tzobj->tzi.utc_offset = -signature->when.offset; /* NOTE(chobie): probably this fine */

	php_date_initialize(zend_object_store_get_object(datetime TSRMLS_CC), NULL, 0, NULL, timezone, 0 TSRMLS_CC);

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
