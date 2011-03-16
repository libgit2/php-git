<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
class GitReferenceTest extends \PHPUnit_Framework_TestCase
{
    protected function setUp()
    {
        //this test still legacy. fix environment probrem soon
        $this->markTestSkipped();
    }

    protected function tearDown()
    {
        // currentry nothing to do.
    }

    /**
     * Repository can lookup Git Reference.
     */
    public function testGitRefrenceCanResolve()
    {
        $rep = new Git\Repository(dirname(__DIR__) . "/.git/");
        $reference = $rep->lookupRef("refs/heads/develop");
        $this->assertTrue($reference instanceof Git\Reference, 'returned object does not Git\\Reference');
    }


    /**
     * Reference can call getType()
     */
    public function testGitReferenceCanUseGetType()
    {
        $rep = new Git\Repository(dirname(__DIR__) . "/.git/");
        $ref = $rep->lookupRef("refs/heads/develop");
        $type = $ref->getType();
        $this->assertEquals(1,$type,"illegal reference type returned.(this is legacy test. check test file)");
    }

    /**
     * Reference can call getName();
     */
    public function testGitReferenceGetName()
    {
        $rep = new Git\Repository(dirname(__DIR__) . "/.git/");
        $ref = $rep->lookupRef("refs/heads/develop");
        $name = $ref->getName();

        $this->assertEquals("refs/heads/develop",$name,"reference name missmatched.");
    }

    /**
     * Reference can call getId();
     */
    public function testGitReferenceGetId()
    {
        $rep = new Git\Repository(dirname(__DIR__) . "/.git/");
        $ref = $rep->lookupRef("refs/heads/develop");
        $id = $ref->getId();

        $this->assertEquals(40,strlen($id),"illegal oid size returned");
    }


    /**
     * Reference failed when call getTarget();
     */
    public function testGitReferenceGetTarget()
    {
        $rep = new Git\Repository(dirname(__DIR__) . "/.git/");
        $ref = $rep->lookupRef("refs/heads/develop");
        try{
            $target = $ref->getTarget();
            $this->fail("something wrong. this method allowed symbolic reference only.");
        }catch(Exception $e){
            $this->assertTrue(true,"can't call getTarget method when lookup doesn't symbolic reference");
        }
    }
}