.. index::
   single: lookupRef (Git\Reference\Manager method)


Git\\Reference\\Manager::lookupRef
===========================================================

this method same as Git\Repository::lookupRef();

Description
***********************************************************

public **Git\\Reference\\Manager::lookupRef** (string *$name*)


Parameters
***********************************************************

*name*
  reference name (e.g.  refs/heads/master)


Return Values
***********************************************************

Git\\Reference

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repo);
   $ref = $manager->lookupRef("refs/heads/master");


See Also
***********************************************************

:doc:`Git\\Repository::lookupRef </classes/repository/lookup_ref>`