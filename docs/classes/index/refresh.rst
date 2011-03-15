.. index::
   single: refresh (Git\Index method)


Git\\Index::refresh
===========================================================

reloading current repository index.

Description
***********************************************************

public **Git\\Index::refresh** ()


Parameters
***********************************************************

Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php
    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $index = $repo->getIndex();
    /**
     * some change wrote.
     * you have to refresh index.
     */
    $index->refresh();
    
See Also
***********************************************************