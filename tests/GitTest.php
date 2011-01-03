<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 class GitTest extends \PHPUnit_Framework_TestCase
 {
     protected function setUp()
     {
         // currentry nothing to do.
     }
     
     protected function tearDown()
     {
         // currentry nothing to do.
     }
     
     public function testConstruct()
     {
         try{
            $git = new Git("/home/chobie/src/git-tutorial/.git");
         }catch(\Exception $e){
             $this->fail();
         }
         unset($git);
     }
     
     public function testGetIndex()
     {
         $git = new Git("/home/chobie/src/git-tutorial/.git");
         $index = $git->getIndex();
         if($index instanceof GitIndex){
             return true;
         }else{
             return false;
         }
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
     
     /**
      * @dataProvider getStringToTypeSpecifications
      */
     public function testStringToType($expected, $str_type, $comment)
     {
         $this->assertEquals($expected, git_string_to_type($str_type), $comment);
     }
     
     public function getStringToTypeSpecifications()
     {
         $array = array();
         $array[] = array(Git::OBJ_COMMIT,"commit","commit type id");
         $array[] = array(Git::OBJ_BLOB,"blob","blob type id");
         $array[] = array(Git::OBJ_TREE,"tree","tree type id");
         $array[] = array(Git::OBJ_TAG,"tag","tag type id");

         return $array;
     }
     
     /**
      * @dataProvider getTypeToStringSpecifications
      */
     public function testTypeToString($expected, $type, $comment)
     {
         $this->assertEquals($expected, git_type_to_string($type), $comment);
     }

     public function getTypeToStringSpecifications()
     {
         $array = array();
         $array[] = array("commit",Git::OBJ_COMMIT,"commit type string");
         $array[] = array("blob",Git::OBJ_BLOB,"blob type string");
         $array[] = array("tree",Git::OBJ_TREE,"tree type string");
         $array[] = array("tag",Git::OBJ_TAG,"tag type string");

         return $array;
     }

 }