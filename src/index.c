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
#include <zend_exceptions.h>
#include <string.h>
#include <time.h>

PHPAPI zend_class_entry *git_index_class_entry;
PHPAPI zend_class_entry *git_index_iterator_class_entry;

static void php_git_index_free_storage(php_git_index_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    if(obj->index){
        git_index_free(obj->index);
    }
    efree(obj);
}

zend_object_value php_git_index_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_index_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_index_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_add, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
    ZEND_ARG_INFO(0, stage)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_find, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_get_entry, 0, 0, 1)
    ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_construct, 0, 0, 1)
  ZEND_ARG_INFO(0, repository_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_remove, 0, 0, 1)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index_insert, 0, 0, 1)
  ZEND_ARG_INFO(0, entry)
ZEND_END_ARG_INFO()

/*
ZEND_BEGIN_ARG_INFO_EX(arginfo_git_index__construct, 0, 0, 1)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
*/

void php_git_index_entry_create(zval **index, git_index_entry *entry)
{
    TSRMLS_FETCH();    
    char oid[GIT_OID_HEXSZ+1] = {0};
	MAKE_STD_ZVAL(*index);
    object_init_ex(*index,git_index_entry_class_entry);
    git_oid_to_string(oid,GIT_OID_HEXSZ+1,&entry->oid);

    add_property_string_ex(*index,"path", sizeof("path"), entry->path, 1 TSRMLS_CC);
    add_property_string_ex(*index,"oid",sizeof("oid"),oid, 1 TSRMLS_CC);
    add_property_long(*index,"dev",entry->dev);
    add_property_long(*index,"ino",entry->ino);
    add_property_long(*index,"mode",entry->mode);
    add_property_long(*index,"uid",entry->uid);
    add_property_long(*index,"gid",entry->gid);
    add_property_long(*index,"file_size",entry->file_size);
    add_property_long(*index,"flags",entry->flags);
    add_property_long(*index,"flags_extended",entry->flags_extended);
    add_property_long(*index,"ctime",time(&entry->ctime.seconds));
    add_property_long(*index,"mtime",time(&entry->mtime.seconds));
}

PHP_METHOD(git_index, count)
{
    php_git_index_t *this = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int entry_count = git_index_entrycount(this->index);

    RETVAL_LONG(entry_count);
}

PHP_METHOD(git_index, find)
{
    int offset = 0;
    char *path;
    int path_len = 0;
    git_index *index = NULL;
    git_index_entry *entry;
    zval *z_git_index_entry;
	php_git_index_t *myobj;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &path, &path_len) == FAILURE){
        return;
    }

    myobj = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    index = myobj->index;

    offset = git_index_find(index,path);
    if(offset < 0){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "specified path does not exist.");
        RETURN_FALSE;
    }

    entry = git_index_get(myobj->index,offset);
    if(entry == NULL){
        return;
    }
    php_git_index_entry_create(&z_git_index_entry, entry);
    RETURN_ZVAL(z_git_index_entry,0,0);
}

PHP_METHOD(git_index, getEntry)
{
    php_git_index_t *this = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_index_entry *entry;
    zval *git_index_entry;
    int offset = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "l", &offset) == FAILURE){
        return;
    }

    entry = git_index_get(this->index,offset);
    php_git_index_entry_create(&git_index_entry, entry);
    RETURN_ZVAL(git_index_entry,0, 0);
}

PHP_METHOD(git_index, add)
{
    int offset = 0;
    char *path;
    int path_len = 0;
    git_index *index = NULL;
    long stage = 0;
	php_git_index_t *myobj;
	int success;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s|l", &path, &path_len, &stage) == FAILURE){
        return;
    }

    myobj = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    index = myobj->index;

    //FIXME: examine stage value.
    // 0 => new file
    // 1 => deleted ?
    // 2 => ?
    success = git_index_add(index,path,stage);
    if(success != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't add specified index.");
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_METHOD(git_index, remove)
{
    php_git_index_t *this = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *path;
    int path_len = 0;
	int offset;
	int result;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &path, &path_len) == FAILURE){
        return;
    }

    offset = git_index_find(this->index,path);
    if(offset < 0){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "specified path does not exist.");
        RETURN_FALSE;
    }

    result = git_index_remove(this->index, offset);
    if(result != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "specified offset does not exist.");
        RETURN_FALSE
    }
    RETURN_TRUE;
}


PHP_METHOD(git_index, write)
{
    php_git_index_t *myobj = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);

    int success = git_index_write(myobj->index);
    if(success != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't write index");
        RETURN_FALSE;
    }

    git_index_read(myobj->index);
    RETURN_TRUE;
}

