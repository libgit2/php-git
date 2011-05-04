--TEST--
Check for php-git presence
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
echo "php-git extension is available";
--EXPECT--
php-git extension is available