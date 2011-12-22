.. index::
   single: getCommitter (Git\Commit method)


Git\\Commit::getCommitter
===========================================================

Description
***********************************************************

public **Git\\Commit::getCommitter** ()


Parameters
***********************************************************



Return Values
***********************************************************

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/repository");
   $ref  = $repo->lookupRef("refs/heads/master");
   $commit = $repo->getCommit($ref->getId());
   $committer = $commit->getCommitter();


See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`
:doc:`Git\\Commit::getAuthor() </classes/commit/get_author>`
:doc:`Git\\Signature </classes/signature/index>`

