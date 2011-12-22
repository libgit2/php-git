.. index::
   single: count (Git\Tree method)


Git\\Tree::count
===========================================================

Countable interface.

Description
***********************************************************

public **Git\\Tree::count** ()


Parameters
***********************************************************


Return Values
***********************************************************

int count.

Examples
***********************************************************

.. code-block:: php

   <?php
   $repository = new Git\Repository("/path/to/repository");
   $refs = $repository->lookupRef("refs/heads/master");
   $tree = $repository->getTree($refs->getId());
   echo count($tree); // or echo $tree->count();

See Also
***********************************************************

`Countable Interface <http://jp2.php.net/manual/en/class.countable.php>`_ (PHP Documents)