.. index::
   single: __construct (Git\Reference\Manager method)


Git\\Reference\\Manager::__construct
===========================================================

Description
***********************************************************

public **Git\\Reference\\Manager::__construct** (Git\\Repository *$repository*)


Parameters
***********************************************************

*repository*
  Git\\Repository


Return Values
***********************************************************

:doc:`Git\\Reference\\Manager </classes/manager/index>`

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repo);

See Also
***********************************************************

:doc:`Git\\Reference </classes/reference/index>`
:doc:`Git\\Repository </classes/repository/index>`
