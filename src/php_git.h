#ifndef PHP_GIT_H

#define PHP_GIT_H

#define PHP_GIT_EXTNAME "git"
#define PHP_GIT_EXTVER "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include <git2.h>

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry git_module_entry;
#define phpext_git_ptr &git_module_entry;

#define REGISTER_GIT_CONST_LONG(const_name, value) { \
	zend_class_entry **git_class_entry;	\
	if (zend_hash_find(CG(class_table), "git", sizeof("git"), (void **) &git_class_entry) != FAILURE)	\
		zend_declare_class_constant_long(*git_class_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);	\
}	\



PHP_METHOD(git, __construct);
PHP_METHOD(git, hello);

#endif /* PHP_GIT_H */