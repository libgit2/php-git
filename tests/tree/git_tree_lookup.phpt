--TEST--
Check for git_tree_lookup
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
	include_once(__DIR__ . '/../init.php');
	$path = "/tmp/git-tree-lookup";
	$testRepo = 'testrepo';
	init_Repo($testRepo, $path);
	$repositroy = git_repository_open($path . '/' . $testRepo);

	$fileHash = '6336846bd5c88d32f93ae57d846683e61ab5c530';
	$treeHash = '1810dff58d8a660512d4832e740f692884338ccd';



	$tree = git_tree_lookup($repositroy, $treeHash);
	if (is_resource($tree)) {
		echo "TREE: $treeHash OK" . PHP_EOL;
	}
	else
	{
		echo "TREE: $treeHash FAIL" . PHP_EOL;
	}

	$tree = @git_tree_lookup($repositroy, $fileHash);
	if ($tree===null) {
		echo "FILE: $fileHash OK" . PHP_EOL;
	}
	else
	{
		echo "FILE: $fileHash FAIL" . PHP_EOL;
	}
--EXPECT--
TREE: 1810dff58d8a660512d4832e740f692884338ccd OK
FILE: 6336846bd5c88d32f93ae57d846683e61ab5c530 FAIL
