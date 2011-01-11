<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 class GitTagTest extends \PHPUnit_Framework_TestCase
 {
     protected function setUp()
     {
         // currentry nothing to do.
     }
     
     protected function tearDown()
     {
         // currentry nothing to do.
     }
     
     public function testGitTagSetMessageGetMessage()
     {
         $repo = new Git\Repository("./.git");
         $tag = new Git\Tag($repo);
         $tag->setMessage("Hello World");
         $this->assertEquals("Hello World", $tag->getMessage());
     }

     public function testGitTagSetNameGetName()
     {
         $repo = new Git\Repository("./.git");
         $tag = new Git\Tag($repo);
         $tag->setName("version 1.0");
         $this->assertEquals("version 1.0", $tag->getName());
     }

 }