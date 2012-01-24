/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2012 Shuhei Tanuma
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "php_git2.h"
#include <spl/spl_array.h>
#include <zend_interfaces.h>

PHPAPI zend_class_entry *git2_config_class_entry;

static void php_git2_config_free_storage(php_git2_config *object TSRMLS_DC)
{
	if (object->config != NULL) {
		free(object->config);
		object->config = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_config_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_config);
	return retval;
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_config___construct, 0,0,1)
	ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_config_get, 0,0,1)
	ZEND_ARG_INFO(0, get)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_config_store, 0,0,2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_config_delete, 0,0,1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

typedef struct{
	zval *result;
	git_config *config;
} php_git2_config_foreach_t;

static int php_git2_config_resolve(zval **result, const char *var_name, zval *m_config)
{
	TSRMLS_FETCH();
	HashTable *hash;
	zval *entry, *tmp_result, **target_offset;
	char *current_key, *tmp_value, *savedptr, *k;
	int error = 0;
	
	entry = zend_read_property(git2_config_class_entry, m_config,"configs",sizeof("configs")-1, 0 TSRMLS_CC);
	
	tmp_value = estrdup(var_name);
	current_key = php_strtok_r(tmp_value, ".", &savedptr);
	while (current_key != NULL) {
		k  = current_key;
		current_key = php_strtok_r(NULL, ".", &savedptr);
		
		if (current_key != NULL && k != NULL) {
			if (zend_hash_exists(Z_ARRVAL_P(entry), k, strlen(k)+1)) {
				if (zend_hash_find(Z_ARRVAL_P(entry), k, strlen(k)+1, (void **)&target_offset) == SUCCESS) {
					entry = *target_offset;
				}
			} else {
				target_offset = NULL;
			}
		} else {
			if (k != NULL) {
				if (zend_hash_find(Z_ARRVAL_P(entry), k, strlen(k)+1, (void **)&target_offset) != SUCCESS) {
					target_offset = NULL;
				}
			}
		}
	}
	efree(tmp_value);
	
	if (target_offset != NULL) {
		MAKE_STD_ZVAL(tmp_result);
		ZVAL_ZVAL(tmp_result, *target_offset,1,0);
	} else {
		MAKE_STD_ZVAL(tmp_result);
		ZVAL_NULL(tmp_result);
	}
	*result = tmp_result;
	
	return error;
}

static int php_git2_config_foreach(const char *var_name, const char *value, void *payload)
{
	HashTable *hash;
	zval *entry, **target_offset;
	const char *config_value;
	char *current_key, *tmp_value, *savedptr, *k;
	php_git2_config_foreach_t *opaque = (php_git2_config_foreach_t *)payload;
	int error = 0;
	
	hash = Z_ARRVAL_P(opaque->result);
	
	error = git_config_get_string(opaque->config, var_name, &config_value);

	tmp_value = estrdup(var_name);
	current_key = php_strtok_r(tmp_value, ".", &savedptr);
	while (current_key != NULL) {
		k  = current_key;
		current_key = php_strtok_r(NULL, ".", &savedptr);
		
		if (current_key != NULL) {
			if (zend_hash_exists(hash, k, strlen(k)+1)) {
				if (zend_hash_find(hash,k, strlen(k)+1, (void **)&target_offset) == SUCCESS) {
					hash = Z_ARRVAL_P(*target_offset);
				}
			} else {
				MAKE_STD_ZVAL(entry);
				array_init(entry);
				zend_hash_add(hash, k, strlen(k)+1, (void **)&entry, sizeof(entry), NULL);
				hash = Z_ARRVAL_P(entry);
			}
		}
	}
	
	if (k != NULL) {
		MAKE_STD_ZVAL(entry);
		ZVAL_STRING(entry, config_value, 1);
		zend_hash_add(hash, k, strlen(k)+1, (void **)&entry, sizeof(entry), NULL);
		Z_ADDREF_P(entry);
		zval_ptr_dtor(&entry);
	}
	efree(tmp_value);
	
	return GIT_SUCCESS;
}

