.. index::
   single: getObject (Git\Repository method)


Git\\Repository::getObject
===========================================================

returns specified Git\\Blob.

.. note::
   this method will rename to Git\\Repository::getBlob

Description
***********************************************************

public **Git\\Repository::getObject** (*$hash*)


Parameters
***********************************************************

*hash*
  blob hash id.


Return Values
***********************************************************

:doc:`Git\\Blob </classes/blob/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/specified.git");
    $blob = $repository->getObject("cd584aba22827a6a59cad3ab1b4e026418558bfb");


See Also
***********************************************************

:doc:`Git\\Blob </classes/blob/index>`
