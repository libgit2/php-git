Git\\Repository Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git_repository.

Constants
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: Git::Repository Git::Repository::__construct(repository_path)

   open specified git repository and returns Git\\Repository class.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");

.. cpp:function:: Git::Commit Git::Repository::getCommit(hash)

   returns specified Git\\Commit.


   .. code-block:: php

       <?php
       $repo = new Git\Repository("/tmp/specified.git");
       $commit = $repo->getCommit("cd584aba22827a6a59cad3ab1b4e026418558bfb");


.. cpp:function:: Git::Index Git::Repository::getIndex()

   returns current Git\\Index object. this method will fail when bare repository.


   .. code-block:: php

       <?php
       $repo = new Git\Repository("/tmp/specified.git");
       $commit = $repo->getCommit("cd584aba22827a6a59cad3ab1b4e026418558bfb");


.. cpp:function:: Git::Index Git::Repository::getTree(tree_hash)

   returns specified Git\\Tree object.

   .. code-block:: php

       <?php
       $repo = new Git\Repository("/tmp/specified.git");
       $commit = $repo->getTree("1b810818919cddbb799a7cf096aa73ba5918a047");


.. cpp:function:: string Git::Repository::getBranch(branch_name)

   this method is convention use to php. not containted libgit2.
   get specified branch's sha1 hash.

   .. code-block:: php

       <?php
       $repo = new Git\Repository("/tmp/specified.git");
       $master_hash = $repo->getBranch("master");


.. cpp:function:: Git::Revwalk Git::Repository::getWalker()

   returns Git\\Revwalk.

   .. code-block:: php

       <?php
       $repo = new Git\Repository("/tmp/specified.git");
       $master_hash = $repo->getBranch("master");
       $walker = $repo->getWalker();
       $walker->push($master_hash);

       while($commit = $walker->next()){
         var_dump($commit);
       }

.. cpp:function:: Git::Repository Git::Repository::init(string repository_path, bool is_bare)

   create a new git repository on your filesystem.

   .. code-block:: php

       <?php
       $repo = Git\Repository::init("/tmp/new.git",true);

   .. note:: can't create non-bared repository now. fix this probrem soon.

.. cpp:function:: bool Git::Repository::update(string branch_name, string hash)

   this method is convention use to php. not containted libgit2.
   updated specified branch's sha1 hash.

   .. code-block:: php

       <?php
       $repo = new Git\Repository("/tmp/specified.git");
       /**
        * some commit.
        */
       $repo->update("master",$newCommitHash);
       // now. you can traverse new commit with `git log`

.. cpp:function:: bool Git::Repository::addBackend(Git::Backend backend)

   this method does not work yet.
