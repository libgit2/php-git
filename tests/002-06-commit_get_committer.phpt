--TEST--
Check for Git2\Commit::getCommitter
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
date_default_timezone_set('Asia/Tokyo');
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
$commit = $repo->lookup("ab68c54212af15d3545c41057e3a8f2f9ff6fd0d");

$signature = $commit->getCommitter();
printf("name: %s\n", $signature->name);
printf("email: %s\n", $signature->email);
printf("time: %s\n", $signature->time->format("Y-m-d H:i:s"));
--EXPECT--
name: Shuhei Tanuma
email: shuhei.tanuma@gmail.com
time: 2012-01-17 21:50:45