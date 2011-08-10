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
#undef lookup

PHPAPI zend_class_entry *git_reference_manager_class_entry;

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_manager__construct, 0, 0, 1)
    ZEND_ARG_INFO(0, repository)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_manager_lookup, 0, 0, 1)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git_reference_manager_create, 0, 0, 2)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, oid)
    ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

static void php_git_reference_manager_free_storage(php_git_reference_manager_t *obj TSRMLS_DC)
{
    zend_object_std_dtor(&obj->zo TSRMLS_CC);
    obj->repository = NULL;
    efree(obj);
}

zend_object_value php_git_reference_manager_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_git_tree_entry_t *obj;
    zval *tmp;

    obj = ecalloc(1, sizeof(*obj));
    zend_object_std_init( &obj->zo, ce TSRMLS_CC );
    zend_hash_copy(obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, 
        (zend_objects_store_dtor_t)zend_objects_destroy_object,
        (zend_objects_free_object_storage_t)php_git_reference_manager_free_storage,
        NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();
    return retval;
}

PHP_METHOD(git_reference_manager, __construct)
{
    php_git_reference_manager_t *this= (php_git_reference_manager_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    zval *repository;
    php_git_repository_t *repo;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "z", &repository) == FAILURE){
        return;
    }
    if(!instanceof_function(Z_OBJCE_P(repository), git_repository_class_entry TSRMLS_CC)){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
             "argument does not Git\\Repository");
        RETURN_FALSE;
    }

    repo = (php_git_repository_t *) zend_object_store_get_object(repository TSRMLS_CC);
    if(repo->repository == NULL){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
             "repository didn't ready");
        RETURN_FALSE;
    }
    this->repository = repo->repository;
}

PHP_METHOD(git_reference_manager, getList)
{
    php_git_reference_manager_t *this= (php_git_reference_manager_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    git_strarray *list = malloc(sizeof(git_strarray));
    int rr, result, i = 0;
    git_reference *reference;
    zval *references;
    git_rtype type;
    const char *target;
    char out[GIT_OID_HEXSZ+1] = {0};
    zval *ref;

    git_reference_listall(list,this->repository,GIT_REF_LISTALL);

    MAKE_STD_ZVAL(references);
    array_init(references);
    for(i = 0; i < list->count; i++){
        // FIXME
        result = git_reference_lookup(&reference, this->repository, list->strings[i]);
        if(result != GIT_SUCCESS) {
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                "Can't find specified reference.");
            RETURN_FALSE;
        }

        MAKE_STD_ZVAL(ref);
        object_init_ex(ref, git_reference_class_entry);
        php_git_reference_t *refobj  = (php_git_reference_t *) zend_object_store_get_object(ref TSRMLS_CC);
        refobj->object = reference;

        add_property_string_ex(ref,"name",  sizeof("name"),  (char *)git_reference_name(reference), 1 TSRMLS_CC);

        type = git_reference_type(reference);
        if(type == GIT_REF_SYMBOLIC) {
            target = git_reference_target(reference);
            if(target != NULL) {
                add_property_string_ex(ref,"target",sizeof("target"),(char *)target, 1 TSRMLS_CC);
            }
            rr = git_reference_resolve(&refobj->object,reference);
            if(rr != GIT_SUCCESS){
                zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                    "something wrong");
                RETURN_FALSE;
            }
        }

        git_oid_to_string(out,GIT_OID_HEXSZ+1,git_reference_oid(refobj->object));
        add_property_string_ex(ref,"oid",sizeof("oid"),out, 1 TSRMLS_CC);
        memset(out,'\0',GIT_OID_HEXSZ+1);

        add_next_index_zval(references, ref);
    }

    git_strarray_free(list);
    RETURN_ZVAL(references,0,0);
}

