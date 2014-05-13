<?php


function recurse_copy($src,$dst) {
	$dir = opendir($src);
	@mkdir($dst);
	while(false !== ( $file = readdir($dir)) ) {
		if (( $file != '.' ) && ( $file != '..' )) {
			if ( is_dir($src . '/' . $file) ) {
				recurse_copy($src . '/' . $file,$dst . '/' . $file);
			}
			else {
				copy($src . '/' . $file,$dst . '/' . $file);
			}
		}
	}
	closedir($dir);
}


function init_repo($reponame, $target, $bare = false)
{
	$rootPath = dirname(__DIR__);
	$libgitPath = $rootPath . '/libgit2';
	$testRepoPath = $libgitPath . '/tests/resources';

	if (!file_exists($testRepoPath))
	{
		throw new Exception('test repository assets not found at '.$testRepoPath);
	}

	$repoPath = $testRepoPath . '/' . $reponame;


	if (!file_exists($repoPath))
	{
		throw new Exception('test repository '. $reponame.' assets not found');
	}

	@mkdir($target);
	recurse_copy($repoPath, $target.'/'.$reponame);

	if (!$bare)
	{
		$oldPath =$target.'/'.$reponame.'/.gitted';

		$newPath =$target.'/'.$reponame.'/.git';

		rename($oldPath, $newPath);
	}

}