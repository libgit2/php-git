.. index::
   single: getEntries (Git\Tree method)


Git\\Tree::getEntries
===========================================================

returns tree entry array.

Description
***********************************************************

public **Git\\Tree::getEntries** ()


Parameters
***********************************************************

Return Values
***********************************************************

array Git\Tree\Entry

Examples
***********************************************************

.. code-block::php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $tree = $repo->getTree($repo->getCommit($repo->lookupRef("refs/heads/master")));
    $result = $tree->getEntries();

See Also
***********************************************************