<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

use Git\Repository;

class GitTreeTest extends \PHPUnit_Framework_TestCase
{
    protected function setUp()
    {
        // currentry nothing to do.
    }
    
    protected function tearDown()
    {
        // currentry nothing to do.
    }
    
    public function testConstruct()
    {
        try{
          $git = new Repository(PHP_GIT_FIXTURE_DIR . "/fixture.git");
          $commit = $git->getCommit("7caa5b63e5fe4596543378e47b5225b6a1fa2dee");
        }catch(\Exception $e){
           $this->fail();
        }
        unset($git);
    }

    public function testCount()
    {
        try{
          $repository = new Repository("./.git");
          $tree = $repository->getTree("8b230bc64e9384f6cedc9c8128270c30635571a7");
          $this->assertEquals(2,count($tree));
        }catch(\Exception $e){
           $this->fail();
        }
        unset($git);
    }

    public function testPath()
    {
        try{
          $repository = new Repository("./.git");
          $tree = $repository->getTree("f031269837fabfa2c63e7a37b000a91171855f3f");
          $object = $tree->path("EXPERIMENTAL");
          $this->assertInstanceof("Git\\Blob",$object,"couldn't get specified blob object");
          $this->assertEquals("80afdcd19e73e8e39757ebcdebedbf8fee2ebfc1",$object->getId());
          $object = $tree->path("docs");
          $this->assertInstanceof("Git\\Tree",$object,"couldn't get specified tree object");
        }catch(\Exception $e){
           $this->fail();
        }
        unset($git);
    }
    
    public function testGetIterator()
    {
          $repository = new Repository("./.git");
          $tree = $repository->getTree("f031269837fabfa2c63e7a37b000a91171855f3f");
          $itr = $tree->getIterator();
          
          $this->assertInstanceOf("Iterator",$itr,"can't get iterator object");
    }
    
    public function testGetEntries()
    {
          $repository = new Repository("./.git");
          $tree = $repository->getTree("f031269837fabfa2c63e7a37b000a91171855f3f");
          $this->assertEquals(10, count($tree->getEntries()),"can't get specified entries");
    }
    
    public function testGetEntry()
    {
          $repository = new Repository("./.git");
          $tree = $repository->getTree("f031269837fabfa2c63e7a37b000a91171855f3f");
          $this->assertEquals("tests", $tree->getEntry(9)->name,"can't get specified entry");
    }

 }