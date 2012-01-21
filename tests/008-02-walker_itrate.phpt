--TEST--
Check for Git2\Walker::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/008-02';
$repo = new Git2\Repository($path);
$walker = new Git2\Walker($repo);
$walker->push("6e20138dc38f9f626107f1cd3ef0f9838c43defe");

foreach ($walker as $oid => $commit) {
	printf("oid: %s\n", $oid);
	printf("message: %s\n", $commit->getMessage());
}
--EXPECT--
oid: 6e20138dc38f9f626107f1cd3ef0f9838c43defe
message: added section 1 contents

oid: 9bb8c853c9ea27609a6bdc48b78cd26a320daf7d
message: added section 1

oid: 7fce1026cb624448e5a8cf8752bd5e19d8f2cb1f
message: modified README

oid: ffc6c773865c1342db9cd5df5777fc91ddeb8a4d
message: initial commit