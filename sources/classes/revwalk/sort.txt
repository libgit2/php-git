.. index::
   single: sort (Git\Revwalk method)


Git\\Revwalk::sort
===========================================================

Description
***********************************************************

public **Git\\Revwalk::sort** (int *$sort_type*)

Parameters
***********************************************************

*sort_type*
  specified sort type

- Git\\Revwalk\\SORT_NONE
- Git\\Revwalk\\SORT_TOPO
- Git\\Revwalk\\SORT_DATE
- Git\\Revwalk\\SORT_REVERSE

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
   $revwalk->sort(Git\Revwalk\SORT_REVERSE);
   $revwalk->push($master->getId());

See Also
***********************************************************