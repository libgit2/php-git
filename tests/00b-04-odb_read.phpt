--TEST--
Check for Git2\ODB::write
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/001-0b';
if (file_exists($path)) {
	`rm -rf {$path}`;
}

$repo = Git2\Repository::init($path,true);
$oid = $repo->odb->write("Hello World", 3);
echo $oid . PHP_EOL;
echo `GIT_DIR={$path} git cat-file blob 5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689` . PHP_EOL;
$odbobj = $repo->odb->read("5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689");
if ($odbobj instanceof Git2\ODBObject) {
	echo "OK" . PHP_EOL;
} else {
	echo "FAIL" . PHP_EOL;
}
echo $odbobj . PHP_EOL;
`rm -rf {$path}`;
--EXPECT--
5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689
Hello World
OK
Hello World