<?php
/*
* This file is part of the PECL_Git package.
* (c) Shuhei Tanuma
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

/*
Git repository management routines

[*]git_repository_open
[]git_repository_open2 
[*]git_repository_open3
[]git_repository_lookup 
[]git_repository_database 
[*]git_repository_index
[]git_repository_newobject
[*]git_repository_free (internal)
[*]git_repository_init
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
    
    public function testGetTree()
    {
       $git = new Git\Repository("./.git");
       $tree= $git->getTree("c40b970eb68bd1c8980f1f97b57396f4c7ae107f");
       $this->assertInstanceof("Git\\Tree",$tree);
       $this->assertEquals("c40b970eb68bd1c8980f1f97b57396f4c7ae107f",$tree->getId());
    }
    
    public function testRepositoryInit()
    {
        $repo = Git\Repository::init("/tmp/uhi",1);
        $this->assertEquals("/tmp/uhi",file_exists("/tmp/uhi"));
        $this->assertInstanceof("Git\\Repository",$repo);
    }

    public function testConstruct()
    {
        try{
            $git = new Git\Repository("./.git");
            $this->assertInstanceof("Git\\Repository",$git);
            unset($git);
        }catch(\Exception $e){
            $this->fail();
        }

        try{
            $git = new Git\Repository("./.git");
            $this->assertInstanceof("Git\\Repository",$git,"Git\\Repository::__construct allowed null parameter. refs #127");
        }catch(\Exception $e){
            $this->fail();
        }
    }
    
    public function testGetIndex()
    {

//        $this->markTestIncomplete("testGetIndex not implemented yet");

        $git = new Git\Repository("./.git");
        $index = $git->getIndex();
        if($index instanceof Git\Index){
            return true;
        }else{
            return false;
        }
    }
    
    public function testInitRepository()
    {
        require_once __DIR__ . "/lib/MemoryBackend.php";
        require_once __DIR__ . "/lib/MemcachedBackend.php";
        if(!is_dir(__DIR__ . "/git_init_test")){
            mkdir(__DIR__ . "/git_init_test",0755);
        }
        
    
        $backend = new Git\Backend\Memory(5);
        $repository = Git\Repository::init(__DIR__ . "/git_init_test",true);
        $repository->addBackend($backend);

        $blob = new Git\Blob($repository);
        $blob->setContent("First Object1");
        $hash = $blob->write();
        $this->assertEquals("abd5864efb91d0fae3385e078cd77bf7c6bea826", $hash,"First Object1 write correctly");
        $this->assertEquals("abd5864efb91d0fae3385e078cd77bf7c6bea826", $blob->getid(),"rawobject and blob hash are same.");
        $this->assertEquals("abd5864efb91d0fae3385e078cd77bf7c6bea826", $backend->get($hash)->getId(),"Backend return same rawobject");
        //$tree = new Git\Tree($repository);
    
        
        unset($repository);
    }
}