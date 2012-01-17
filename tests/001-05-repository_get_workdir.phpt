--TEST--
Check for Git2\Repository::getWorkdir
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
if ($repo->getWorkdir() == "") {
	echo "OK" . PHP_EOL;
} else {
	echo "NG" . PHP_EOL;
}
--EXPECT--
OK