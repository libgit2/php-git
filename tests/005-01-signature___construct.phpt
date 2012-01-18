--TEST--
Check for Git2\Signature::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$sig = new Git2\Signature(
	"Shuhei Tanuma",
	 "chobieee@gmail.com",
	new DateTime("2012-01-19 00:32:32", new DateTimeZone("Asia/Tokyo")));

echo $sig->name . PHP_EOL;
echo $sig->email . PHP_EOL;
echo $sig->time->format("Y-m-d H:i:s") . PHP_EOL;

--EXPECT--
Shuhei Tanuma
chobieee@gmail.com
2012-01-19 00:32:32