#include "php_git2.h"
#include "php_git2_priv.h"
#include "graph.h"

/* {{{ proto long git_graph_ahead_behind(resource $repo, string $local, string $upstream)
 */
PHP_FUNCTION(git_graph_ahead_behind)
{
	int result = 0, local_len = 0, upstream_len = 0, error = 0;
	zval *repo = NULL, *array = NULL;
	php_git2_t *_repo = NULL;
	char *local = NULL, *upstream = NULL;
	git_oid __local = {0}, __upstream = {0};
	size_t ahead = 0, behind = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
		"rss", &ahead, &behind, &repo, &local, &local_len, &upstream, &upstream_len) == FAILURE) {
		return;
	}
	
	ZEND_FETCH_RESOURCE(_repo, php_git2_t*, &repo, -1, PHP_GIT2_RESOURCE_NAME, git2_resource_handle);
	if (git_oid_fromstrn(&__local, local, local_len)) {
		RETURN_FALSE;
	}
	if (git_oid_fromstrn(&__upstream, upstream, upstream_len)) {
		RETURN_FALSE;
	}
	result = git_graph_ahead_behind(&ahead, &behind, PHP_GIT2_V(_repo, repository), &__local, &__upstream);

	MAKE_STD_ZVAL(array);
	array_init(array);
	add_next_index_long(array, ahead);
	add_next_index_long(array, behind);

	RETURN_ZVAL(array, 0, 1);
}
/* }}} */

