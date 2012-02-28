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

PHPAPI zend_class_entry *git2_tree_class_entry;

static void php_git2_tree_free_storage(php_git2_tree *object TSRMLS_DC)
{
	if (object->tree != NULL) {
		git_tree_free(object->tree);
		object->tree = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_tree_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_tree);
	object->offset = 0;
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_diff, 0,0,2)
	ZEND_ARG_INFO(0, old)
	ZEND_ARG_INFO(0, new)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_get_subtree, 0,0,1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_tree_get_entry_by_name, 0,0,1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()


static int php_git2_tree_diff_cb(const git_tree_diff_data *ptr, void *data)
{
/*
typedef struct {
        unsigned int old_attr;
        unsigned int new_attr;
        git_oid old_oid;
        git_oid new_oid;
        git_status_t status;
        const char *path;
} git_tree_diff_data;
*/
	fprintf(stderr,"path:%s\n",ptr->path);
}
	
typedef struct{
	zval *old;
	zval *new;
	zval *result;
} php_git2_tree_diff_cb_t;
/*
{{{ proto: Git2\Tree::diff($old, $new)
	@todo: think this behavior
*/
PHP_METHOD(git2_tree, diff)
{
	zval *old, *new;
	php_git2_tree *m_old, *m_new;
	php_git2_tree_diff_cb_t payload;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"OO", &old, git2_tree_class_entry, &new, git2_tree_class_entry) == FAILURE) {
		return;
	}
	
	m_old = PHP_GIT2_GET_OBJECT(php_git2_tree, old);
	m_new = PHP_GIT2_GET_OBJECT(php_git2_tree, new);

	git_tree_diff(m_old->tree,m_new->tree, &php_git2_tree_diff_cb, &payload);
}
/* }}} */


/* Iterator Implementation */

/*
{{{ proto: Git2\Tree::current()
*/
PHP_METHOD(git2_tree, current)
{
	php_git2_tree *m_tree;
	const git_tree_entry *entry;
	zval *z_entry;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	entry = git_tree_entry_byindex(m_tree->tree, m_tree->offset);
	if (entry == NULL) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
			"specified offset does not exist. %d");
		RETURN_FALSE;
	}
	create_tree_entry_from_entry(&z_entry, (git_tree_entry *)entry ,m_tree->repository);
	RETURN_ZVAL(z_entry, 0, 1);
}
/* }}} */

/*
{{{ proto: Git2\Tree::key()
*/
PHP_METHOD(git2_tree, key)
{
	php_git2_tree *m_tree;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	RETURN_LONG(m_tree->offset);
}

/*
{{{ proto: Git2\Tree::valid()
*/
PHP_METHOD(git2_tree, next)
{
	php_git2_tree *m_tree;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	m_tree->offset++;
}

/*
{{{ proto: Git2\Tree::rewind()
*/
PHP_METHOD(git2_tree, rewind)
{
	php_git2_tree *m_tree;

	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	m_tree->offset = 0;
}

