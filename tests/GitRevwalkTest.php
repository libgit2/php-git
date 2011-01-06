<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
/*
Git revision traversal routines

[*]git_revwalk_new (Implemented at Git::getWalker)
[*]git_revwalk_reset
[*]git_revwalk_push
[*]git_revwalk_hide
[*]git_revwalk_sorting
[]git_revwalk_free
[-]git_revwak_repository (not support)

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
        $git = new GitRepository(".git");
        $walker = $git->getWalker();
        $this->assertInstanceOf("GitWalker",$walker);
        unset($git);
    }
    
    public function testPush()
    {
        $git = new GitRepository(".git");
        $walker = $git->getWalker();
        $walker->push("1def80657903dcf8d9d87a5e4edfaca92ddcff38");
        $commit = $walker->next();
        $this->assertInstanceof("stdClass",$commit);
        unset($git);
    }
    
    public function testRest()
    {
        $git = new GitRepository(".git");
        $walker = $git->getWalker();
        $walker->push("1def80657903dcf8d9d87a5e4edfaca92ddcff38");
        $walker->reset();
    }

    public function testSort()
    {
        /*
            Git::SORT_NONE
            Git::SORT_TOPO
            Git::SORT_DATE
            Git::SORT_REVERSE
            先にPHPのarrayにしてuserspaceでの対応にするか悩む
        */
        $git = new GitRepository(".git");
        $walker = $git->getWalker();
        $walker->sort(Git::SORT_NONE);
        $walker->push("1def80657903dcf8d9d87a5e4edfaca92ddcff38");
        $this->assertInstanceof("stdClass",$walker->next());
    }
}