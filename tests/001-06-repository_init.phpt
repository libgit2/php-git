--TEST--
Check for Git2\Repository::init
--SKIPIF--
<?php if (!extension_loaded("git2")) print "skip"; ?>
--FILE--
<?php
$bare_path = __DIR__ . "/mock/001-06/bare";
if (file_exists($bare_path)) {
	`rm -rf {$bare_path}`;
}
$repo = Git2\Repository::init($bare_path,true);

$expected_files = array(
	"HEAD",
	"config",
	"objects",
	"objects/info",
	"objects/pack",
	"refs",
	"refs/heads",
	"refs/tags",
);

if (file_exists($bare_path)) {
	echo "OK" . PHP_EOL;
	foreach ($expected_files as $file) {
		if (file_exists($bare_path . "/{$file}")) {
			echo "OK" . PHP_EOL;
		} else {
			echo "FAIL: missing {$file}" . PHP_EOL;
		}
	}

	`rm -rf {$bare_path}`;
}
echo "END_BARE" . PHP_EOL;

$normal_path = __DIR__ . "/mock/001-06/normal";
if (file_exists($normal_path)) {
	`rm -rf {$normal_path}`;
}
$repo = Git2\Repository::init($normal_path);

$expected_files = array(
	".git",
	".git/HEAD",
	".git/config",
	".git/objects",
	".git/objects/info",
	".git/objects/pack",
	".git/refs",
	".git/refs/heads",
	".git/refs/tags",
);

if (file_exists($normal_path)) {
	echo "OK" . PHP_EOL;
	foreach ($expected_files as $file) {
		if (file_exists($normal_path . "/{$file}")) {
			echo "OK" . PHP_EOL;
		} else {
			echo "FAIL: missing {$file}" . PHP_EOL;
		}
	}

	`rm -rf {$normal_path}`;
}

--EXPECT--
OK
OK
OK
OK
OK
OK
OK
OK
OK
END_BARE
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
