.. index::
   single: getReferences (Git\Repository method)


Git\\Repository::getReferences
===========================================================

returns a list with all the references that can be found in a repository.

.. note::
   this method may changed next development.

Description
***********************************************************

public **Git\\Repository::getReferences** (int *$flag*)


Parameters
***********************************************************

*flag*
  fill them out lator


Return Values
***********************************************************

:doc:`array Git\\References </classes/references/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/specified.git");
    $refs = $repository->getReferences();

See Also
***********************************************************

:doc:`Git\\Reference </classes/reference/index>`