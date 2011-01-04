<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
class GitRevwalkTest extends \PHPUnit_Framework_TestCase
{
    protected function setUp()
    {
        // currentry nothing to do.
    }

    protected function tearDown()
    {
        // currentry nothing to do.
    }
    
    public function testGetWalker()
    {
        $git = new Git(".git");
        $walker = $git->getWalker();
        $this->assertInstanceOf("GitWalker",$walker);
        unset($git);
    }
    
    public function testPush()
    {
        $git = new Git(".git");
        $walker = $git->getWalker();
        $walker->push("1def80657903dcf8d9d87a5e4edfaca92ddcff38");
        $commit = $walker->next();
        $this->assertInstanceof("stdClass",$commit);
        unset($git);
    }
}