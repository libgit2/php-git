.. index::
   single: getAuthor (Git\Commit method)


Git\\Commit::getAuthor
===========================================================

Description
***********************************************************

public **Git\\Commit::getAuthor** ()


Parameters
***********************************************************


Return Values
***********************************************************

Git\\Signature

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/repository");
   $ref  = $repo->lookupRef("refs/heads/master");
   $commit = $repo->getCommit($ref->getId());
   $author = $commit->getAuthor();

See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`
:doc:`Git\\Commit::getCommitter() </classes/commit/get_committer>`
:doc:`Git\\Signature </classes/signature/index>`

