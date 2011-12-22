.. index::
   single: getIterator (Git\Index method)


Git\\Index::getIterator
===========================================================

IteratorAggregate interface.

Description
***********************************************************

public **Git\\Index::getIterator** ()

Parameters
***********************************************************

Return Values
***********************************************************

Examples
***********************************************************

.. code-block::php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $index = $repo->getIndex();
    foreach($index->getIterator() as $entry){
       // something...
    }
    
See Also
***********************************************************