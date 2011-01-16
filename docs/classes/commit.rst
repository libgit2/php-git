Git\\Commit Class extends Git\\Object
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git commit.


Attention
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Git\\Commit::write feature does not work correctry on first alpha development release.
please wait next alpha release.


Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: Git::Commit Git::Commit::__construct(Git\Repository repository)

   create new commit.


   .. code-block:: php

      <?php

      $repository = new Git\Repository("/path/to/repository");
      $author = new Git\Commit($repository);

.. cpp:function:: void Git::Commit::setTree(Git\Tree tree)

.. cpp:function:: void Git::Commit::setAuthor(Git\Signature author)

.. cpp:function:: Git::Signature Git::Commit::getAuthor()

.. cpp:function:: void Git::Commit::setCommitter(Git\Signature author)

.. cpp:function:: Git::Signature Git::Commit::getCommitter()

.. cpp:function:: void Git::Commit::setMessage(string message)

.. cpp:function:: string Git::Commit::getMessage()

.. cpp:function:: string Git::Commit::getShortMessage()

.. cpp:function:: void Git::Commit::setParent(string parent_commit_hash)
