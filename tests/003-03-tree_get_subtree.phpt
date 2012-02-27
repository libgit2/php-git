--TEST--
Check for Git2\Tree::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/003-03");
$tree = $repo->lookup("451cad1f3affaf6e3159c7c85d9ce9a21e21993d");

var_dump($tree->getSubtree(""));
var_dump($tree->getSubtree("a"));
var_dump($tree->getSubtree("a/b"));
var_dump($tree->getSubtree("a/c"));

--EXPECT--
bool(false)
object(Git2\Tree)#5 (1) {
  ["entries"]=>
  array(1) {
    [0]=>
    object(Git2\TreeEntry)#6 (3) {
      ["name"]=>
      string(1) "b"
      ["oid"]=>
      string(40) "a2c260d5a5c3a4b9f4247433b89dd0069fce423f"
      ["attributes"]=>
      int(16384)
    }
  }
}
object(Git2\Tree)#5 (1) {
  ["entries"]=>
  array(1) {
    [0]=>
    object(Git2\TreeEntry)#6 (3) {
      ["name"]=>
      string(1) "c"
      ["oid"]=>
      string(40) "bc2b542422510d8b23eae97ede32dc2d5fa13c90"
      ["attributes"]=>
      int(16384)
    }
  }
}
bool(false)