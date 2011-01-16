Git\\Backend Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
libgit2 can use custom backend.you can create custom backend with Git\\Backend


Attention
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

this feature does not work on first alpha development release.
please wait next alpha release.


Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: Git::Backend Git::Backend::__construct(int priority)

   specified backend priority

.. note:: you must call parent::__construct($prioriy)

Abstract Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: Git::RawObject Git::Backend::read(string key)

.. cpp:function:: Git::RawObject Git::Backend::read_header(string key)

.. cpp:function:: Git::RawObject Git::Backend::write(string key, Git::RawObject object)

.. cpp:function:: bool Git::Backend::exists(string key)

.. cpp:function:: void Git::Backend::free()


Example
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

memcached_backend.php

.. code-block:: php

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

        public function __construct($priority, $address = "127.0.0.1", $port = 11211){
           $memcached = new \Memcached();
           $memcached->addServer($address,$port);
           $this->memcached = $memcached;

           parent::__construct($priority);
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
         * @param string $key  sha1 hash.
         * @param Git\RawObject $object.
         * @return boolean
         */
        public function write($key, $object){
            $this->set($key, $object);
            return true;
        }

        public function free()
        {
            unset($this->memcached);
        }
    }

sample.php

.. code-block:: php

    <?php
    require "memcached_backend.php";
    $back = new Git\Backend\Memcached(5);
    $repo = new Git\Repository("/path/to/repository");

    $repo->addBackend($back);
    // now memcached backend is highest priority.
