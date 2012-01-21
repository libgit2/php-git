# PHP-Git2 - libgit2 bindings in PHP

php-git2 is a PHP bindings to the libgit2 linkable C Git library. 
this extension are re-writing php-git as that code too dirty.

# Installing And Running

````
git clone https://github.com/chobie/php-git2.git
cd php-git2
phpize
./configure
make
sudo make Install
````

# API

## Repository Access

````php
$repo = new Git2\Repository($path);
/*
  bool = $repo->isExist(string sha1)
  Git2\Object = $repo->read(string sha1)
  string sha1 = $repo->hash(string content, long type)
  string sha1 = $repo->write(string content, long type)
  bool = $repo->isBare()
  bool = $repo->isEmpty()
  bool = $repo->headDetached()
  bool = $repo->headOrphan()
  string path = Git2\Repository::discover("/Users/chobie/projects/work/repo/lib/subdir");
  // => /Users/chobie/projects/work/repo/.git

  Git2\Repository = Git2\Repository::init(string $path, bool isBare)
*/
````

## Object Access