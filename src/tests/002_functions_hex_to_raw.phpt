--TEST--
Check git_hex_to_raw() function
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
$hash = "599955586da1c3ad514f3e65f1081d2012ec862d";
echo base64_encode(git_hex_to_raw($hash));
--EXPECT--
WZlVWG2hw61RTz5l8QgdIBLshi0=