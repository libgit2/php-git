--TEST--
Check for git_blob_create_frombuffer presence
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repositroy = git_repository_init("/tmp/a");
echo git_blob_create_frombuffer($repositroy, "Helo World");

$repositroy = git_repository_new();
$result = @git_blob_create_frombuffer($repositroy, "Helo World");
if (is_null($result)) {
	echo "OK" . PHP_EOL;
}
--EXPECT--
826a9a65bc435bb1f1812433fa8fd5fa2ee9d678
OK