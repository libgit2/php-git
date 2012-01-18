--TEST--
Check for Git2\Repository::headOrphan
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . "/mock/001-01/refs/heads";
$discovered = Git2\Repository::discover($path);
if ($discovered == __DIR__ . "/mock/001-01/") {
	echo "OK" . PHP_EOL;
} else {
	echo "NG" . PHP_EOL;
}
--EXPECT--
OK
