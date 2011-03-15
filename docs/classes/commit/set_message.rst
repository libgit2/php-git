.. index::
   single: setMessage (Git\Commit method)


Git\\Commit::setMessage
===========================================================

.. note::
   have to set commit message when writing commit.

Description
***********************************************************

public **Git\\Commit::setMessage** (string *$message*)


Parameters
***********************************************************

*message*
  commit message.


Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php

    <?php
    $commit = new Git\Commit($repository);
    $commit->setMessage(
        "initial import\n" // short message
        ."\n"
        ."import from https://github.com/...\n"
		);


See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`