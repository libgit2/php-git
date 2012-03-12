--TEST--
Check for Git2\Config::__construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/fixtures/testrepo.git/config';
$config = new Git2\Config($path);
var_dump($config instanceof Git2\Config);
--EXPECT--
bool(true)