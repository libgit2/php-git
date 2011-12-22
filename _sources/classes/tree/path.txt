.. index::
   single: path (Git\Tree method)


Git\\Tree::path
===========================================================

returns specified Git\Tree\Entry.

Description
***********************************************************

public **Git\\Tree::path** (*$path*)


Parameters
***********************************************************

*path*
  file name


Return Values
***********************************************************

:doc:`Git\\Tree\Entry </classes/tree/entry/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/specified.git");
    $tree = $repository->getTree("cd584aba22827a6a59cad3ab1b4e026418558bfb");
    $entry = $tree->path("README.md");


.. note::

   this method can't resolve recursive yet.

See Also
***********************************************************

:doc:`Git\\Tree\\Entry </classes/entry/index>`