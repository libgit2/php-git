<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
class GitBackendTest extends \PHPUnit_Framework_TestCase
{
    protected function setUp()
    {
    }
     
    protected function tearDown()
    {
        // currentry nothing to do.
    }
    
    public function testReadMethodExists()
    {
        $reflection = new \ReflectionClass("Git\\Backend");
        $method = $reflection->getMethod("read");
        $this->assertEquals(true,$method->isPublic());

        $parameters = $method->getParameters();

        $this->assertEquals(1,count($parameters));
        $this->assertEquals("key",$parameters[0]->getname());
    }

    public function testWriteMethodExists()
    {
        $reflection = new \ReflectionClass("Git\\Backend");
        $method = $reflection->getMethod("write");
        $this->assertEquals(true,$method->isPublic());

        $parameters = $method->getParameters();

        $this->assertEquals(1,count($parameters));
        $this->assertEquals("object",$parameters[0]->getname());
    }

    public function testExistsMethodExists()
    {
        $reflection = new \ReflectionClass("Git\\Backend");
        $method = $reflection->getMethod("exists");
        $this->assertEquals(true,$method->isPublic());

        $parameters = $method->getParameters();

        $this->assertEquals(1,count($parameters));
        $this->assertEquals("key",$parameters[0]->getname());
    }

    public function testReadHeaderMethodExists()
    {
        $reflection = new \ReflectionClass("Git\\Backend");
        $method = $reflection->getMethod("read_header");
        $this->assertEquals(true,$method->isPublic());

        $parameters = $method->getParameters();

        $this->assertEquals(1,count($parameters));
        $this->assertEquals("key",$parameters[0]->getname());
    }

    public function testConstructMethodExists()
    {
        $reflection = new \ReflectionClass("Git\\Backend");
        $method = $reflection->getMethod("__construct");
        $this->assertEquals(true,$method->isPublic());

        $parameters = $method->getParameters();

        $this->assertEquals(1,count($parameters));
        $this->assertEquals("priority",$parameters[0]->getname());
    }
}
