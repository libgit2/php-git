.. index::
   single: addBackend (Git\Repository method)


Git\\Repository::addBackend
===========================================================

Description
***********************************************************

public **Git\\Repository::addBackend** (*$backend*, *$priority*)


Parameters
***********************************************************

*backend*
  Specifies a class that inherits from :doc:`Git\\Backend </classes/backend/index>`

*priority*
  [low] 1 ... 5[high]


Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php

    <?php
    /**
     * PHP Memory Backend.
     * 
     * You have to inherits Git\Backend to create own custom backend.
     *
     */
    class MemoryBackend extends \Git\Backend
    {
        protected $memory = array();
    
        /**
         * Read Data
         *
         * @param string $key  sha1 hash.
         * @return Git\RawObject
         * 
         * Note: libgit2 usualy use internal cache.
         *       so this method does not call everytime.
         */
        public function read($key){
           if($this->exists($key)){
               $object = $this->get($key);
               return $object;
           }
        }
    
        /**
         * Read Header
         *
         * @param string $key  sha1 hash.
         * @return Git\RawObject
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
            $std = new \Stdclass();
            $std->data = $object->data;
            $std->type = $object->type;
            $std->len = $object->len;
            $this->memory[$key] = $std;
            return $key;
        }
    
        public function free()
        {
            unset($this->memory);
        }
    }


    $repository = new Git\Repository("/tmp/example/.git");
    $repository->addBackend(new MemoryBackend(), 5);// higher priority.

See Also
***********************************************************

:doc:`Git\\Backend </classes/backend/index>`