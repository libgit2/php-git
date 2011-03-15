.. index::
   single: getId (Git\Tree method)


Git\\Tree::getId
===========================================================

returns tree hash id.

Description
***********************************************************

public **Git\\Tree::getId** ()


Parameters
***********************************************************


Return Values
***********************************************************

string hash id

Examples
***********************************************************

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository");
   $refs = $repository->lookupRef("refs/heads/master");
   $tree = $repository->getTree($refs->getId());
   echo $tree->getId();

See Also
***********************************************************