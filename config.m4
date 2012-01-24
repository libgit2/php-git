PHP_ARG_ENABLE(git2, Whether to enable the "git2" extension,
	[  --enable-git2      Enable "php-git2" extension support])

PHP_ARG_WITH(libgit2-dir,  for libgit2,
	[  --with-libgit2-dir[=DIR]   Set the path to libgit2 install prefix.], yes)

if test $PHP_GIT2 != "no"; then
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
	PHP_ADD_LIBRARY_WITH_PATH(git2, $LIBGIT2_LIBDIR, GIT2_SHARED_LIBADD)

	PHP_SUBST(GIT2_SHARED_LIBADD)
	PHP_NEW_EXTENSION(git2, git2.c \
				repository.c \
				commit.c \
				blob.c \
				tree.c \
				tree_builder.c \
				tree_entry.c \
				signature.c \
				walker.c \
				reference.c \
				index.c \
				index_entry.c \
				config.c \
				remote.c \
	, $ext_shared)

	ifdef([PHP_ADD_EXTENSION_DEP],
	[
		PHP_ADD_EXTENSION_DEP(git, spl, true)
	])

fi
