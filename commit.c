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

PHPAPI zend_class_entry *git2_commit_class_entry;

static void php_git2_commit_free_storage(php_git2_commit *object TSRMLS_DC)
{
	if (object->commit != NULL) {
		git_commit_free(object->commit);
		object->commit = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_commit_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_commit);
	return retval;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_commit_create, 0,0,2)
	ZEND_ARG_INFO(0, repository)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_git2_commit_get_parent, 0,0,1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

/*
{{{ proto: Git2\Commit::getMessage()
*/
PHP_METHOD(git2_commit, getMessage)
{
	char *data;
	php_git2_commit *m_commit;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		RETURN_STRING(git_commit_message(m_commit->commit),1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getMessageEncoding()
*/
PHP_METHOD(git2_commit, getMessageEncoding)
{
	const char *encoding;
	php_git2_commit *m_commit;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		encoding = git_commit_message_encoding(m_commit->commit);
		if (encoding != NULL) {
			RETURN_STRING(encoding,1);
		} else {
			RETURN_STRING("UTF-8",1);
		}
	} 
	RETURN_FALSE;
}
/* }}} */


/*
{{{ proto: Git2\Commit::parentCount()
*/
PHP_METHOD(git2_commit, parentCount)
{
	unsigned int parent_count = 0;
	php_git2_commit *m_commit;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		parent_count = git_commit_parentcount(m_commit->commit);
		RETURN_LONG(parent_count);
	}
	RETURN_FALSE;
}
/* }}} */

/*
{{{ proto: Git2\Commit::getAuthor()
*/
PHP_METHOD(git2_commit, getAuthor)
{
	unsigned int parent_count = 0;
	php_git2_commit *m_commit;
	zval *z_signature, *date;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}

		php_git2_create_signature_from_commit(&z_signature, m_commit->commit, 0 TSRMLS_CC);
		RETVAL_ZVAL(z_signature, 0, 1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getCommitter()
*/
PHP_METHOD(git2_commit, getCommitter)
{
	unsigned int parent_count = 0;
	php_git2_commit *m_commit;
	zval *z_signature, *date;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}

		php_git2_create_signature_from_commit(&z_signature, m_commit->commit,1 TSRMLS_CC);
		RETVAL_ZVAL(z_signature, 0, 1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getOid()
*/
PHP_METHOD(git2_commit, getOid)
{
	unsigned int parent_count = 0;
	php_git2_commit *m_commit;
	char oid_out[GIT_OID_HEXSZ] = {0};
	git_oid oid;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}

		git_oid_fmt(oid_out, git_commit_id(m_commit->commit));
		RETVAL_STRINGL(oid_out,GIT_OID_HEXSZ,1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::create(Git2\Repository $repo, array $data)
*/
PHP_METHOD(git2_commit, create)
{
	php_git2_tree *m_tree;
	php_git2_signature *m_author,*m_committer;
	php_git2_repository *m_repository;
	zval *repository, **element, *z_parents, *z_tree, *z_author, *z_committer, *z_array, **value_pp = NULL;
	HashTable *hash;
	const git_commit **parents = NULL;
	git_commit **free_list = NULL;
	git_tree *tree;
	git_signature *author, *committer;
	git_oid commit_oid;
	char *message, *encoding, *ref, oid_out[GIT_OID_HEXSZ];
	int parent_count, i, error = 0;
	HashPosition pos;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"Oa", &repository, git2_repository_class_entry,&z_array) == FAILURE) {
		return;
	}
	
	m_repository = PHP_GIT2_GET_OBJECT(php_git2_repository, repository);

	hash = Z_ARRVAL_P(z_array);
	if (zend_hash_find(hash,"author",sizeof("author"),(void **)&value_pp) != FAILURE) {
		z_author = *value_pp;
		m_author = PHP_GIT2_GET_OBJECT(php_git2_signature,z_author);
	} else {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"key 'author' required");
		return;
	}

	if (zend_hash_find(hash,"committer",sizeof("committer"),(void **)&value_pp) != FAILURE) {
		z_committer = *value_pp;
		m_committer = PHP_GIT2_GET_OBJECT(php_git2_signature,z_committer);
	} else {
		z_committer = z_author;
		m_committer = PHP_GIT2_GET_OBJECT(php_git2_signature,z_committer);
	}

	if (zend_hash_find(hash,"tree",sizeof("tree"),(void **)&value_pp) != FAILURE) {
		z_tree = *value_pp;
		if (Z_TYPE_P(z_tree) == IS_STRING) {
			git_oid oid;
			error = git_oid_fromstr(&oid, Z_STRVAL_P(z_tree));
			error = git_tree_lookup(&tree, m_repository->repository,&oid);
		} else {
			m_tree = PHP_GIT2_GET_OBJECT(php_git2_tree, z_tree);
			tree = m_tree->tree;
		}
	} else {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"key 'tree' required");
		return;
	}

	if (zend_hash_find(hash,"parents",sizeof("parents"),(void **)&value_pp) != FAILURE) {
		z_parents = *value_pp;
	}

	if (zend_hash_find(hash,"ref",sizeof("ref"),(void **)&value_pp) != FAILURE) {
		ref = emalloc(sizeof(char)*Z_STRLEN_PP(value_pp)+1);
		sprintf(ref, "%s", Z_STRVAL_PP(value_pp));
	} else {
		ref = emalloc(sizeof(char)*5);
		sprintf(ref,"HEAD");
	}

	if (zend_hash_find(hash,"message",sizeof("message"),(void **)&value_pp) != FAILURE) {
		message = Z_STRVAL_PP(value_pp);
	} else {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,"key 'message' required");
		return;
	}

	if (zend_hash_find(hash,"encoding",sizeof("encoding"),(void **)&value_pp) != FAILURE) {
		encoding = emalloc(sizeof(char)*Z_STRLEN_PP(value_pp)+1);
		sprintf(encoding, "%s",Z_STRVAL_PP(value_pp));
	} else {
		encoding = emalloc(sizeof(char)*6);
		sprintf(encoding,"UTF-8");
	}
	
	parent_count = zend_hash_num_elements(Z_ARRVAL_P(z_parents));
	parents = emalloc(parent_count * sizeof(void *));
	free_list = emalloc(parent_count * sizeof(void *));
	
	for(i = 0, zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(z_parents), &pos);
			zend_hash_get_current_data_ex(Z_ARRVAL_P(z_parents), (void **)&element, &pos) == SUCCESS;
			zend_hash_move_forward_ex(Z_ARRVAL_P(z_parents), &pos)
	) {
		git_commit *parent = NULL;
		git_commit *free_ptr = NULL;
		
		if (Z_TYPE_PP(element) == IS_STRING) {
			git_oid oid;
			error = git_oid_fromstr(&oid, Z_STRVAL_PP(element));
			git_commit_lookup(&parent, m_repository->repository,&oid);

			free_ptr = parent;
		} else {
			php_git2_commit *m_commit;
			m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, *element);
			parent = m_commit->commit;
		}
		
		parents[i] = parent;
		free_list[i] = free_ptr;
		i++;
	}
	
	error = git_commit_create(
		&commit_oid,
		m_repository->repository,
		ref,
		m_author->signature,
		m_committer->signature,
		encoding,
		message,
		tree,
		parent_count,
		parents
	);

	git_oid_fmt(oid_out, &commit_oid);
	RETVAL_STRINGL(oid_out,GIT_OID_HEXSZ,1);
	
	for (i =0; i < parent_count; ++i) {
		git_object_free((git_object *)free_list[i]);
	}
	efree(ref);
	efree(parents);
	efree(free_list);
	efree(encoding);
}
/* }}} */


