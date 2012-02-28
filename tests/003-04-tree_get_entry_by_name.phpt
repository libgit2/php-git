--TEST--
Check for Git2\Tree::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
$tree = $repo->lookup("67dc4302383b2715f4e0b8c41840eb05b1873697");

$entry = $tree->getEntryByName("README");
var_dump($entry);
--EXPECT--
object(Git2\TreeEntry)#5 (3) {
  ["name"]=>
  string(6) "README"
  ["oid"]=>
  string(39) "557db03de997c86a4a028e1ebd3a1ceb225be23"
  ["attributes"]=>
  int(33188)
}
