--TEST--
Check for Git2\Commit::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
$commit = $repo->lookup("ab68c54212af15d3545c41057e3a8f2f9ff6fd0d");

if ($commit instanceof Git2\Commit) {
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
--EXPECT--
OK
