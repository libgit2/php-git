--TEST--
Check for Git2\Tree::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
$tree = $repo->lookup("67dc4302383b2715f4e0b8c41840eb05b1873697");

if ($tree instanceof Git2\Tree) {
	echo "OK" . PHP_EOL;
} else {
	echo "NG" . PHP_EOL;
}
--EXPECT--
OK