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
        $git = new Git("./.git");
        $tree= $git->getTree("c40b970eb68bd1c8980f1f97b57396f4c7ae107f");
        $this->assertInstanceof("GitTree",$tree);
        $this->assertEquals("c40b970eb68bd1c8980f1f97b57396f4c7ae107f",$tree->getId());
     }
     
     public function testRepositoryInit()
     {
         $repo = Git::init("/tmp/uhi",1);
         $this->assertInstanceof("Git",$repo);
     }

     public function testConstruct()
     {
         try{
             $git = new Git("./.git");
         }catch(\Exception $e){
             $this->fail();
         }
     }
     
     public function testGetIndex()
     {

//        $this->markTestIncomplete("testGetIndex not implemented yet");

         $git = new Git("./.git");
         $index = $git->getIndex();
         if($index instanceof GitIndex){
             return true;
         }else{
             return false;
         }
     }
 }