.. index::
   single: push (Git\Revwalk method)


Git\\Revwalk::push
===========================================================

push commit to revwalk object.

Description
***********************************************************

public **Git\\Revwalk::push** (string *$hash*)


Parameters
***********************************************************

*hash*
  commit id


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
   while($commit = $revwalk->next()){
      // 
   }

See Also
***********************************************************

:doc:`Git\\Reference </classes/reference/index>`
:doc:`Git\\Revwalk::next() </classes/revwalk/next>`