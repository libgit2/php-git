--TEST--
Check for Git2\TreeEntry::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$entry = new Git2\TreeEntry(array(
	"name" => "README.txt",
	"oid" => "63542fbea05732b78711479a31557bd1b0aa2116",
	"attributes" => 33188,
));

echo $entry->name . PHP_EOL;
echo $entry->oid . PHP_EOL;
echo $entry->attributes . PHP_EOL;
--EXPECT--
README.txt
63542fbea05732b78711479a31557bd1b0aa2116
33188