/*
{{{ proto: Git2\Tree::valid()
*/
PHP_METHOD(git2_tree, valid)
{
	php_git2_tree *m_tree;
	int entry_count = 0;
	
	m_tree     = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	entry_count = git_tree_entrycount(m_tree->tree);
	if (m_tree->offset < entry_count && m_tree->offset >= 0) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


static int get_subtree(git_tree **result, git_tree *root, char *path)
{
	char *p, *k, *current_key, *tmp_value, *savedptr = NULL;
	git_tree_entry *entry;
	git_tree *target,*tmp_result;
	int error = 0;
	
	target = root;
	p = (char *)strchr(path, '/');
	
	if (p == NULL) {
		entry = git_tree_entry_byname(target, path);
		if (entry) {
			git_otype type;
			type = git_tree_entry_type((const git_tree_entry*)entry);
			if (type == GIT_OBJ_TREE) {
				return git_tree_lookup(
					result,
					git_object_owner((const git_object *)target),
					git_tree_entry_id(entry)
				);
			} else {
				*result = NULL;
				return -1;
			}
		} else {
			return -1;
		}
	}

	tmp_value = estrdup(path);
	current_key = php_strtok_r(tmp_value, "/", &savedptr);
	
	while (current_key != NULL && target != NULL) {
		k  = current_key;
		
		if (current_key != NULL && k != NULL) {
			entry = git_tree_entry_byname(target, current_key);
			if (entry && git_tree_entry_type((const git_tree_entry*)entry) == GIT_OBJ_TREE) {
				error = git_tree_lookup(
					&tmp_result,
					git_object_owner((const git_object *)target),
					git_tree_entry_id(entry)
				);
				
				if (error == GIT_SUCCESS) {
					target = tmp_result;
				} else {
					return -1;
				}
			} else {
				target = NULL;
				current_key = NULL;
			}
		} else {
			if (k != NULL) {
				entry = git_tree_entry_byname(target, current_key);
				if (entry && git_tree_entry_type((const git_tree_entry*)entry) == GIT_OBJ_TREE) {
					error = git_tree_lookup(
						&tmp_result,
						git_object_owner((const git_object *)target),
						git_object_id((const git_object *)entry)
					);
					
					if (error == GIT_SUCCESS) {
						target = tmp_result;
					} else {
						return -1;
					}
				} else {
					target = NULL;
					current_key = NULL;
				}
			}
		}
		
		current_key = php_strtok_r(NULL, "/", &savedptr);
	}
	efree(tmp_value);
	
	if (target && target != root) {
		*result = target;
		return 0;
	} else {
		return -1;
	}
}

/*
{{{ proto: Git2\Tree Git2\Tree::getSubtree($path)
*/
PHP_METHOD(git2_tree, getSubtree)
{
	char *path = NULL;
	int error, path_len = 0;
	git_tree *subtree;
	php_git2_tree *object;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}
	
	object = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	
	/* note: this method does not use git_tree_getsubtree as that function follows dirname(3) style.
	 * this method returns specified subtree or false.
	*/
	error = get_subtree(&subtree, object->tree, path);
	if (error == GIT_SUCCESS) {
		zval *result;
		
		result = php_git2_object_new(git_object_owner((git_object *)object->tree), (git_object *)subtree TSRMLS_CC);
		RETVAL_ZVAL(result, 0, 1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


/*
{{{ proto: Git2\Tree Git2\Tree::getEntryByName($name)
*/
PHP_METHOD(git2_tree, getEntryByName)
{
	char *path = NULL;
	int path_len = 0;
	php_git2_tree *object;
	const git_tree_entry *entry = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"s", &path, &path_len) == FAILURE) {
		return;
	}
	
	object = PHP_GIT2_GET_OBJECT(php_git2_tree, getThis());
	
	entry = git_tree_entry_byname(object->tree, (const char *)path);
	if (entry) {
		zval *result;
		
		create_tree_entry_from_entry(&result, (git_tree_entry *)entry ,git_object_owner((git_object *)object->tree));
		RETVAL_ZVAL(result, 0, 1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


static zend_function_entry php_git2_tree_methods[] = {
	PHP_ME(git2_tree, diff,        arginfo_git2_tree_diff,          ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	/* Iterator Implementation */
	PHP_ME(git2_tree, current,     NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, key,         NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, next,        NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, rewind,      NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, valid,       NULL,                            ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, getSubtree,  arginfo_git2_tree_get_subtree,   ZEND_ACC_PUBLIC)
	PHP_ME(git2_tree, getEntryByName,arginfo_git2_tree_get_entry_by_name, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_tree_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Tree", php_git2_tree_methods);
	git2_tree_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_tree_class_entry->create_object = php_git2_tree_new;
	zend_class_implements(git2_tree_class_entry TSRMLS_CC, 1, spl_ce_Iterator);
}