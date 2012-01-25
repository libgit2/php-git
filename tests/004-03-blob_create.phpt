--TEST--
Check for Git2\Blob::__toString
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/fixtures/testrepo.git';
$repo = new Git2\Repository($path);
$id = Git2\Blob::create($repo, "Hello World");

if ($id == "5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689") {
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
--EXPECT--
OK
