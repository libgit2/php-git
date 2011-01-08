<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 class GitSignatureTest extends \PHPUnit_Framework_TestCase
 {
     protected function setUp()
     {
         // currentry nothing to do.
     }
     
     protected function tearDown()
     {
         // currentry nothing to do.
     }
     
     public function testSignatureConstruct()
     {
         $signature = new Git\Signature("Name","sample@example.com",1294147094);
         
         $this->assertEquals("Name",$signature->name);
         $this->assertEquals("sample@example.com",$signature->email);
         $this->assertEquals(1294147094,$signature->time);
     }
 }