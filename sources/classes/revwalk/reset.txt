.. index::
   single: reset (Git\Revwalk method)


Git\\Revwalk::reset
===========================================================

reset internal pointer.

Description
***********************************************************

public **Git\\Revwalk::reset** ()


Parameters
***********************************************************


Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/tmp/specified.git");
   $master = $repo->lookupRef("refs/heads/master");
   $revwalk = $repo->getWalker();
   $revwalk->push($master->getId());
   $commit = $revwalk->next();
   $revwalk->reset();

See Also
***********************************************************