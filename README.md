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

## Commit

````
<?php
date_default_timezone_set('Asia/Tokyo');
$repo = Git2\Repository::init("/path/to/repo",true);

$author = new Git2\Signature("Shuhei Tanuma","chobieee@gmail.com",new DateTime());

$bld = new Git2\TreeBuilder();
$bld->insert(new Git2\TreeEntry(array(
	"name" => "README.txt",
	"oid" => "63542fbea05732b78711479a31557bd1b0aa2116",
	"attributes" => octdec('100644'),
)));
$tree = $bld->write($repo);

$parent = "";
$parents = array();
for ($i = 0; $i< 10;$i++){
	$parent = Git2\Commit::create($repo, array(
		"author"    => $author,
		"committer" => $author,
		"message"   => "Hello World: {$i}",
		"tree"      => $tree,
		"parents"   => $parents,
	));
	$parents = array($parent);
}
````

## Revision Walking

````
$repo = new Git2\Repository($path);
$walker = new Git2\Walker($repo);
/* specify HEAD oid */
$walker->push("6e20138dc38f9f626107f1cd3ef0f9838c43defe");

foreach ($walker as $oid => $commit) {
        printf("oid: %s\n", $oid);
        printf("message: %s\n", $commit->getMessage());
}
