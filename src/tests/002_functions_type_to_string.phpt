--TEST--
Check git_type_to_string() function
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
$array = array(Git\Object\Commit,Git\Object\Tree,Git\Object\Blob,Git\Object\Tag);

foreach ($array as $key) {
  echo git_type_to_string($key) . PHP_EOL;
}

--EXPECT--
commit
tree
blob
tag