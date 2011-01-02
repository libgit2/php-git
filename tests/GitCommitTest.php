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
/*
        //passed
         $commit = new GitCommit();
         $commit->setAuthor(new GitSignature("Someone Else","someone@example.com",1293956764));
         $author = $commit->getAuthor();
         $this->assertEquals("Someone Else",$author->name);
         $this->assertEquals("someone@example.com",$author->email);
         $this->assertEquals(1293956764,$author->time);
*/
     }

     public function testGitCommitCommitterSignature()
     {
/*
        //passed
         $commit = new GitCommit();
         $commit->setCommitter(new GitSignature("Someone Else","someone@example.com",1293956764));
         $committer = $commit->getCommitter();
         $this->assertEquals("Someone Else",$committer->name);
         $this->assertEquals("someone@example.com",$committer->email);
         $this->assertEquals(1293956764,$committer->time);
*/
     }

 }