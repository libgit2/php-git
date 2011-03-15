.. index::
   single: init (Git\Repository method)


Git\\Repository::init
===========================================================

create a new git repository on your filesystem.

Description
***********************************************************

public static **Git\\Repository::init** (*$path*, *$is_bare*)


Parameters
***********************************************************

*path*
  blank directory

*is_bare*
  create bare repository when is_bare is true.


.. note::
   do not call this method when specified repository exists.

Return Values
***********************************************************

:doc:`Git\\Repository </classes/repository/index>`

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = Git\Repository::init("/tmp/new.git",true);

See Also
***********************************************************

:doc:`Git\\Repository </classes/repository/index>`