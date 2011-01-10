Git\\Revwalk Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git revwalk.

Namespace Constants
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Git\\Revwalk\\SORT_NONE
* Git\\Revwalk\\SORT_TOPO
* Git\\Revwalk\\SORT_DATE
* Git\\Revwalk\\SORT_REVERSE

Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: void Git::Revwalk::push(hash)

   push commit to revwalk object.


   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $master = $repo->getBranch("master");
      $revwalk = $repo->getWalker();
      $revwalk->push($master);

.. cpp:function:: Git\Commit Git::Revwalk::next()

   returns next travesable commit.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $master = $repo->getBranch("master");
      $revwalk = $repo->getWalker();
      $revwalk->push($master);
      $commit = $revwalk->next();


.. cpp:function:: void Git::Revwalk::hide(hash)

   hide specified commit comes from.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $dev = $repo->getBranch("develop");
      $master = $repo->getBranch("master");
      $revwalk = $repo->getWalker();
      $revwalk->push($master);
      $revwalk->hide($dev);
      // now revwalk skip develop changes.

.. cpp:function:: void Git::Revwalk::sort(int sort_order)

   you can choose sort method.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $dev = $repo->getBranch("develop");
      $master = $repo->getBranch("master");
      $revwalk = $repo->getWalker();
      $revwalk->push($master);
      $revwalk->sort(Git\Revwalk\SORT_NONE);
      // now revwalk skip develop changes.


.. cpp:function:: void Git::Revwalk::reset()

   reset iterator pointer to first.

   .. code-block:: php

      <?php
      $repo = new Git\Repository("/tmp/specified.git");
      $master = $repo->getBranch("master");
      $revwalk = $repo->getWalker();
      $revwalk->push($master);
      while($commit = $revwalk->next){
      }
      $revwalk->reset();
      // now you can iterate revwalk again.
