.. index::
   single: count (Git\Index method)


Git\\Index::count
===========================================================

Countable Interface. you can count(Git::Index) this method.

Description
***********************************************************

public **Git\\Index::count** ()


Parameters
***********************************************************


Return Values
***********************************************************

Examples
***********************************************************

.. code-block:: php

    <?php
    
    $repo = new Git\Repository("/tmp/specified.git");
    $index = $repo->getIndex();
    echo count($index);
    // same as echo $index->count();
    
See Also
***********************************************************