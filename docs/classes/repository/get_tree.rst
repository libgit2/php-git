.. index::
   single: getTree (Git\Repository method)


Git\\Repository::getTree
===========================================================

returns specified Git\\Tree.

Description
***********************************************************

public **Git\\Repository::getTree** (*$hash*)


Parameters
***********************************************************

*hash*
  tree hash id.


Return Values
***********************************************************

:doc:`Git\\Tree </classes/tree/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/specified.git");
    $tree = $repository->getTree("cd584aba22827a6a59cad3ab1b4e026418558bfb");

See Also
***********************************************************

:doc:`Git\\Tree </classes/tree/index>`