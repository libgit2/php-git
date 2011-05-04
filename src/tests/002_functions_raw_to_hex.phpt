--TEST--
Check git_raw_to_hex() function
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
$raw = base64_decode("WZlVWG2hw61RTz5l8QgdIBLshi0=");
echo git_raw_to_hex($raw);
--EXPECT--
599955586da1c3ad514f3e65f1081d2012ec862d