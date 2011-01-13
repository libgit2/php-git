<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

class GitODBTest extends \PHPUnit_Framework_TestCase
{
    protected function setUp()
    {
        // currentry nothing to do.
    }
    
    protected function tearDown()
    {
        // currentry nothing to do.
    }
    
    public function testCheckMemcachedModule()
    {
        $this->assertEquals(true,extension_loaded("memcached"));
        require_once __DIR__ . "/lib/MemcachedBackend.php";
    }
    
    /**
     * @depends testCheckMemcachedModule
     */
    public function testConstruct()
    {
        $odb = new Git\ODB();
        $this->assertInstanceof("Git\\ODB",$odb);
    }

    /**
     * @depends testCheckMemcachedModule
     */
    public function testAddBackend()
    {
        $odb = new Git\ODB();
        $memcached = new Git\Backend\Memcached(5);
        $odb->addBackend($memcached);
        $this->assertInstanceof("Git\\ODB",$odb);
    }

}