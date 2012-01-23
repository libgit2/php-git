--TEST--
Check for Git2\TreeBuilder::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$bld = new Git2\TreeBuilder();

if ($bld instanceof Git2\TreeBuilder) {
	echo "OK";
}
--EXPECT--
OK
