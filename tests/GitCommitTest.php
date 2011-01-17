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
         $commit = new Git\Commit(new Git\Repository(PHP_GIT_FIXTURE_DIR . "/fixture.git"));
         $commit->setAuthor(new Git\Signature("Someone Else","someone@example.com",new DateTime("@1293956764")));
         $author = $commit->getAuthor();
         $this->assertEquals("Someone Else",$author->name);
         $this->assertEquals("someone@example.com",$author->email);
         $this->assertEquals(1293956764,$author->time);
     }

     public function testGitCommitCommitterSignature()
     {
         $commit = new Git\Commit(new Git\Repository(PHP_GIT_FIXTURE_DIR . "/fixture.git"));
         $commit->setCommitter(new Git\Signature("Someone Else","someone@example.com",new DateTime("@1293956764")));
         $committer = $commit->getCommitter();
         $this->assertEquals("Someone Else",$committer->name);
         $this->assertEquals("someone@example.com",$committer->email);
         $this->assertEquals(1293956764,$committer->time);
     }

     public function testGitGetCommitFlomRepository()
     {
         $repository = new Git\Repository(".git");
         $commit = $repository->getCommit("1f27eed71970a0dbc0ca758f449e4b68c4c91bd8");
         $author = $commit->getAuthor();
         
         $this->assertEquals("Shuhei Tanuma",$author->name);
         $this->assertEquals("shuhei.tanuma@gmail.com",$author->email);
         
         $committer = $commit->getCommitter();
         $this->assertEquals("Shuhei Tanuma",$committer->name);
         $this->assertEquals("shuhei.tanuma@gmail.com",$committer->email);
         $this->assertEquals("1f27eed71970a0dbc0ca758f449e4b68c4c91bd8", $commit->getId());
     }
 }