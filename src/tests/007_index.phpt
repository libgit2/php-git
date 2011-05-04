--TEST--
Check Git\Index behavior
--SKIPIF--
<?php if (!extension_loaded("git")) print "skip"; ?>
--FILE--
<?php
use Git\Repository;

function tmp_rmdir($dir)
{
    if (is_dir($dir)) { 
        $objects = scandir($dir); 
        foreach ($objects as $object) { 
            if ($object != "." && $object != "..") { 
                if (filetype($dir."/".$object) == "dir") tmp_rmdir($dir."/".$object); else unlink($dir."/".$object); 
            }
        }
        reset($objects);
        rmdir($dir);
    }
}


define("REPOSITORY_NAME","/git_index_test");

if(is_dir(__DIR__ . REPOSITORY_NAME)){
    tmp_rmdir(__DIR__ . REPOSITORY_NAME);
}
Repository::init(__DIR__ . REPOSITORY_NAME,false);


$repository = new Repository(__DIR__ . REPOSITORY_NAME . "/.git");
$index = $repository->getIndex();
echo ($index instanceof Git\Index) ? "true" : "false";
echo PHP_EOL;

file_put_contents(__DIR__ . REPOSITORY_NAME . "/example","Hello World");
$repository = new Repository(__DIR__ . REPOSITORY_NAME . "/.git");
$index = $repository->getIndex();
$index->add("example");
$entry = $index->find("example");
echo ($entry->path == "example") ? "ok": "couldn't add index";
echo PHP_EOL;
$index->refresh();


$repository = new Repository(__DIR__ . REPOSITORY_NAME . "/.git");
$index = $repository->getIndex();
$index->add("example");
$index->write();
$data = file_get_contents(__DIR__ . REPOSITORY_NAME . "/.git/index");
echo (strpos($data,"example") !== false) ? "ok" : "couldn't write index";
echo PHP_EOL;



$repository = new Repository(__DIR__ . REPOSITORY_NAME . "/.git");
$index = $repository->getIndex();
$index->add("example");
$index->remove("example");
$index->write();
$data = file_get_contents(__DIR__ . REPOSITORY_NAME . "/.git/index");
echo (strpos($data,"example") === false) ? "ok" : "couldn't remove index";
echo PHP_EOL;


$repository = new Repository(__DIR__ . REPOSITORY_NAME . "/.git");
$index = $repository->getIndex();
$index->add("example");
$index->write();
$entry = $index->getEntry(0);
echo ($entry->path == "example") ? "ok" : "couldn't get specified index";
echo PHP_EOL;


$repository = new Repository(__DIR__ . REPOSITORY_NAME . "/.git");
$index = $repository->getIndex();
$index->add("example");
$index->write();
$it = $index->getIterator();
echo ($it instanceof Iterator) ? "ok" : "couldn't get iterator instance";


tmp_rmdir(__DIR__ . REPOSITORY_NAME);

--EXPECT--
true
ok
ok
ok
ok
ok