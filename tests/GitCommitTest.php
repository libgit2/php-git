<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 class GitCommitTest extends \PHPUnit_Framework_TestCase
 {
     protected function setUp()
     {
         // currentry nothing to do.
     }
     
     protected function tearDown()
     {
         // currentry nothing to do.
     }
     
     public function testGitCommitAuthorSignature()
     {
         $commit = new GitCommit();
         $commit->setAuthor(new GitSignature("Someone Else","someone@example.com",1293956764));
         $this->assertEquals("Someone Else",$commit->author->name);
         $this->assertEquals("someone@example.com",$commit->author->email);
         $this->assertEquals(1293956764,$commit->author->time);
     }

     public function testGitCommitCommitterSignature()
     {
         $commit = new GitCommit();
         $commit->setCommitter(new GitSignature("Someone Else","someone@example.com",1293956764));
         $this->assertEquals("Someone Else",$commit->committer->name);
         $this->assertEquals("someone@example.com",$commit->committer->email);
         $this->assertEquals(1293956764,$commit->committer->time);
     }

 }