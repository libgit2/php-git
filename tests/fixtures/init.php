<?php
$repo = new Git2\Repository(__DIR__ . "/fixtures/testrepo.git");
$oids = array();
$oids[] = $repo->write("Hello World",3);
$oids[] = $repo->write("Hello Chobie",3);
$oids[] = $repo->write("this is chobie",3);
$oids[] = $repo->write("moe is Japanese word",3);

foreach ($oids as $oid) {
	echo $oid . PHP_EOL;
}

/*
e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689
a08e8505259a0ab4474ca79ba92bd7912b5a32c3
87cef34f1a5c8d386418e9fa3e8948ef7322a007
ca06beddccb5d9eb9bf4787ef42407a438b3abf1
*/

$builder = new Git2\TreeBuilder();
$builder->insert(new Git2\TreeEntry(array(
		"name" => "README",
		"oid" => "e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689",
		"attributes" => 33188,
)));
$oid = $builder->write($repo);
echo $oid . PHP_EOL;
/*
	199e7c128125a430899fc5c1c0bd08699c9a5692
*/

$builder = new Git2\TreeBuilder();
$i = 0;
$builder->insert(new Git2\TreeEntry(array(
		"name" => "$i",
		"oid" => "e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689",
		"attributes" => 33188,
)));
$oid = $builder->write($repo);
echo $oid . PHP_EOL;

/*
 2c83838315fd649b17e968e96e9d4543c9efd1e9
*/

$builder = new Git2\TreeBuilder();
for($i = 0;$i<1000;$i++){
$builder->insert(new Git2\TreeEntry(array(
		"name" => "$i",
		"oid" => "e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689",
		"attributes" => 33188,
)));
}
$oid = $builder->write($repo);
echo $oid . PHP_EOL;
// 74edf90112fadb1c0ea2dc48352e0ed4ead2e1cf
