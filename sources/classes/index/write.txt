.. index::
   single: write (Git\Index method)


Git\\Index::write
===========================================================

write current index to filesystem.

Description
***********************************************************

public **Git\\Index::write** ()


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
    $index->add("newcontents.txt");
    $index->write();
    $index->refresh();
    
See Also
***********************************************************