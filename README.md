# PHP-Git2 - libgit2 bindings in PHP

php-git2 is a PHP bindings to the libgit2 linkable C Git library. 

## Status

0.3.0 Alpha (switching to functions)

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


// error code will handle extension.
// resource creation or getting functions will return their resource or bool.
resource|bool function git_repository_init(string $path, long $is_bare);

some small structure (e.g: git_config_entry) should consider return as an array. it's usefull.
````

see http://libgit2.github.com/libgit2/#HEAD

##### file name rules.

basically, we rely libgit2 grouping at this time. (`branch` group functions should be in branch.c)
some group (e.g config) will conflicts php headers. we choose `g_` prefix for now.

check grouping here http://libgit2.github.com/libgit2/#HEAD

##### generating files

if you wanna try to work new file. please use gen.php and generate stubs. as declarations are bored task.
(sometimes, this generator might output wrong headers. then just comment out or fix generator)

````
php gen.php libgit2/include/git2/branch.h (0|1) [filter] > target.c or target.h
````

you can ouptut function entry with this. past it to `php_git2.c`

````
php fe.php target.c
````

##### testing

group/function.phpt

##### policy

* don't create OOP interface for ease of maintenance.
* follow latest libgit2 api. don't consider BC at this time.

## LICENSE

MIT License
