.. index::
   single: getEntry (Git\Tree method)


Git\\Tree::getEntry
===========================================================

returns specified tree entry.

Description
***********************************************************

public **Git\\Tree::getEntry** (int *$offset* = 0)


Parameters
***********************************************************

*offset*
  tree entry offset


Return Values
***********************************************************

Git\Tree\Entry

Examples
***********************************************************

.. code-block::php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $tree = $repo->getTree($repo->getCommit($repo->lookupRef("refs/heads/master")));
    $result = $tree->getEntry(0);

See Also
***********************************************************