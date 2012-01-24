--TEST--
Check for Git2\Config::__construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/fixtures/testrepo.git/config';
$config = new Git2\Config($path);
var_dump($config);
--EXPECT--
object(Git2\Config)#1 (1) {
  ["configs"]=>
  array(1) {
    ["core"]=>
    array(4) {
      ["repositoryformatversion"]=>
      string(1) "0"
      ["filemode"]=>
      string(4) "true"
      ["bare"]=>
      string(4) "true"
      ["ignorecase"]=>
      string(4) "true"
    }
  }
}