.. index::
   single: find (Git\Index method)


Git\\Index::find
===========================================================

returns specified file offset in git_index.

.. note::
   this method may change next development.

Description
***********************************************************

public **Git\\Index::find** (string *$path*)


Parameters
***********************************************************

*path*
  file name

Return Values
***********************************************************

int offset

Examples
***********************************************************

.. code-block::php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $index = $repo->getIndex();
    $offset = $index->find("README.md");

See Also
***********************************************************