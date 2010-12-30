#include <stdio.h>
#include <git2.h>
#include <time.h>

/**
 * libgit2 also has a set of index (cachefile) manipulation methods.
 * These cover being able to read and write the Git index file - 
 * stage and unstage files, that sort of thing.
 * http://libgit2.github.com/libgit2/structgit__index__entry.html
 */
int main()
{
    git_index_entry *entry;
    git_index *index;
    git_index_open_bare(&index,"./repository/.git/index");
    char oid[40];

    git_index_read(index);
    git_index_entrycount(index);

    int offset = git_index_find(index,"Example");
    entry = git_index_get(index,offset);
    if(entry == NULL){
        fprintf(stderr,"not found");
        return 0;
    }
    
    git_oid_fmt(oid,&entry->oid);
    printf("oid: %s\n",oid);
    printf("path: %s\n",entry->path);
    printf("ctime: %s",ctime(&entry->ctime.seconds));
    printf("mtime: %s",ctime(&entry->mtime.seconds));
	return 0;
}