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

PHPAPI zend_class_entry *git2_tag_class_entry;

static void php_git2_tag_free_storage(php_git2_tag *object TSRMLS_DC)
{
	if (object->tag != NULL) {
		free(object->tag);
		object->tag = NULL;
	}
	zend_object_std_dtor(&object->zo TSRMLS_CC);
	efree(object);
}

zend_object_value php_git2_tag_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	PHP_GIT2_STD_CREATE_OBJECT(php_git2_tag);
	return retval;
}

/*
{{{ proto: Git2\Tag::getTarget()
*/
PHP_METHOD(git2_tag, getTarget)
{
	php_git2_tag *m_tag;
	git_object *object;
	zval *result;
	int error = 0;
	
	m_tag = PHP_GIT2_GET_OBJECT(php_git2_tag, getThis());
	
	error = git_tag_target(&object, m_tag->tag);
	if (error == GIT_SUCCESS) {
		result = php_git2_object_new((git_repository*)git_object_owner((git_object*)m_tag->tag), object TSRMLS_CC);
		RETVAL_ZVAL(result,0,1);
	}
}
/* }}} */

/*
{{{ proto: Git2\Tag::getMessage()
*/
PHP_METHOD(git2_tag, getMessage)
{
	php_git2_tag *m_tag;
	const char *message;
	zval *result;
	int error = 0;
	
	m_tag = PHP_GIT2_GET_OBJECT(php_git2_tag, getThis());
	message = git_tag_message(m_tag->tag);
	RETURN_STRING(message,1);
}
/* }}} */


/*
{{{ proto: Git2\Tag::getBaseName()
*/
PHP_METHOD(git2_tag, getBaseName)
{
	zval *result;
	const char *name = NULL;
	const *basename = NULL;
	php_git2_tag *m_tag;
	size_t len;
	
	m_tag = PHP_GIT2_GET_OBJECT(php_git2_tag, getThis());
	
	name  = git_tag_name(m_tag->tag);
	php_basename(name, strlen(name), NULL, 0, &basename, &len TSRMLS_CC);
	RETVAL_STRINGL(basename, len, 0);
}
/* }}} */

static zend_function_entry php_git2_tag_methods[] = {
	PHP_ME(git2_tag, getTarget, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_tag, getMessage, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(git2_tag, getBaseName, NULL, ZEND_ACC_PUBLIC)
	{NULL,NULL,NULL}
};

void php_git2_tag_init(TSRMLS_D)
{
	zend_class_entry ce;
	
	INIT_NS_CLASS_ENTRY(ce, PHP_GIT2_NS, "Tag", php_git2_tag_methods);
	git2_tag_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
	git2_tag_class_entry->create_object = php_git2_tag_new;
}