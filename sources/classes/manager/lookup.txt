.. index::
   single: lookup (Git\Reference\Manager method)


Git\\Reference\\Manager::lookup
===========================================================

this method same as Git\Repository::lookup();

Description
***********************************************************

public **Git\\Reference\\Manager::lookup** (string *$name*)


Parameters
***********************************************************

*name*
  reference name (e.g.  refs/heads/master)


Return Values
***********************************************************

Git\\Reference

ChangeLog
***********************************************************

- method name changed from lookupRef to lookup.
  (can't define lookup method because php-compat defines `lookup` preprocessor.)

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repo);
   $ref = $manager->lookup("refs/heads/master");


See Also
***********************************************************

:doc:`Git\\Repository::lookupRef </classes/repository/lookup_ref>`