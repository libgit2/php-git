#include <git2.h>
#include <string.h>
#include <stdio.h>

/**
 * Blobデータを扱うサンプル
 */
int main()
{
	git_repository *repo;
	git_repository_open(&repo, "./repository/.git");

	git_oid id;
	git_blob *blob;
	git_object *obj;

	//普通はIndexからoidを拾ってくる。
	git_oid_mkstr(&id,"a32ac5db9af41d8a60c9db69aa232f656240da81");
	git_blob_lookup(&blob, repo, &id);
	printf("size: %d\n", git_blob_rawsize(blob));
	printf("raw content:\n%s\n",git_blob_rawcontent(blob));
	
	// raw objectとして扱う
	git_odb *odb;
	git_rawobj raw;

	odb = git_repository_database(repo);
	int error = git_odb_read(&raw,odb,&id);

	printf("rawdata:\n%s\n",(char *)raw.data);
	git_repository_free(repo);
	return 0;
}