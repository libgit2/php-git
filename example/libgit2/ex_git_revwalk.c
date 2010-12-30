#include <git2.h>
#include <string.h>
#include <stdio.h>

/**
 * Revisionをあるくよ
 */
int main()
{
	git_oid id;
	git_revwalk *walk;
	git_commit *head, *commit;
	char *msg;

	git_signature *author;
	git_repository *repo;
	git_repository_open(&repo, "./repository/.git");
	
	git_oid_mkstr(&id,"9321ca6661d57ca0eebe774da070d62d98f22f7c");
	git_commit_lookup(&head,repo,&id);
	
	git_revwalk_new(&walk, repo);
	git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE);
	git_revwalk_push(walk, head);
	
	while((commit = git_revwalk_next(walk)) != NULL)
	{
		msg = git_commit_message_short(commit);
		author = git_commit_author(commit);
		printf("%s (%s)\n",msg, author->email);
	}
	git_revwalk_free(walk);

	git_repository_free(repo);
	return 0;
}