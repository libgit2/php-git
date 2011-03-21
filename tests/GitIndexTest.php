<?php
/*
* This file is part of the PECL_Git package.
* (c) Shuhei Tanuma
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

use Git\Repository;

class GitIndexTest extends \PHPUnit_Framework_TestCase
{
    const REPOSITORY_NAME = "/git_index_test";
    
    public static function setupBeforeClass()
    {
        if(is_dir(__DIR__ . self::REPOSITORY_NAME)){
            self::rmdir(__DIR__ . self::REPOSITORY_NAME);
        }
        Repository::init(__DIR__ . self::REPOSITORY_NAME,false);
    }
    
    public static function teardownAfterClass()
    {
        self::rmdir(__DIR__ . self::REPOSITORY_NAME);
    }

    public function testGetIndex()
    {
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $this->assertInstanceOf("Git\\Index",$index);
    }


    public function testAddIndex()
    {
        file_put_contents(__DIR__ . self::REPOSITORY_NAME . "/example","Hello World");
        
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $index->add("example");
        $entry = $index->find("example");
        $this->assertEquals($entry->path, "example","couldn't add index");
        $index->refresh();
    }
    
    public function testWriteIndex()
    {
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $index->add("example");
        $index->write();
        $data = file_get_contents(__DIR__ . self::REPOSITORY_NAME . "/.git/index");
        $this->assertTrue((strpos($data,"example") !== false),"couldn't write index");
    }

    public function testRemoveIndex()
    {
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $index->add("example");
        $index->remove("example");
        $index->write();
        $data = file_get_contents(__DIR__ . self::REPOSITORY_NAME . "/.git/index");
        $this->assertTrue((strpos($data,"example") === false),"couldn't remove index");
    }

    public function testGetEntry()
    {
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $index->add("example");
        $index->write();
        $entry = $index->getEntry(0);
        $this->assertEquals($entry->path,"example","couldn't get specified index");
    }
    
    public function testGetIterator()
    {
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $index->add("example");
        $index->write();
        $it = $index->getIterator();
        
        $this->assertInstanceOf("Iterator",$it);
    }
    
    public static function rmdir($dir)
    {
       if (is_dir($dir)) { 
         $objects = scandir($dir); 
         foreach ($objects as $object) { 
           if ($object != "." && $object != "..") { 
             if (filetype($dir."/".$object) == "dir") self::rmdir($dir."/".$object); else unlink($dir."/".$object); 
           } 
         } 
         reset($objects); 
         rmdir($dir); 
       } 
    }
}