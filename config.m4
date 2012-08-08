PHP_ARG_ENABLE(git2, Whether to enable the "git2" extension,
	[  --enable-git2      Enable "php-git2" extension support])

if test $PHP_GIT2 != "no"; then
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
				tag.c \
				odb.c \
				odb_object.c \
				backend.c \
	, $ext_shared)

	PHP_ADD_INCLUDE([$ext_srcdir/libgit2/include])

	CFLAGS=" $CFLAGS -Wunused-variable -Wpointer-sign -Wimplicit-function-declaration -Winline -Wunused-macros -Wredundant-decls -Wstrict-aliasing=2 -Wswitch-enum -Wdeclaration-after-statement -Wl,libgit2/build/libgit2.a"
	PHP_SUBST([CFLAGS])

	ifdef([PHP_ADD_EXTENSION_DEP],
	[
		PHP_ADD_EXTENSION_DEP(git, spl, true)
	])

fi
