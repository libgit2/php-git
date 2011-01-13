<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 /*
 Git repository management routines

 [*]git_repository_open
 []git_repository_open2 (そのうち)
 []git_repository_lookup (そのうち)
 []git_repository_database (そのうち)
 [*]git_repository_index
 []git_repository_newobject(そのうち)
 [*]git_repository_free (internal)
 [*]git_repository_init
 */
 
 class GitTest extends \PHPUnit_Framework_TestCase
 {
     protected function setUp()
     {
         // currentry nothing to do.
     }
     
     protected function tearDown()
     {
         // currentry nothing to do.
     }
     
     public function testGetTree()
     {
        $git = new Git\Repository("./.git");
        $tree= $git->getTree("c40b970eb68bd1c8980f1f97b57396f4c7ae107f");
        $this->assertInstanceof("Git\\Tree",$tree);
        $this->assertEquals("c40b970eb68bd1c8980f1f97b57396f4c7ae107f",$tree->getId());
     }
     
     public function testRepositoryInit()
     {
         $repo = Git\Repository::init("/tmp/uhi",1);
         $this->assertEquals("/tmp/uhi",file_exists("/tmp/uhi"));
         $this->assertInstanceof("Git\\Repository",$repo);
     }

     public function testConstruct()
     {
         try{
             $git = new Git\Repository("./.git");
             $this->assertInstanceof("Git\\Repository",$git);
             unset($git);
         }catch(\Exception $e){
             $this->fail();
         }

         try{
             $git = new Git\Repository("./.git");
             $this->assertInstanceof("Git\\Repository",$git,"Git\\Repository::__construct allowed null parameter. refs #127");
         }catch(\Exception $e){
             $this->fail();
         }
     }
     
     public function testGetIndex()
     {

//        $this->markTestIncomplete("testGetIndex not implemented yet");

         $git = new Git\Repository("./.git");
         $index = $git->getIndex();
         if($index instanceof Git\Index){
             return true;
         }else{
             return false;
         }
     }
 }