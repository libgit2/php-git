<?php
/*
 * This file is part of the PECL_Git package.
 * (c) Shuhei Tanuma
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
 
 /*
Git revision object management routines

 []git_object_write
 []git_object_id
 []git_object_type
 []git_object_owner
 []git_object_free
 [*]git_object_type2string
 [*]git_object_string2type
 []git_object_typeisloose
 */
class GitObjectManagementTest extends \PHPUnit_Framework_TestCase
{
    protected function setUp()
    {
        // currentry nothing to do.
    }
     
    protected function tearDown()
    {
        // currentry nothing to do.
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
        $array[] = array(Git::OBJ_BLOB,  "blob",  "blob type id");
        $array[] = array(Git::OBJ_TREE,  "tree",  "tree type id");
        $array[] = array(Git::OBJ_TAG,   "tag",   "tag type id");

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
        $array[] = array("blob",  Git::OBJ_BLOB,  "blob type string");
        $array[] = array("tree",  Git::OBJ_TREE,  "tree type string");
        $array[] = array("tag",   Git::OBJ_TAG,   "tag type string");
        return $array;
    }

}