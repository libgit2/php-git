.. index::
   single: __construct (Git\Commit method)

create new commit.


Git\\Commit::__construct
===========================================================

Description
***********************************************************

public **Git\\Commit::__construct** (Git\\Repository *$repository*)


Parameters
***********************************************************

Git\\Repository *repository*
  Repository class


Return Values
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`

Examples
***********************************************************


.. code-block:: php

   <?php
   
   $repository = new Git\Repository("/path/to/repository");
   $author = new Git\Commit($repository);

See Also
***********************************************************

:doc:`Git\\Signature </classes/signature/index>`