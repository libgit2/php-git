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

PHPAPI function_entry php_git_blob_methods[] = {
    {NULL, NULL, NULL}
};

void git_init_blob(TSRMLS_D)
{
/*
    struct git_object {
	git_oid id;
	git_repository *repo;
	git_odb_source source;
	int in_memory:1, modified:1;
};
*/
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "GitBlob", php_git_blob_methods);
    git_blob_class_entry = zend_register_internal_class(&ce TSRMLS_CC);
}