#include <git2.h>
#include <string.h>
#include <stdio.h>


/**
 * Todo：
 * 多分branchのハッシュを持ってくるAPIがない
int main()
{
	git_oid oid;
	git_commit *head, *commit;
	git_odb *odb;
	char *msg;

	git_signature *author;
	git_repository *repo;
	git_repository_open(&repo, "./repository/.git");
	
	odb = git_repoistory_database(repo);
	git_oid_mkstr(&oid,)
	
	git_repository_free(repo);
	return 0;
}
 */
