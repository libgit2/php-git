.. index::
   single: add (Git\Index method)


Git\\Index::add
===========================================================

add specified file to your index. you have to call Git::Index::write after this method.


Description
***********************************************************

public **Git\\Index::add** (string *$path*)


Parameters
***********************************************************

*path*
  fill them out later


Return Values
***********************************************************

Examples
***********************************************************

.. code-block:: php

    <?php
    $repo = new Git\Repository("/tmp/sample/.git");
    $index = $repo->getIndex();
    $index->add("newcontents.txt");
    $index->write();
    $index->refresh();

See Also
***********************************************************