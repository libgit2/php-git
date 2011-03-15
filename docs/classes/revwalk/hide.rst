.. index::
   single: hide (Git\Revwalk method)


Git\\Revwalk::hide
===========================================================

hide uninterested commits.

::

  o---o---o---o---o---o---o---o
               `--o---o--/
                  ^hide

::

  o---o---o---o---o---o---o---o


Description
***********************************************************

public **Git\\Revwalk::hide** (*$hash*)


Parameters
***********************************************************

*hash*
  uninterested commit id


Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/tmp/specified.git");
   $master = $repo->lookupRef("refs/heads/master");
   $revwalk = $repo->getWalker();
   $uninterested = "";// specified uninterested commit id
   $revwalk->hide($uninterested);

See Also
***********************************************************