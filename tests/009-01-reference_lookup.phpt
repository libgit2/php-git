--TEST--
Check for Git2\Reference::lookup
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/001-01';
$repo = new Git2\Repository($path);
$ref = Git2\Reference::lookup($repo, "refs/heads/master");
echo $ref->getName() . PHP_EOL;
echo $ref->getTarget() . PHP_EOL;
--EXPECT--
refs/heads/master
ab68c54212af15d3545c41057e3a8f2f9ff6fd0d