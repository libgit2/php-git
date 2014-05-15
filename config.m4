PHP_ARG_ENABLE(git2, Whether to enable the "git2" extension,
	[  --enable-git2      Enable "php-git2" extension support])

PHP_ARG_ENABLE(git2-debug, for git2 debug support,
  [  --enable-git2-debug       Enable git2 debug support], no, no)

PHP_ARG_ENABLE(git2feedback, Whether to submit feedback to php-git,
	[  --disable-git2feedback      Disable "php-git2" feedback])

if test $PHP_GIT2FEEDBACK != "yes";; then
	AC_CONFIG_FILES([run-tests.php], [chmod +x run-tests.php])
	AC_CONFIG_FILES([Makefile.global.in])
fi

if test $PHP_GIT2 != "no"; then
	PHP_SUBST(GIT2_SHARED_LIBADD)

	PHP_NEW_EXTENSION(git2, php_git2.c repository.c commit.c tree.c clone.c blob.c helper.c revwalk.c treebuilder.c reference.c g_config.c object.c index.c revparse.c branch.c tag.c status.c cred.c remote.c transport.c diff.c checkout.c filter.c ignore.c indexer.c pathspec.c patch.c merge.c note.c odb.c reflog.c blame.c packbuilder.c stash.c signature.c attr.c reset.c message.c submodule.c giterr.c push.c refspec.c graph.c, $ext_shared)
	PHP_ADD_INCLUDE([$ext_srcdir/libgit2/include])

	# for now
	CFLAGS=" $CFLAGS -Wunused-variable -Wpointer-sign -Wimplicit-function-declaration -Winline -Wunused-macros -Wredundant-decls -Wstrict-aliasing=2 -Wswitch-enum -Wdeclaration-after-statement -Wl,libgit2/build/libgit2.a"

	if test "$PHP_GIT2_DEBUG" != "no"; then
		CFLAGS="-g -O0 $CFLAGS"
	fi

	PHP_ADD_LIBPATH($ext_srcdir/libgit2/build, GIT2_SHARED_LIBADD)
	#PHP_ADD_LIBRARY(git2,, GIT2_SHARED_LIBADD)
	PHP_SUBST([CFLAGS])

	ifdef([PHP_ADD_EXTENSION_DEP],
	[
		PHP_ADD_EXTENSION_DEP(git2, spl, true)
	])
fi
