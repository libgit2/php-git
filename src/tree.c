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

PHP_METHOD(git_tree, count)
{
	long cnt = 0;
    zval *entries;

    entries = zend_read_property(git_tree_entry_class_entry,getThis(),"entries",7,0 TSRMLS_DC);
	cnt = zend_hash_num_elements(Z_ARRVAL_P(entries));

    RETURN_LONG(cnt);
}

// GitTree
PHPAPI function_entry php_git_tree_methods[] = {
    PHP_ME(git_tree, count, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void git_init_tree(TSRMLS_D)
{
    zend_class_entry git_tree_ce;
    INIT_CLASS_ENTRY(git_tree_ce, "GitTree", php_git_tree_methods);
    git_tree_class_entry = zend_register_internal_class(&git_tree_ce TSRMLS_CC);
    zend_class_implements(git_tree_class_entry TSRMLS_CC, 1, spl_ce_Countable);
}