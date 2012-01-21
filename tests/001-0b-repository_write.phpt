--TEST--
Check for Git2\TreeBuilder::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/001-0b';
if (file_exists($path)) {
	`rm -rf {$path}`;
}

$repo = Git2\Repository::init($path,true);
$oid = $repo->write("Hello World", 3);
echo $oid . PHP_EOL;
echo `GIT_DIR={$path} git cat-file blob 5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689` . PHP_EOL;
$blob = $repo->lookup("5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689");
echo $blob . PHP_EOL;
`rm -rf {$path}`;
--EXPECT--
5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689
Hello World
Hello World