--TEST--
Check for Git2\ODB::hash
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/001-0c';
if (file_exists($path)) {
	`rm -rf {$path}`;
}

$repo = Git2\Repository::init($path,true);
$oid = $repo->odb->hash("Hello World", 3);
echo $oid . PHP_EOL;
if (!file_exists($path . "/objects/5e/5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689")) {
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
`rm -rf {$path}`;
--EXPECT--
5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689
OK