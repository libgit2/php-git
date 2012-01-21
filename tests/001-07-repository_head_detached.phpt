--TEST--
Check for Git2\Repository::headDetached
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . "/mock/001-07/detached";
$repo = new Git2\Repository($path);
if ($repo->headDetached()) {
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
--EXPECT--
OK
