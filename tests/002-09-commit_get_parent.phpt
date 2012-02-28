--TEST--
Check for Git2\Commit::getCommitter
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
date_default_timezone_set('Asia/Tokyo');

$path2 = __DIR__ . '/mock/008-02';
$repo = new Git2\Repository($path2);
$commit = $repo->lookup("6e20138dc38f9f626107f1cd3ef0f9838c43defe");

$parent = $commit->getParent();
var_dump($parent->getOid());
var_dump($parent->getMessage());
--EXPECT--
string(40) "9bb8c853c9ea27609a6bdc48b78cd26a320daf7d"
string(16) "added section 1
"