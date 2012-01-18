--TEST--
Check for Git2\Blob::__toString
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repo = new Git2\Repository(__DIR__ . "/mock/001-01");
$blob = $repo->lookup("557db03de997c86a4a028e1ebd3a1ceb225be238");

if ($blob instanceof Git2\Blob) {
	echo $blob->__toString();
} else {
	echo "NG" . PHP_EOL;
}
--EXPECT--
Hello World