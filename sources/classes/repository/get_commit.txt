.. index::
   single: getCommit (Git\Repository method)


Git\\Repository::getCommit
===========================================================

returns specified Git\\Commit.

Description
***********************************************************

public **Git\\Repository::getCommit** (string *$hash*)


Parameters
***********************************************************

*hash*
  commit hash id.


Return Values
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/specified.git");
    $commit = $repository->getCommit("cd584aba22827a6a59cad3ab1b4e026418558bfb");


See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`