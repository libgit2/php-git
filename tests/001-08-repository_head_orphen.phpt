--TEST--
Check for Git2\Repository::headOrphan
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . "/mock/001-08/orphaned";
$repo = new Git2\Repository($path);
if ($repo->headOrphan()) {
	echo "OK" . PHP_EOL;
} else {
	echo "NG" . PHP_EOL;
}
--EXPECT--
OK