PHP_METHOD(git_reference_manager, pack)
{
    php_git_reference_manager_t *this= (php_git_reference_manager_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    int ret = git_reference_packall(this->repository);
    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "an error occured while packing references. error_code: %d\n",ret);
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

PHP_METHOD(git_reference_manager, lookup)
{
    php_git_reference_manager_t *this = (php_git_reference_manager_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *name;
    int rr, result, name_len = 0;
    zval *ref;
    char out[GIT_OID_HEXSZ+1] = {0};
    git_oid *oid;
    git_rtype type;
    git_reference *reference;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "s", &name, &name_len) == FAILURE){
        return;
    }

    result = git_reference_lookup(&reference, this->repository, name);
    if(result != GIT_SUCCESS) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "Can't find specified reference.");
        RETURN_FALSE;
    }

    MAKE_STD_ZVAL(ref);
    object_init_ex(ref, git_reference_class_entry);
    php_git_reference_t *refobj  = (php_git_reference_t *) zend_object_store_get_object(ref TSRMLS_CC);
    refobj->object = reference;

    add_property_string_ex(ref,"name",  sizeof("name"),  (char *)git_reference_name(reference), 1 TSRMLS_CC);

    type = git_reference_type(reference);
    if(type == GIT_REF_SYMBOLIC) {
        const char *target = git_reference_target(reference);
        if(target != NULL) {
            add_property_string_ex(ref,"target",sizeof("target"),(char *)target, 1 TSRMLS_CC);
        }
        rr = git_reference_resolve(&refobj->object,reference);
        if(rr != GIT_SUCCESS){
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                "something wrong");
            RETURN_FALSE;
        }
    }

    git_oid_to_string(out,GIT_OID_HEXSZ+1,git_reference_oid(refobj->object));
    add_property_string_ex(ref,"oid",sizeof("oid"),out, 1 TSRMLS_CC);

    RETURN_ZVAL(ref,0,0);
}

PHP_METHOD(git_reference_manager, create)
{
    php_git_reference_manager_t *this = (php_git_reference_manager_t *) zend_object_store_get_object(getThis() TSRMLS_CC);
    char *name;
    int name_len = 0;
    char *oid;
    int ret,rr, oid_len = 0;
    git_oid id;
    zend_bool force = 0;
    git_odb *odb;
    git_reference *reference;
    char out[GIT_OID_HEXSZ+1] = {0};
    git_rtype type;
    zval *ref;
    const char *target;
    
    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
        "ss|b", &name, &name_len, &oid, &oid_len, &force) == FAILURE){
        return;
    }
    if(oid_len != GIT_OID_HEXSZ){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "oid length seems illegal");
        RETURN_FALSE;
    }
    
    git_oid_fromstr(&id, oid);
    odb = git_repository_database(this->repository);
    
    if(!git_odb_exists(odb,&id)){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "specified oid not found");
        RETURN_FALSE;
    }
    
    ret = git_reference_create_oid(&reference, this->repository, name, &id, force);
    if(ret != GIT_SUCCESS){
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
            "can't add reference, maybe try setting force to boolean true");
        RETURN_FALSE;
    }
    
    MAKE_STD_ZVAL(ref);
    object_init_ex(ref, git_reference_class_entry);
    php_git_reference_t *refobj  = (php_git_reference_t *) zend_object_store_get_object(ref TSRMLS_CC);
    refobj->object = reference;

    add_property_string_ex(ref,"name",  sizeof("name"),  name, 1 TSRMLS_CC);
    type = git_reference_type(reference);
    if(type == GIT_REF_SYMBOLIC) {
        target = git_reference_target(reference);
        if(target != NULL) {
            add_property_string_ex(ref,"target",sizeof("target"),(char *)target, 1 TSRMLS_CC);
        }
        rr = git_reference_resolve(&refobj->object,reference);
        if(rr != GIT_SUCCESS){
            zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
                "something wrong");
            RETURN_FALSE;
        }
    }
    git_oid_to_string(out,GIT_OID_HEXSZ+1,git_reference_oid(refobj->object));
    add_property_string_ex(ref,"oid",sizeof("oid"),out, 1 TSRMLS_CC);
    RETURN_ZVAL(ref,0,0);
}

static zend_function_entry php_git_reference_manager_methods[] = {
    PHP_ME(git_reference_manager, __construct, arginfo_git_reference_manager__construct, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference_manager, getList,     NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference_manager, lookup,   arginfo_git_reference_manager_lookup, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference_manager, pack,        NULL, ZEND_ACC_PUBLIC)
    PHP_ME(git_reference_manager, create,      arginfo_git_reference_manager_create, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_reference_manager(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, ZEND_NS_NAME(PHP_GIT_NS,"Reference"),"Manager", php_git_reference_manager_methods);
    git_reference_manager_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
    git_reference_manager_class_entry->create_object = php_git_reference_manager_new;

}
