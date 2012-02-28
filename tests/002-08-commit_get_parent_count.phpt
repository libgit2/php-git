--TEST--
Check for Git2\Commit::getCommitter
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
date_default_timezone_set('Asia/Tokyo');
$path = __DIR__ . '/mock/001-01';

$repo = new Git2\Repository($path);
$commit = $repo->lookup("ab68c54212af15d3545c41057e3a8f2f9ff6fd0d");


var_dump($commit->getParentCount());

$path2 = __DIR__ . '/mock/008-02';
$repo = new Git2\Repository($path2);
$commit = $repo->lookup("6e20138dc38f9f626107f1cd3ef0f9838c43defe");

var_dump($commit->getParentCount());

--EXPECT--
int(0)
int(1)