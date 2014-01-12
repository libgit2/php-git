--TEST--
Check for git_blob_create_frombuffer presence
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$repositroy = git_repository_init("/tmp/a");
echo git_blob_create_frombuffer($repositroy, "Helo World");

// TODO(chobie): we can't detect git_repository_new has correct odb now. fix this.
//$repositroy = git_repository_new();
//git_blob_create_frombuffer($repositroy, "Helo World");

--EXPECT--
826a9a65bc435bb1f1812433fa8fd5fa2ee9d678