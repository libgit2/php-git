<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

require_once __DIR__ . "/lib/MemoryBackend.php";

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
        $this->assertTrue($odb instanceof Git\ODB);
    }

    /**
     * @depends testCheckMemcachedModule
     */
    public function testAddBackend()
    {
        $odb = new Git\ODB();
        $memcached = new Git\Backend\Memcached();
        $odb->addBackend($memcached,5);
        $this->assertTrue($odb instanceof Git\ODB);
    }

    public function testMemoryBackend()
    {

        $odb = new Git\ODB();
        $memory = new Git\Backend\Memory();
        $odb->addBackend($memory,5);
        $this->assertTrue($odb instanceof Git\ODB);
    }

    public function testAddAlternate()
    {

        $odb = new Git\ODB();
        $memory = new Git\Backend\Memory();
        $odb->addAlternate($memory,5);
        $this->assertTrue($odb instanceof Git\ODB);
    }
}