.. index::
   single: getIterator (Git\Tree method)


Git\\Tree::getIterator
===========================================================

IteratorAggregate interface.

Description
***********************************************************

public **Git\\Tree::getIterator** ()

Parameters
***********************************************************

Return Values
***********************************************************

Examples
***********************************************************

.. code-block::php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $commit = $repo->getCommit($repo->lookupRef("refs/heads/master")->getId());
		$tree = $commit->getTree();
    foreach($tree->getIterator() as $entry){
       // something...
    }
    
See Also
***********************************************************