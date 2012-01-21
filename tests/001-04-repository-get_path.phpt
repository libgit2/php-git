--TEST--
Check for Git2\Repository::getPath
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
if ($repo->getPath() == __DIR__ . "/mock/001-01/") {
	/* getPath should add DIRECTORY_SEPARATOR at last */
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
--EXPECT--
OK
