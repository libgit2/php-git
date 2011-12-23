.. index::
   single: getList (Git\Reference\Manager method)


Git\\Reference\\Manager::getList
===========================================================

get available reference list.

Description
***********************************************************

public **Git\\Reference\\Manager::getList** ()


Parameters
***********************************************************



Return Values
***********************************************************

array Git\\Reference

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repo);
   $lists = $manager->getList();

See Also
***********************************************************

:doc:`Git\\Reference </classes/reference/index>`