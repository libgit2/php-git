.. index::
   single: getMessage (Git\Commit method)


Git\\Commit::getMessage
===========================================================

Description
***********************************************************

public **Git\\Commit::getMessage** ()


Parameters
***********************************************************

Return Values
***********************************************************

string

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/repository");
   $ref  = $repo->lookupRef("refs/heads/master");
   $commit = $repo->getCommit($ref->getId());
   $message = $commit->getMessage();


See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`
:doc:`Git\\Commit::getShortMessage() </classes/commit/get_short_message>`