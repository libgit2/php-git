--TEST--
Check for Git2\Config::get
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/fixtures/testrepo.git/config';
$config = new Git2\Config($path);
echo $config->get("core.repositoryformatversion") . PHP_EOL;
echo $config->get("core.filemode") . PHP_EOL;
echo $config->get("core.bare") . PHP_EOL;
echo $config->get("core.ignorecase") . PHP_EOL;
echo ($config->get("core") == array("repositoryformatversion"=>"0","filemode"=>"true","bare"=>"true","ignorecase"=>"true")) ? "OK\n" : "FAIL\n";
echo ($config->get("") == false)  ? "OK\n" : "FAIL\n";
echo ($config->get("core.uhi") == false)  ? "OK\n" : "FAIL\n";
--EXPECT--
0
true
true
true
OK
OK
OK