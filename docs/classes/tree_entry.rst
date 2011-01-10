Git\\Tree\\Entry Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git tree entry.


Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: void Git::Tree::Entry::setId(hash)

   update tree entry sha1 hash.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/path/to/repository");
      $master = $repo->getBranch("master");

      // write some contents to your git repository.
      $blob = new Git\Blob($repo);
      $blob->data = "Hello World";
      $sha = $blob->write();

      // add new tree entry to your git tree.
      // these operation may change next release.
      $entry = new Git\Tree\Entry();
      $entry->name = "GREETINGS";
      $entry->mode = 0644;
      $entry->oid = $sha;

      // write current tree.
      $commit = $repo->getCommit($master);
      $tree = $commit->getTree();
      $tree->add($entry);
      $hash = $tree->write();

      $newCommit = new Git\Commit($repo);
      $newCommit->setAuthor(new Git\Signature("Someone","someone@example.com",new DateTime()));
      $newCommit->setCommitter(new Git\Signature("Someone","someone@example.com",new DateTime()));
      $newCommit->setTree($tree->getId());
      $newCommit->setParent($master);
      $newCommit->setMessage("update commit message");
      $newMasterHash = $newCommit->write();

      $repo->update("master",$newMasterHash);
