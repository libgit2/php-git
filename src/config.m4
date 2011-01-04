PHP_ARG_ENABLE(git,
  [Whether to enable the "git" extension]
  [  --enable-git      Enable "git" extension support])

if test $PHP_GIT != "no"; then
  export CFLAGS="$CFLAGS -D_FILE_OFFSET_BITS=64 -lgit2"
  PHP_SUBST(GIT_SHARED_LIBADD)
  PHP_NEW_EXTENSION(git,php_git.c signature.c commit.c index.c tree.c blob.c tree_entry.c walker.c object.c rawobject.c tag.c backend.c, $ext_shared)
fi