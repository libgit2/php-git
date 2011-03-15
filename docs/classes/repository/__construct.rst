.. index::
   single: __construct (Git\Repository method)


Git\\Repository::__construct
===========================================================

Description
***********************************************************

public **Git\\Repository::__construct** ( [*$repository_path*])


Parameters
***********************************************************

*repository_path*
  git repository path.


Return Values
***********************************************************

:doc:`Git\Repository </classes/repository/index>`

Examples
***********************************************************

.. code-block:: php

    <?php
    $repository = new Git\Repository("/tmp/specified.git");

See Also
***********************************************************