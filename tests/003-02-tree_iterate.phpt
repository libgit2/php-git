--TEST--
Check for Git2\Tree::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
$tree = $repo->lookup("67dc4302383b2715f4e0b8c41840eb05b1873697");

foreach ($tree as $entry) {
	echo $entry->name . PHP_EOL;
	echo $entry->oid . PHP_EOL;
	echo $entry->attributes . PHP_EOL;
}
--EXPECT--
README
557db03de997c86a4a028e1ebd3a1ceb225be23
33188