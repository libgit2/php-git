.. index::
   single: remove (Git\Tree method)


Git\\Tree::remove
===========================================================

Description
***********************************************************

public **Git\\Tree::remove** (string *$name*)


Parameters
***********************************************************

*name*
  specified file name

Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository");
   $hash = "";// blob / tree hash.
   $tree = new Git\Tree($repository);
   $tree->remove("README");
   $tree_hash = $tree->write();

See Also
***********************************************************

:doc:`Git\\Tree </classes/tree/index>`