# PHP-Git2 - libgit2 bindings in PHP

php-git2 is a PHP bindings to the libgit2 linkable C Git library.
this extension are re-writing php-git as that code too dirty.

# Latest Branch

v0.3.0 (switching to functions)
https://github.com/libgit2/php-git/tree/functions

# Important Notice

php-git changed it's API drastically. this changes doesn't care about compatibility between old one.
please check tests cases.

# Installing And Running

you need to install libgit2 before make php-git.

````
git clone https://github.com/libgit2/php-git.git --recursive
cd libgit2
mkdir build && cd build
cmake ..
cmake -DBUILD_SHARED_LIBS=OFF -build .
make
cd ../../
phpize
./configure
make
make install
sudo make install
# add `extension=git2.so` to your php.ini
````

new php-git features almost tested.

# API

## Repository Access

````php
$repo = new Git2\Repository($path);
/*
  bool = $repo->exists(string sha1)
  Git2\Object = $repo->lookup(string sha1)
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

### create new blob

````
$oid = Git2\Blob::create($repo, "Hello World");
/*
  $blob = $repo->lookup($oid);
  int $blob->getSize();
  string $blob->getContent();
*/
````

## Tree Access

````
$repo = new Git2\Repository($path);
$tree = $repo->lookup(tree sha); // specify tree sha
foreach ($tree as $oid => $entry) {
/*
  bool $entry->isTree();
  bool $entry->isBlob();
  bool $entry->isSubmodule();
*/
        var_dump($entry);
}
````

## Ref Management

````
$ref = Git2\Reference::lookup($repo, "refs/heads/master");
  sha = $ref->getTarget();
  str = $ref->getName();
````

````
foreach (Git2\Reference::each($repo) as $ref) {
  echo $ref->getName() . PHP_EOL;
}
````


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
$parent = Git2\Commit::create($repo, array(
	"author"    => $author,
	"committer" => $author,
	"message"   => "Hello World",
	"tree"      => $tree,
	"parents"   => $parents,
));
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
````

## Config access

````
$config = new Git2\Config("path/to/git/config");
$config->get("core.bare");
$config->store("core.bare","1");

// Git2\Config supports read / write dimension.
$config['core.bare']
$config['core.bare'] = 1;
````

## ODB operation

````
$repo = Git2\Repository::init("/path/to/repo",true);
$odb = $repo->odb // read only property
Git\OdbObject $odb->read(sha1) // returns uncompressed git raw data.
string $odb->hash(string contents, int type)// same as Git2\Repository::hash
string $odb->write(string contents, int type)// same as Git2\Repository::write
bool $odb->exists(sha1)// same as Git2\Repository::exists
````

## Reflog
will be add.

## Remote access (Experimental)

this API will be change.

````
$repo = new Git2\Repository("/path/to/.git");
$remote = new Git2\Remote($repo,"http://github.com/libgit2/php-git.git");
// for now, remote can fetch files only. that does not update references.
$remote->fetch();
````

## Author
* Shuhei Tanuma

## Contributors

* Anthony Van de Gejuchte
* Cameron Eagans
* Graham Weldon
* James Titcumb
* Matthieu Moquet
* Ryusuke SEKIYAMA
* Shuhei Tanuma
* Vasileios Georgitzikis
* tsteiner

## LICENSE

MIT License
