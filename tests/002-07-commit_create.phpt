--TEST--
Check for Git2\Commit::getCommitter
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
date_default_timezone_set('Asia/Tokyo');
$path = __DIR__ . '/mock/002-07';
if (file_exists($path)) {
	`rm -rf {$path}`;
}
$repo = Git2\Repository::init($path, true);
$oid = $repo->write("Hello World", 3);

$author = new Git2\Signature("Shuhei Tanuma","chobieee@gmail.com",new DateTime("@1327164747"));
$committer = new Git2\Signature("Shuhei Tanuma San","chobieee@gmail.com",new DateTime("@1327164747"));
$bld = new Git2\TreeBuilder();
$bld->insert(new Git2\TreeEntry(array(
	"name" => "README.txt",
	"oid" => $oid,
	"attributes" => octdec('100644'),
)));
$tree = $bld->write($repo);

$parent = "";
$parents = array();
$parent = Git2\Commit::create($repo, array(
	"author"    => $author,
	"committer" => $committer,
	"message"   => "Hello World",
	"tree"      => $tree,
	"parents"   => $parents,
));

$commit = $repo->lookup($parent);

printf("commit_id: %s\n",$parent);
printf("author: %s\n", $commit->getAuthor()->name);
printf("email: %s\n", $commit->getAuthor()->email);
printf("time: %s\n", $commit->getAuthor()->time->getTimestamp());
echo PHP_EOL;
printf("%s\n", $commit->getMessage());
`rm -rf {$path}`;
--EXPECT--
commit_id: 239442d8e6cdbd904e150e25778cc45024b60d51
author: Shuhei Tanuma
email: chobieee@gmail.com
time: 1327164747

Hello World