/*
{{{ proto: Git2\Commit::getTree()
*/
PHP_METHOD(git2_commit, getTree)
{
	php_git2_commit *m_commit;
	const git_oid *oid;
	git_oid *id;
	git_otype type = GIT_OBJ_TREE;
	git_object *object;
	zval *result;
	int error = 0;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}

		oid = git_commit_tree_oid(m_commit->commit);
		error = git_object_lookup(&object, git_object_owner((git_object *)m_commit->commit), oid, type);
		result = php_git2_object_new(git_object_owner((git_object *)m_commit->commit), object TSRMLS_CC);
		RETVAL_ZVAL(result,0,1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getParents()
*/
PHP_METHOD(git2_commit, getParents)
{
	php_git2_commit *m_commit;
	unsigned int parent_count = 0;
	int error, i = 0;
	zval *result;
	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}

		parent_count = git_commit_parentcount(m_commit->commit);
		MAKE_STD_ZVAL(result);
		array_init(result);
		for (i = 0; i < parent_count; i++) {
			git_commit *parent = NULL;
			zval *tmp = NULL;
			
			error = git_commit_parent(&parent, m_commit->commit, i);
			if (error == GIT_SUCCESS) {
				tmp = php_git2_object_new(git_object_owner((git_object *)m_commit->commit), parent TSRMLS_CC);
				add_next_index_zval(result, tmp);
			}
		}
		
		RETVAL_ZVAL(result,0,1);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getParent([int index])
*/
PHP_METHOD(git2_commit, getParent)
{
	php_git2_commit *m_commit;
	unsigned int parent_count = 0;
	int error, i = 0;
	long index = 0;
	zval *result;
	git_commit *parent = NULL;

	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"|l", &index) == FAILURE) {
		return;
	}

	
	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}

		parent_count = git_commit_parentcount(m_commit->commit);
		if (index > (parent_count-1) || index < 0) {
			/* @todo: throws invalidargument exception */
			RETURN_FALSE;
		}
		
		error = git_commit_parent(&parent, m_commit->commit, (unsigned int)index);
		if (error == GIT_SUCCESS) {
			result = php_git2_object_new(git_object_owner((git_object *)m_commit->commit), parent TSRMLS_CC);
			RETVAL_ZVAL(result,0,1);
		}
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/*
{{{ proto: Git2\Commit::getParentCount()
*/
PHP_METHOD(git2_commit, getParentCount)
{
	php_git2_commit *m_commit;
	unsigned int parent_count = 0;
	int error, i = 0;
	zval *result;
	git_commit *parent = NULL;

	m_commit = PHP_GIT2_GET_OBJECT(php_git2_commit, getThis());

	if (m_commit != NULL) {
		if (m_commit->commit == NULL) {
			RETURN_FALSE;
		}
		
		parent_count = git_commit_parentcount(m_commit->commit);
		RETURN_LONG(parent_count);
	} else {
		RETURN_FALSE;
	}
}
/* }}} */


static zend_function_entry php_git2_commit_methods[] = {
	PHP_ME(git2_commit, getMessage,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getMessageEncoding, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, parentCount,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getAuthor,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getCommitter,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getOid,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getTree,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getParentCount,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getParent,          arginfo_git2_commit_get_parent, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, getParents,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_commit, create,             arginfo_git2_commit_create, ZEND_ACC_STATIC | ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_commit_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Commit", php_git2_commit_methods);
	git2_commit_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_commit_class_entry->create_object = php_git2_commit_new;
}
