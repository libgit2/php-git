.. index::
   single: getIndex (Git\Repository method)


Git\\Repository::getIndex
===========================================================

returns current Git\Index object. this method will fail when bare repository.

Description
***********************************************************

public **Git\\Repository::getIndex** ()


Parameters
***********************************************************


Return Values
***********************************************************

:doc:`Git\\Index </classes/index/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/example/.git");
    $index = $repository->getIndex();


See Also
***********************************************************