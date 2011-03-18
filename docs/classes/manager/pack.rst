.. index::
   single: pack (Git\Reference\Manager method)


Git\\Reference\\Manager::pack
===========================================================

.. note::
   WARNING: calling this method may invalidate any existing references previously loaded on the cache.

Description
***********************************************************

public **Git\\Reference\\Manager::pack** ()


Parameters
***********************************************************


Return Values
***********************************************************

boolean

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repo);
   $manager->pack();

See Also
***********************************************************