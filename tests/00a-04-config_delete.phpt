--TEST--
Check for Git2\Config::get
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/fixtures/testrepo.git/config';
$data = file_get_contents($path);
$path = __DIR__ . '/fixtures/testrepo.git/config.test';
file_put_contents($path,$data);

$config = new Git2\Config($path);
echo $config->get("core.bare") . PHP_EOL;
$config->delete("core.bare");
var_dump($config->get("core.bare"));
//for now, recursive delete does not support.
//$config->delete("core");
//var_dump($config->get("core"));
unlink($path);
--EXPECT--
true
NULL