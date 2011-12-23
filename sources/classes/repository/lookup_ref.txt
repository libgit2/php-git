.. index::
   single: lookupRef (Git\Repository method)


Git\\Repository::lookupRef
===========================================================

return specified reference object.

Description
***********************************************************

public **Git\\Repository::lookupRef** (*$name*)


Parameters
***********************************************************

*name*
  reference name. 


Return Values
***********************************************************

:doc:`Git\\Reference </classes/reference/index>`

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/tmp/specified.git");
   $reference = $repo->lookupRef("refs/heads/master");

See Also
***********************************************************

:doc:`Git\\Reference </classes/reference/index>`