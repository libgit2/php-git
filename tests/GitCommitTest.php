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
        $this->assertEquals(1293956764,$author->time->getTimestamp());
    }

    public function testGitCommitCommitterSignature()
    {
        $commit = new Git\Commit(new Git\Repository(PHP_GIT_FIXTURE_DIR . "/fixture.git"));
        $commit->setCommitter(new Git\Signature("Someone Else","someone@example.com",new DateTime("@1293956764")));
        $committer = $commit->getCommitter();
        $this->assertEquals("Someone Else",$committer->name);
        $this->assertEquals("someone@example.com",$committer->email);
        $this->assertEquals(1293956764,$committer->time->getTimestamp());
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
        
        $tree = $commit->getTree();
        $entry1 = $tree->getEntry(0);
        $this->assertEquals("EXPERIMENTAL",$entry1->name);
        $this->assertEquals("35a136e7e190505e46367a04f730e827062b13cc",$entry1->oid);

        $entry2 = $tree->getEntry(1);
        $this->assertEquals("README.md",$entry2->name);
        $this->assertEquals("a1a07d27e9d8a78e3bc6fb8a6d8308d358ff9b07",$entry2->oid);
        
        $commit = $repository->getCommit("bba0bb972cbdc72d908ebd7c89157d7e207f5e92");
        $parent = $commit->getParent();
        $this->assertEquals("b500d73e7125ae105ce125b96390ad09d6174629",$parent->getId());

        $author = $parent->getAuthor();
        $this->assertEquals("Shuhei Tanuma",$author->name);
        $this->assertEquals("shuhei.tanuma@gmail.com",$author->email);

        $committer = $parent->getCommitter();
        $this->assertEquals("Shuhei Tanuma",$committer->name);
        $this->assertEquals("shuhei.tanuma@gmail.com",$committer->email);
    }
}