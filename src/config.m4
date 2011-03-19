PHP_ARG_ENABLE(git,Whether to enable the "git" extension,
  [  --enable-git      Enable "phpgit" extension support])

PHP_ARG_WITH(libgit2-dir,  for libgit2,
[  --with-libgit2-dir[=DIR]   Set the path to libgit2 install prefix.], yes)

if test $PHP_GIT != "no"; then
  if test "$PHP_LIBGIT2_DIR" != "no" && test "$PHP_LIBGIT2_DIR" != "yes"; then
    LIBGIT2_SEARCH_DIRS=$PHP_LIBGIT2_DIR
  else
    LIBGIT2_SEARCH_DIRS="/usr/local /usr"
  fi

  for i in $LIBGIT2_SEARCH_DIRS; do
    if test -f $i/include/libgit2/git2.h; then
      LIBGIT2_DIR=$i
      LIBGIT2_INCDIR=$i/include/libgit2
    elif test -f $i/include/git2.h; then
      LIBGIT2_DIR=$i
      LIBGIT2_INCDIR=$i/include
    fi
  done

  if test -z "$LIBGIT2_DIR"; then
    AC_MSG_ERROR(Cannot find libgit2)
  fi

  LIBGIT2_LIBDIR=$LIBGIT2_DIR/$PHP_LIBDIR
  PHP_ADD_LIBRARY_WITH_PATH(git2, $LIBGIT2_LIBDIR, GIT_SHARED_LIBADD)

  PHP_SUBST(GIT_SHARED_LIBADD)
  PHP_NEW_EXTENSION(git,php_git.c reference.c reference_manager.c repository.c signature.c commit.c index_entry.c index_iterator.c index.c tree_iterator.c tree.c blob.c tree_entry.c walker.c object.c rawobject.c tag.c odb.c backend.c, $ext_shared)

  ifdef([PHP_ADD_EXTENSION_DEP],
  [
    PHP_ADD_EXTENSION_DEP(git, spl, true)
  ])

fi
