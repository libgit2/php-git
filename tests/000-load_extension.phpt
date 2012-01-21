--TEST--
Check for Git2 Presence
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
echo "git2 extension is available";
--EXPECT--
git2 extension is available
