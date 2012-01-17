--TEST--
Check for Git2\Repository::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
echo "OK" . PHP_EOL;
try{
	$repo = new Git2\Repository("/path/doesnot/exist");
	echo "failed: path does not exit" . PHP_EOL;
} catch (\Exception $e) {
	echo "OK" . PHP_EOL;
}
--EXPECT--
OK
OK