static int php_git2_config_reload(zval *object, unsigned short dtor TSRMLS_DC)
{
	zval *entry;
	php_git2_config_foreach_t payload;
	php_git2_config *m_config;
	int error = 0;
	
	m_config = PHP_GIT2_GET_OBJECT(php_git2_config, object);
	entry = zend_read_property(git2_config_class_entry, object,"configs",sizeof("configs")-1, 1 TSRMLS_CC);
	if (entry != NULL) {
		zval_ptr_dtor(&entry);
		entry = NULL;
	}

	MAKE_STD_ZVAL(entry);
	array_init(entry);

	payload.config = m_config->config;
	payload.result = entry;
	error = git_config_foreach(m_config->config,&php_git2_config_foreach,&payload);
	add_property_zval(object, "configs", entry);
	if (dtor == 1) {
		zval_ptr_dtor(&entry);
	}
}

/*
{{{ proto: Git2\Config::__construct(string $path)
*/
PHP_METHOD(git2_config, __construct)
{
	char *path;
	git_config *config;
	int error, path_len = 0;
	php_git2_config *m_config;
	zval *config_array;
	php_git2_config_foreach_t payload;

	/* @todo: supports array for reading multiple configs */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}
	
	error = git_config_open_ondisk(&config, path);
	/* @todo: automatic convert types */
	m_config = PHP_GIT2_GET_OBJECT(php_git2_config, getThis());
	m_config->config = config;
	
	php_git2_config_reload(getThis(), 1 TSRMLS_CC);
	/**
	 * @todo: support global config
	 * php_array_merge(HashTable *dest, HashTable *src, int recursive TSRMLS_DC);
	 */
}
/* }}} */

/*
{{{ proto: Git2\Config::get(string $key)
*/
PHP_METHOD(git2_config, get)
{
	char *key;
	git_config *config;
	int error, key_len = 0;
	const char *value;
	php_git2_config *m_config;
	zval *result;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &key, &key_len) == FAILURE) {
		return;
	}
	
	if (key_len < 1) {
		RETURN_FALSE;
	}
	
	php_git2_config_resolve(&result, (const char *)key, getThis());
	RETVAL_ZVAL(result,0,1);
}
/* }}} */


/*
{{{ proto: Git2\Config::store(string $key, mixed $value)
*/
PHP_METHOD(git2_config, store)
{
	char *key;
	int error, key_len = 0;
	zval *result, *value, *entry;
	php_git2_config *m_config;
	php_git2_config_foreach_t payload;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"sz", &key, &key_len, &value) == FAILURE) {
		return;
	}
	
	if (key_len < 1) {
		RETURN_FALSE;
	}
	
	m_config = PHP_GIT2_GET_OBJECT(php_git2_config, getThis());
	
	switch (Z_TYPE_P(value)) {
		case IS_STRING:
			error = git_config_set_string(m_config->config, key, Z_STRVAL_P(value));
			break;
		case IS_BOOL:
			error = git_config_set_bool(m_config->config, key, Z_BVAL_P(value));
			break;
		case IS_LONG:
			error = git_config_set_int32(m_config->config, key, Z_LVAL_P(value));
			break;
		default:
			zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
				"Git2\\Config::store must pass string or bool or long value");
			RETURN_FALSE;
	}

	php_git2_config_reload(getThis(),0 TSRMLS_CC);
}
/* }}} */


/*
{{{ proto: Git2\Config::delete(string $key)
*/
PHP_METHOD(git2_config, delete)
{
	char *key;
	int error, key_len = 0;
	zval *result, *entry;
	php_git2_config *m_config;
	php_git2_config_foreach_t payload;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &key, &key_len) == FAILURE) {
		return;
	}
	
	if (key_len < 1) {
		RETURN_FALSE;
	}
	
	m_config = PHP_GIT2_GET_OBJECT(php_git2_config, getThis());
	git_config_delete(m_config->config, key);
	php_git2_config_reload(getThis(), 0 TSRMLS_CC);
}
/* }}} */

static zend_function_entry php_git2_config_methods[] = {
	PHP_ME(git2_config, __construct, arginfo_git2_config___construct, ZEND_ACC_PUBLIC)
	PHP_ME(git2_config, get,         arginfo_git2_config_get,         ZEND_ACC_PUBLIC)
	PHP_ME(git2_config, store,       arginfo_git2_config_store,       ZEND_ACC_PUBLIC)
	PHP_ME(git2_config, delete,      arginfo_git2_config_delete,      ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_config_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Config", php_git2_config_methods);
	git2_config_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_config_class_entry->create_object = php_git2_config_new;
}