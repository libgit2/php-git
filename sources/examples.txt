Examples
==================================================

php-git examples.these example uses experimental API.

Create new blob
++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository/.git");
   $blob = new Git\Blob($repository);
   $blob->setContent("First Object1");
   $blobHash = $blob->write();

:doc:`Git\Blob::setContent </classes/blob/set_content>`

.. note::
   maybe this API will change next release.

Create new Tree
++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository/.git");
   $tree = new Git\Tree($repository);
   $tree->add($hash,"README",100644);
   $tree_hash = $tree->write();

:doc:`Git\Tree::add </classes/tree/add>`

.. note::
   maybe this API will change next release.


Create new Commit
++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: php

    <?php
    $repository = new Git\Repository("/path/to/repository/.git");
    $tree = new Git\Tree($repository);
    $tree->add($hash,"README",100644);
    $tree_hash = $tree->write();
    $commit = new Git\Commit($repository);
    $commit->setAuthor(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));
    $commit->setCommitter(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));
    $commit->setTree($tree->getId());
    // when first commit. you dont call setParent.
    //$commit->setParent($last_commit->getParent()->getId());
    $commit->setMessage("initial import");
    
    $master_hash = $commit->write();

:doc:`Git\Tree::add </classes/tree/add>`
:doc:`Git\Commit::setAuthor </classes/commit/set_author>`
:doc:`Git\Commit::setCommitter </classes/commit/set_committer>`
:doc:`Git\Commit::setTree </classes/commit/set_tree>`
:doc:`Git\Commit::setParent </classes/commit/set_parent>`
:doc:`Git\Commit::setMessage </classes/commit/set_message>`

.. note::
   php-git can't manage multiple parents now. this will fix next release.

get master tree
++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository/.git");
   $master_commit = $repository->getCommit($repository->lookupRef("refs/heads/master"));
   $tree = $master_commit->getTree();
   // or $tree->getEntries()
   foreach($tree->getIterator() as $entry){
      var_dump($entry);
   }

revision walking
++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository/.git");
   $master_commit = $repository->getCommit($repository->lookupRef("refs/heads/master"));
   $walker = $master_commit->getWalker();
   $walker->push($master_commit->getId());
   while($commit = $walker->next()){
       var_dump($commit);
   }

custom backends
++++++++++++++++++++++++++++++++++++++++++++++++++

see also :doc:`Git\\Repository\\addBackend </classes/repository/add_backend>`


get available references
++++++++++++++++++++++++++++++++++++++++++++++++++

.. note::
   maybe this API will change next release.

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repository);
   $manager->getList();

:doc:`Git\\Reference\\Manager </classes/manager/index>`


this method gets available all references.if you want gets available branches.you have to check manualy now.

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repository);
   $branches = array();
   foreach($manager->getList() as $ref){
      if(strpos($ref->name,"refs/heads")){
          $brandhes[] $ref;
      }
   }
