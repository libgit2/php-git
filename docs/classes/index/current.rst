.. index::
   single: current (Git\Index method)


Git\\Index::current
===========================================================

Iterator interface.

Description
***********************************************************

public **Git\\Index::current** ()


Parameters
***********************************************************



Return Values
***********************************************************

Examples
***********************************************************

.. code-block:: php

    <?php
    $repo = new Git\Repository("/tmp/specified.git");
    $index = $repo->getIndex();
    foreach($index as $hash => $entry){
      var_dump($entry);
    }

See Also
***********************************************************

`The Iterator interface(PHP Documents) <http://jp.php.net/manual/en/class.iterator.php>`_
