.. index::
   single: write (Git\Tree method)


Git\\Tree::write
===========================================================

Description
***********************************************************

public **Git\\Tree::write** ()


Parameters
***********************************************************



Return Values
***********************************************************

Examples
***********************************************************

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository");
   $hash = "";// blob / tree hash.
   $tree = new Git\Tree($repository);
   $tree->add($hash,"README",100644);
   $tree_hash = $tree->write();

See Also
***********************************************************

:doc:`Git\\Object::write </classes/object/write>`