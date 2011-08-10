/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2011 Shuhei Tanuma
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

#include "php_git.h"
#include <spl/spl_array.h>
#include <zend_interfaces.h>
#include <string.h>
#include <time.h>

PHPAPI zend_class_entry *git_config_class_entry;

static void php_git_config_free_storage(php_git_config_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    efree(obj);
}

zend_object_value php_git_config_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_config_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_config_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_config_parse_file, 0, 0, 1)
  ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

typedef struct{
    zval *array;
    git_config *config;
} git_config_foreach_t;


static int php_git_config_foreach(const char *key, void *data)
{
    HashTable *hash;
    zval *config, *moe_key, *moe, **target_key;
    char *savedptr, *current_key, *uu, *value, *tmp;

    config = ((git_config_foreach_t*)data)->array;
    hash =  Z_ARRVAL_P(config);
    tmp = estrdup(key);
    git_config_get_string(((git_config_foreach_t *)data)->config,key,&value);

    current_key = php_strtok_r(tmp, ".",&savedptr);
    while (current_key != NULL) {
        uu = current_key;
        current_key = php_strtok_r(NULL, ".",&savedptr);
        if(current_key != NULL) {
            if(zend_hash_exists(hash,uu,strlen(uu)+1)) {
                if (zend_hash_find(hash,uu,strlen(uu)+1,(void **)&target_key) == SUCCESS) {
                    hash = Z_ARRVAL_P(*target_key);
                }
            } else {
                MAKE_STD_ZVAL(moe_key);
                array_init(moe_key);
                zend_hash_add(hash,uu,strlen(uu)+1,(void **)&moe_key,sizeof(moe_key),NULL);
                hash = Z_ARRVAL_P(moe_key);
            }
        }
    }
    
    if(uu != NULL) {
        MAKE_STD_ZVAL(moe);
        ZVAL_STRING(moe,value,1);
        zval_copy_ctor(&moe);
        zend_hash_add(hash,uu,strlen(uu)+1,(void **)&moe,sizeof(moe),NULL);
    }

    efree(tmp);
    return GIT_SUCCESS;
}

PHP_METHOD(git_config, parseFile)
{
    git_config_foreach_t t;
    git_config *config;
    zval *zconf;
    char *path;
    int path_len = 0;
    int ret = GIT_ERROR;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &path,&path_len) == FAILURE){
        return;
    }
    
    ret = git_config_open_file(&config, path);
    if(ret != GIT_SUCCESS) {
        php_git_throw_exception(NULL,ret,NULL TSRMLS_CC);
        return;
    }
    
    MAKE_STD_ZVAL(zconf);
    array_init(zconf);

    t.array = zconf;
    t.config = config;
    
    git_config_foreach(config,php_git_config_foreach,&t);
    
    t.array = NULL;
    t.config = NULL;
    git_config_free(config);
    
    RETURN_ZVAL(zconf,0,1);
}

static zend_function_entry php_git_config_methods[] = {
    PHP_ME(git_config, parseFile, arginfo_git_config_parse_file, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL,NULL,NULL}
};

void git_config_init(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, PHP_GIT_NS,"Config", php_git_config_methods);
    git_config_class_entry  = zend_register_internal_class(&ce TSRMLS_CC);
    git_config_class_entry->create_object = php_git_config_new;
}
