.. index::
   single: next (Git\Revwalk method)


Git\\Revwalk::next
===========================================================

get next travasable commit.

Description
***********************************************************

public **Git\\Revwalk::next** ()


Parameters
***********************************************************


Return Values
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/tmp/specified.git");
   $master = $repo->lookupRef("refs/heads/master");
   $revwalk = $repo->getWalker();
   $revwalk->push($master->getId());
   $commit = $revwalk->next();

See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`