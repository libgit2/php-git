--TEST--
Check for git_filter_list_new presence
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
echo "NOT YET";
--XFAIL--
NOT YET
--EXPECT--
