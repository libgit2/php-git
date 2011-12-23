.. index::
   single: getEntry (Git\Index method)


Git\\Index::getEntry
===========================================================

returns specified index entry.

Description
***********************************************************

public **Git\\Index::getEntry** (int *$offset* = 0)


Parameters
***********************************************************

*offset*
  index offset


Return Values
***********************************************************

Stdclass

Examples
***********************************************************

.. code-block::php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $index = $repo->getIndex();
    $result = $index->getEntry(0);
    /*
    object(stdClass)#4 (12) {
      ["path"]=>
      string(10) ".gitignore"
      ["oid"]=>
      string(40) "5b1a5b7ad3dd7141ccacd25e50e3078de4288a22"
      ["dev"]=>
      int(2050)
      ["ino"]=>
      int(1205498)
      ["mode"]=>
      int(33188)
      ["uid"]=>
      int(1000)
      ["gid"]=>
      int(1000)
      ["file_size"]=>
      int(364)
      ["flags"]=>
      int(10)
      ["flags_extended"]=>
      int(0)
      ["ctime"]=>
      int(1294640280)
      ["mtime"]=>
      int(1294640280)
    }
    */

.. note::
   return object may change next development

See Also
***********************************************************