PHP_METHOD(git_index, refresh)
{
    git_index *index = NULL;
    php_git_index_t *myobj = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    index = myobj->index;

    git_index_read(index);
}

PHP_METHOD(git_index, getIterator)
{
    php_git_index_t *this = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *iterator;
	php_git_index_iterator_t *obj;
    
    MAKE_STD_ZVAL(iterator);
    object_init_ex(iterator,git_index_iterator_class_entry);
    obj = (php_git_index_iterator_t *) zend_object_store_get_object(iterator TSRMLS_CC);
    obj->index = this->index;
    obj->offset = 0;
    RETURN_ZVAL(iterator,0,0);
}
/*
PHP_METHOD(git_index, __construct)
{
    php_git_index_t *this = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_index *index;
    char *path;
    int path_len = 0;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &path, &path_len) == FAILURE){
        return;
    }
    int ret = git_index_open_bare(&index,path);
    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't read specified index");
        RETURN_FALSE;
    }
    this->index = index;
    this->offset = 0;
    add_property_long(getThis(), "entry_count",git_index_entrycount(index));

}
*/
/*
PHP_METHOD(git_index, insert)
{
    php_git_index_t *this = (php_git_index_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *z_entry;
    git_index_entry entry;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &z_entry) == FAILURE){
        return;
    }
    entry.ctime = zend_read_property(git_index_entry_class_entry, z_entry,"ctime",sizeof("ctime"), 0 TSRMLS_CC);
    entry.mtime = zend_read_property(git_index_entry_class_entry, z_entry,"mtime",sizeof("mtime"), 0 TSRMLS_CC);
    entry.dev   = zend_read_property(git_index_entry_class_entry, z_entry,"dev",sizeof("dev"), 0 TSRMLS_CC);
    entry.ino   = zend_read_property(git_index_entry_class_entry, z_entry,"ino",sizeof("ino"), 0 TSRMLS_CC);
    entry.mode  = zend_read_property(git_index_entry_class_entry, z_entry,"mode",sizeof("mode"), 0 TSRMLS_CC);
    entry.uid   = zend_read_property(git_index_entry_class_entry, z_entry,"uid",sizeof("uid"), 0 TSRMLS_CC);
    entry.gid   = zend_read_property(git_index_entry_class_entry, z_entry,"gid",sizeof("gid"), 0 TSRMLS_CC);
    entry.file_size = zend_read_property(git_index_entry_class_entry, z_entry,"file_size",sizeof("file_size"), 0 TSRMLS_CC);
    entry.oid = zend_read_property(git_index_entry_class_entry, z_entry,"oid",sizeof("oid"), 0 TSRMLS_CC);
    entry.flags = zend_read_property(git_index_entry_class_entry, z_entry,"flags",sizeof("flags"), 0 TSRMLS_CC);
    entry.flags_extended = zend_read_property(git_index_entry_class_entry, z_entry,"flags_extended",sizeof("flags_extended"), 0 TSRMLS_CC);
    entry.path = zend_read_property(git_index_entry_class_entry, z_entry,"path",sizeof("path"), 0 TSRMLS_CC);
    
    int ret = git_index_insert(this->index, &entry);
    if(ret != GIT_SUCCESS){
        
    }
}
*/

static zend_function_entry php_git_index_methods[] = {
    //PHP_ME(git_index, __construct, arginfo_git_index__construct,ZEND_ACC_PUBLIC)
    PHP_ME(git_index, getEntry,    arginfo_git_index_get_entry, ZEND_ACC_PUBLIC)
    PHP_ME(git_index, find,        arginfo_git_index_find,      ZEND_ACC_PUBLIC)
    PHP_ME(git_index, add,         arginfo_git_index_add,       ZEND_ACC_PUBLIC)
    PHP_ME(git_index, remove,      arginfo_git_index_remove,    ZEND_ACC_PUBLIC)
    PHP_ME(git_index, refresh,     NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_index, write,       NULL,                        ZEND_ACC_PUBLIC)
    //PHP_ME(git_index, insert,      arginfo_git_index_insert,    ZEND_ACC_PUBLIC)
    // Countable
    PHP_ME(git_index, count,       NULL,                        ZEND_ACC_PUBLIC)
    PHP_ME(git_index, getIterator, NULL,                        ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_index_init(TSRMLS_D)
{
    zend_class_entry git_index_ce;
    INIT_NS_CLASS_ENTRY(git_index_ce, PHP_GIT_NS,"Index", php_git_index_methods);

    git_index_class_entry = zend_register_internal_class(&git_index_ce TSRMLS_CC);
    git_index_class_entry->create_object = php_git_index_new;
    zend_class_implements(git_index_class_entry TSRMLS_CC, 2, spl_ce_Countable, zend_ce_aggregate);
}
