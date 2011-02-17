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

    public function testLookupRef()
    {
        //this test still legacy. fix environment probrem soon
        $this->markTestSkipped();
        
        //temporary added Git\\Reference.
        $git = new Git\Repository(dirname(__DIR__) . "/.git/");
        $ref = $git->lookupRef("refs/heads/master");
        $commit = $git->getCommit($ref->oid);

        $this->assertInstanceof("Git\\Reference",$ref,"Git\\Referenceが帰ってきているか？");
        $this->assertInstanceof("Git\\Commit",$commit,"Git\\Commitが帰ってきているか？");
    }


    public function testGetBlob()
    {
       $git = new Git\Repository(dirname(__DIR__) . "/.git/");
       $blob = $git->getObject("5b4a19f66f8271d7457839f0e8554b3fe5aa6fd0");
       $this->assertEquals("5b4a19f66f8271d7457839f0e8554b3fe5aa6fd0",$blob->getId());
    }

    public function testGetTree()
    {
       $git = new Git\Repository(dirname(__DIR__) . "/.git/");
       $tree= $git->getTree("c40b970eb68bd1c8980f1f97b57396f4c7ae107f");
       $this->assertInstanceof("Git\\Tree",$tree);
       $this->assertEquals("c40b970eb68bd1c8980f1f97b57396f4c7ae107f",$tree->getId());
       foreach($tree->entries as $entry){
           $object = $entry->toObject();
           $this->assertInstanceof("Git\\Object",$object);
           if($object->getType() == GIT\Object\Blob){
               $this->assertInstanceof("Git\\Blob",$object);
           }else if($object->getType() == GIT\Object\Tree) {
               $this->assertInstanceof("Git\\Tree",$object);
           }else {
               $this->fail("unhandled object found.");
           }
       }
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
            $git = new Git\Repository(dirname(__DIR__) . "/.git/");
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
        $git = new Git\Repository(dirname(__DIR__) . "/.git/");
        $index = $git->getIndex();
        if($index instanceof Git\Index){
            foreach($index as $entry){
                $this->assertInstanceof("Git\\Index\\Entry",$entry);
            }
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
        
    
        $backend = new Git\Backend\Memory();
        $repository = Git\Repository::init(__DIR__ . "/git_init_test",true);
        $repository->addBackend($backend,1);

        $blob = new Git\Blob($repository);
        $blob->setContent("First Object1");
        $hash = $blob->write();
        
        $this->assertEquals("abd5864efb91d0fae3385e078cd77bf7c6bea826", $hash,"First Object1 write correctly");
        $this->assertEquals("abd5864efb91d0fae3385e078cd77bf7c6bea826", $blob->getid(),"rawobject and blob hash are same.");
        $data = $backend->read($hash);
        if($backend->read($hash)){
            $this->assertEquals("abd5864efb91d0fae3385e078cd77bf7c6bea826", $backend->read($hash)->getId(),"Backend return same rawobject");
        }
        
        $tree = new Git\Tree($repository);
        $tree->add($hash,"README",100644);
        $tree_hash = $tree->write();
        $this->assertEquals("3c7493d000f58ae3eed94b0a3bc77d60694d33b4",$tree_hash, "tree writing");
        
        $data = $backend->read("3c7493d000f58ae3eed94b0a3bc77d60694d33b4");
        if($data){
        $this->assertEquals("3c7493d000f58ae3eed94b0a3bc77d60694d33b4",$data->getId(), "Backend return same tree raw");
        }
        
        $commit = new Git\Commit($repository);
        $commit->setAuthor(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));
        $commit->setCommitter(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));
        $commit->setTree($tree->getId());
        // when first commit. you dont call setParent.
        //$commit->setParent(""); 
        $commit->setMessage("initial import");
        
        $master_hash = $commit->write();

        //$this->markTestIncomplete("this test does not implemente yet.");
        $this->assertEquals("c12883a96cf60d1b2edba971183ffaca6d1b077e",$master_hash,"commit writing");

        $re = new Git\Reference($repository);
        $re->setName("refs/heads/master");
        //$re->setTarget("refs/heads/master");
        // you can't use setOid if setTarget called.
        $re->setOID("c12883a96cf60d1b2edba971183ffaca6d1b077e");
        $re->write();


        $rmdir = function($dir) use(&$rmdir){
           if (is_dir($dir)) { 
             $objects = scandir($dir); 
             foreach ($objects as $object) { 
               if ($object != "." && $object != "..") { 
                 if (filetype($dir."/".$object) == "dir") $rmdir($dir."/".$object); else unlink($dir."/".$object); 
               } 
             } 
             reset($objects); 
             rmdir($dir); 
           } 
        };
        $rmdir(__DIR__ . "/git_init_test");
    }
}