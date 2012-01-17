--TEST--
Check for Git2\Repository::isEmpty
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-02");
if ($repo->isEmpty()) {
	echo "NG" . PHP_EOL;
} else {
	echo "OK" . PHP_EOL;
}
--EXPECT--
OK