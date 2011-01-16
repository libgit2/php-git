Git\\Tree Class extends Git\\Object
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git tree.


Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: void Git::Tree::getId()

   getting current tree id.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/path/to/repository");
      $master = $repo->getBranch("master");
      $commit = $repo->getCommit($master);
      $tree = $commit->getTree();
      echo $tree->getId();

.. cpp:function:: void Git::Tree::add(Git::Tree::Entry entry)

   add new entry to current tree. see also Git\\Tree\\Entry


.. cpp:function:: int Git::Tree::count()

   Countable Interface.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/path/to/repository");
      $master = $repo->getBranch("master");
      $commit = $repo->getCommit($master);
      $tree = $commit->getTree();
      echo count($tree);


.. cpp:function:: string Git::Tree::write()

   write current tree to git repository. see also Git\\Tree\\Entry

