<?php
namespace Git\Backend;

/**
 * Memory Git Storage Engine.
 * 
 * You must extends \Git\Backend to create own custom backend.
 *
 */
class Memory extends \Git\Backend
{
    protected $memory = array();
    /**
     * for debug
     */
    public function get($key){
       if(isset($this->memory[$key])){
           $obj = $this->memory[$key];

           return new \Git\RawObject($obj->type,$obj->data,$obj->len);
       }else{
           return false;
       }
    }

    /**
     * Read Data
     *
     * @param string $key  sha1 hash.
     * @return Git\RawObject
     * 
     * Note: libgit2 usualy use internal cache.
     *       so this method does not call anytime.
     */
    public function read($key){
       if($this->exists($key)){
           $object = $this->get($key);
       }
    }

    /**
     * Read Header
     *
     * @param string $key  sha1 hash.
     * @return Git\RawObject
     * 
     */
    public function read_header($key){
       if(isset($this->memory[$key])){
           return new \Git\RawObject($obj->type,"",$obj->len);
       }
    }

    /**
     * check specified contents.
     *
     * @param string $key  sha1 hash.
     * @return boolean
     * 
     */
    public function exists($key){
        if(isset($this->memory[$key])){
            return true;
        }else{
            return false;
        }
    }

    /**
     * write contents
     *
     * you have to write key,data,type your storage engine.
     *
     * @param string $key  sha1 hash.
     * @param Git\RawObject $object.
     * @return hash
     */
    public function write($object){
        $key = $object->getId();
        $this->memory[$key] = $object;
        return $key;
    }

    public function free()
    {
        unset($this->memory);
    }
}
