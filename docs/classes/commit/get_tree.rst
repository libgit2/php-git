.. index::
   single: getTree (Git\Commit method)


Git\\Commit::getTree
===========================================================

Description
***********************************************************

public **Git\\Commit::getTree** ()


Parameters
***********************************************************



Return Values
***********************************************************

Git\\Tree

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo   = new Git\Repository("/path/repository");
   $ref    = $repo->lookupRef("refs/heads/master");
   $commit = $repo->getCommit($ref->getId());
   $tree   = $commit->getTree();

See Also
***********************************************************

:doc:`Git\\Tree </classes/tree/index>`
:doc:`Git\\Commit </classes/commit/index>`
