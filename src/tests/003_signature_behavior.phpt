--TEST--
Check Git\Signature behavior
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
 $signature = new Git\Signature("Name","sample@example.com",new Datetime("@1294147094"));
 
echo $signature->name . PHP_EOL;
echo $signature->email . PHP_EOL;
echo $signature->time->getTimestamp() . PHP_EOL;

--EXPECT--
Name
sample@example.com
1294147094