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
            $git = new GitRepository(PHP_GIT_FIXTURE_DIR . "/fixture.git");
            $commit = $git->getCommit("7caa5b63e5fe4596543378e47b5225b6a1fa2dee");
         }catch(\Exception $e){
             $this->fail();
         }
         unset($git);
     }
 }