.. index::
   single: getShortMessage (Git\Commit method)


Git\\Commit::getShortMessage
===========================================================

Description
***********************************************************

public **Git\\Commit::getShortMessage** (*$message*)


Parameters
***********************************************************

*message*
  fill them out later


Return Values
***********************************************************

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/repository");
   $ref  = $repo->lookupRef("refs/heads/master");
   $commit = $repo->getCommit($ref->getId());
   $message = $commit->getShortMessage();

See Also
***********************************************************