<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
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
            $git = new Git\Repository(PHP_GIT_FIXTURE_DIR . "/fixture.git");
            $commit = $git->getCommit("7caa5b63e5fe4596543378e47b5225b6a1fa2dee");
         }catch(\Exception $e){
             $this->fail();
         }
         unset($git);
     }

     public function testCount()
     {
         try{
            $repository = new Git\Repository("./.git");
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
            $repository = new Git\Repository("./.git");
            $tree = $repository->getTree("f031269837fabfa2c63e7a37b000a91171855f3f");
            $object = $tree->path("EXPERIMENTAL");
            $this->assertInstanceof("Git\\Blob",$object,"正しくblobが取れている");
            $this->assertEquals("2d76dd497c3179cc25cf676cdde1739c25eaca9a",sha1($object->data));
            $object = $tree->path("docs");
            $this->assertInstanceof("Git\\Tree",$object,"正しくtreeが取れている");
         }catch(\Exception $e){
             $this->fail();
         }
         unset($git);
     }

 }