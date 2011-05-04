--TEST--
Check git_string_to_type() function
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
$array = array("commit","tree","blob","tag");

foreach ($array as $key) {
  echo git_string_to_type($key) . PHP_EOL;
}

--EXPECT--
1
2
3
4