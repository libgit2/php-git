--TEST--
Check for Git2\Walker::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/001-01';
$repo = new Git2\Repository($path);
$walker = new Git2\Walker($repo);
if ($walker instanceof Git2\Walker) {
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
--EXPECT--
OK
