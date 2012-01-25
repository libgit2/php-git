--TEST--
Check for Git2\TreeEntry::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/fixtures/testrepo.git';
$repo = new Git2\Repository($path);

$tree = $repo->lookup("199e7c128125a430899fc5c1c0bd08699c9a5692");
foreach ($tree as $entry) {
	if ($entry->isBlob()) {
		echo "OK" . PHP_EOL;
	} else {
		echo "FAIL" . PHP_EOL;
	}
}
--EXPECT--
OK