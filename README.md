# PHP-Git2 - libgit2 bindings in PHP

php-git2 is a PHP bindings to the libgit2 linkable C Git library. 

## Status

0.3.0 Alpha (switching to functions)

https://docs.google.com/spreadsheet/ccc?key=0AjvShWAWqvfHdDRneEtIUF9GRUZMNVVVR1hpdURiUWc&usp=sharing

## How to build

```
# build libgit2.a
git submodule init && git submodule update
mkdir libgit2/build
cd libgit2/build
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF .
cmake --build .

# build php-git2
cd ../../
phpize
./configure --enable-git2-debug
make
make install
# add extension=git2.so to your php.ini
```

## For Contributors

##### Issue first.

please make a issue first. don't work before creating it.

##### Coding Styles

follow pecl coding standards (except 8 at this moment).

* http://git.php.net/?p=php-src.git;a=blob_plain;f=CODING_STANDARDS;hb=HEAD

##### Signature conversions

````
GIT_EXTERN(int) git_repository_init(
        git_repository **out,
        const char *path,
        unsigned is_bare);


// error code should handle in extension.
// resource creation or getting functions will return their resource or bool.
resource|bool function git_repository_init(string $path, long $is_bare);

public struct (e.g: git_config_entry) should consider return as an array.
````

see libgit2.github.com/libgit2/#v0.20.0

##### file name rules.

basically, we rely libgit2 grouping at this time. (`branch` group functions should be in branch.c)
some group (e.g config) will conflicts php header files. we choose `g_` prefix for now.

check grouping here libgit2.github.com/libgit2/#v0.20.0

##### generating files

if you wanna try to work new file. please use gen.php and generate stubs. as declarations are bored task.
(sometimes, this generator might output wrong headers. then just comment out or fix generator)

````
PRINT_HEADER=1 php ng.php libgit2/include/git2/branch.h > branch.h
php ng.php libgit2/include/git2/branch.h > branch.c
````

you can generate `PHP_FE` with this. past it to `php_git2.c`

````
php fe.php target.c
````

Note: usually, these generators might output needless variables. DON'T PR `prettify codes` at this moment.
As we have more than 500 php functions. we like to use some fixer command than fix by hand.

##### documents

use prototype.

```
  /* {{{ proto int abs(int number)
     Returns the absolute value of the number */
  PHP_FUNCTION(abs)
  {
     ...
  }
  /* }}} */
```

document will generate later. please check source code before publish docs.

##### testing

[group]/[function].phpt

##### policy

* don't create OOP interface in extension for ease of maintenance.
* follow latest libgit2 api. don't consider BC at this time.

## LICENSE

MIT License
