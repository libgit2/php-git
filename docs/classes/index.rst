Git\\Index Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git index.

Implements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Countable, Iterator

Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: Stdclass Git::Index::getEntry(int offset)

   returns specified index entry.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      $result = $index->getEntry(0);
      /*
      object(stdClass)#4 (12) {
        ["path"]=>
        string(10) ".gitignore"
        ["oid"]=>
        string(40) "5b1a5b7ad3dd7141ccacd25e50e3078de4288a22"
        ["dev"]=>
        int(2050)
        ["ino"]=>
        int(1205498)
        ["mode"]=>
        int(33188)
        ["uid"]=>
        int(1000)
        ["gid"]=>
        int(1000)
        ["file_size"]=>
        int(364)
        ["flags"]=>
        int(10)
        ["flags_extended"]=>
        int(0)
        ["ctime"]=>
        int(1294640280)
        ["mtime"]=>
        int(1294640280)
      }
      */

   .. note:: return object may change next release.


.. cpp:function:: bool Git::Index::refresh()

   reloading current repository index.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      /**
       * some change wrote.
       * you have to refresh index.
       */
      $index->refresh();

.. cpp:function:: int Git::Index::find(file_name)

   returns specified file name offset in git_index.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      $offset = $index->find("README.md");

.. cpp:function:: int Git::Index::add(file_name)

   add specified file to your index.
   you have to call `Git::Index::write` after this method.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      $index->add("newcontents.txt");
      $index->write();
      $index->refresh();

.. cpp:function:: int Git::Index::write()

   write in memory index to disk.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      $index->add("newcontents.txt");
      $index->write();
      $index->refresh();

.. cpp:function:: int Git::Index::count()

   Countable Interface. you can `count(Git::Index)` this method.

   .. code-block:: php

      <?php

      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      echo count($index);
      // same as echo $index->count();

.. cpp:function:: Git::Index::current()

   Iterator interface. you don't have to call this manualy.


   .. code-block:: php

      <?php

      $repo = new Git\Repository("/tmp/specified.git");
      $index = $repo->getIndex();
      foreach($index as $hash => $entry){
        var_dump($entry);
      }


.. cpp:function:: Git::Index::next()

   Iterator interface. you don't have to call this manualy.

.. cpp:function:: Git::Index::rewind()

   Iterator interface. you don't have to call this manualy.

.. cpp:function:: Git::Index::valid()

   Iterator interface. you don't have to call this manualy.