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
        $repository = Repository::init(__DIR__ . self::REPOSITORY_NAME,false);
    }
    
    public static function teardownAfterClass()
    {
        self::rmdir(__DIR__ . self::REPOSITORY_NAME);
    }

    public function testGitAdd()
    {
        file_put_contents(__DIR__ . self::REPOSITORY_NAME . "/example","Hello World");
        
        $repository = new Repository(__DIR__ . self::REPOSITORY_NAME . "/.git");
        $index = $repository->getIndex();
        $index->add("example");
        $entry = $index->find("example");
        $this->assertEquals($entry->path, "example","couldn't add index");
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