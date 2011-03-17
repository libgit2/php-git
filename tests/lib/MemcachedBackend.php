<?php
namespace Git\Backend;

/**
 * Memcached Git Storage Engine.
 * 
 * You must extends \Git\Backend to create own custom backend.
 *
 */
class Memcached extends \Git\Backend
{
    protected $memcached;

    protected function serialize($value){
        return serialize($value);
    }

    protected function unserialize($value){
        return unserialize($value);
    }

    protected function set($key, $value){
        return $this->memcached->set($key, $this->serialize($value));
    }

    protected function get($key){
       $data = $this->memcached->get($key);
       if($data){
           return $this->unserialize($data);
       }else{
           return false;
       }
    }

    public function __construct($address = "127.0.0.1", $port = 11211){
       $memcached = new \Memcached();
       $memcached->addServer($address,$port);
       $this->memcached = $memcached;

       parent::__construct();
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
       $data = $this->get($key);
       if($data){
           $raw = new \Git\RawObject();
           $raw->data = $data->data;
           $raw->type = $data->type;
       }

       return $raw;
    }

    /**
     * Read Header
     *
     * @param string $key  sha1 hash.
     * @return Git\RawObject
     * 
     */
    public function read_header($key){
       $data = $this->get($key);
       if($data){
           $raw = new \Git\RawObject();
           $raw->data = null;
           $raw->type = $data->type;
       }

       return $raw;
    }

    /**
     * check specified contents.
     *
     * @param string $key  sha1 hash.
     * @return boolean
     * 
     */
    public function exists($key){
        $data = $this->get($key);
        if($data){
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
     * @param Git\RawObject $object.
     * @return string rawobject hash.
     */
    public function write($object){
        $key = $object->getid();
        $this->set($key, $object);

        return $key;
    }

    public function free()
    {
        unset($this->memcached);
    }
}
