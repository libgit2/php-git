--TEST--
Check for Git2\TreeBuilder::construct
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$path = __DIR__ . '/mock/007-02';
if (file_exists($path)) {
	`rm -rf {$path}`;
}

$repo = Git2\Repository::init($path,true);

$bld = new Git2\TreeBuilder();
$bld->insert(new Git2\TreeEntry(array(
	"name" => "README.txt",
	"oid" => "63542fbea05732b78711479a31557bd1b0aa2116",
	"attributes" => 33188,
)));
$oid = $bld->write($repo);
echo $oid . PHP_EOL;
if (is_file($path . "/objects/75/b9737032278849da7e57829164a1265911afda")) {
  echo "PASS" . PHP_EOL;
} else {
  echo "FAIL" . PHP_EOL;
}
echo `GIT_DIR={$path} git ls-tree 75b9737032278849da7e57829164a1265911afda`;
`rm -rf {$path}`;
--EXPECT--
75b9737032278849da7e57829164a1265911afda
PASS
100644 blob 63542fbea05732b78711479a31557bd1b0aa2116	README.txt