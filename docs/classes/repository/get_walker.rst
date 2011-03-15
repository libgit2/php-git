.. index::
   single: getWalker (Git\Repository method)


Git\\Repository::getWalker
===========================================================

returns Git\Revwalk.

Description
***********************************************************

public **Git\\Repository::getWalker** (*$hash*)


Parameters
***********************************************************

*hash*
  fill them out later


Return Values
***********************************************************

:doc:`Git\\Revwalk </classes/revwalk/index>`

Examples
***********************************************************


.. code-block:: php

   <?php
   $repo = new Git\Repository("/tmp/specified.git");
   $reference = $repo->lookupRef("refs/heads/master");
   $walker = $repo->getWalker();
   $walker->push($reference->getId());

   while($commit = $walker->next()){
     var_dump($commit);
   }

See Also
***********************************************************

:doc:`Git\\Revwalk </classes/revwalk/index>`
:doc:`Git\\Commit </classes/commit/index>`