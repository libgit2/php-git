<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 /*
 Git object id routines

 [*]git_oid_mkstr (git_hex_to_raw)
 [*]git_oid_mkraw (git_raw_to_hex)
 [-]git_oid_fmt   (not support)
 [-]git_oid_pathfmt(not support)
 [-]git_oid_allocfmt(not support)
 [-]git_oid_to_string(not support)
 [-]git_oid_cpy(not support)
 [-]git_oid_cmp(not support)

Git revision object management routines

 []git_object_write
 []git_object_id
 []git_object_type
 []git_object_owner
 []git_object_free
 []git_object_type2string
 []git_object_string2type
 []git_object_typeisloose
 */
 
 class GitFunctionsTest extends \PHPUnit_Framework_TestCase
 {
     protected function setUp()
     {
         // currentry nothing to do.
     }
     
     protected function tearDown()
     {
         // currentry nothing to do.
     }
     
     public function testHexToRaw()
     {
         $hex = "599955586da1c3ad514f3e65f1081d2012ec862d";
         $raw = git_hex_to_raw($hex);

         $this->assertEquals(
            "WZlVWG2hw61RTz5l8QgdIBLshi0=",
            base64_encode($raw),
            "Hex to raw conversion"
         );
     }
     
     public function testRawToHex()
     {
         $raw = base64_decode("WZlVWG2hw61RTz5l8QgdIBLshi0=");
         $hex = git_raw_to_hex($raw);
         
         $this->assertEquals(
             "599955586da1c3ad514f3e65f1081d2012ec862d",
             $hex,
             "Raw to hex conversion"
             );
     }
}