.. index::
   single: __construct (Git\Signature method)


Git\\Signature::__construct
===========================================================

create signature.

Description
***********************************************************

public **Git\\Signature::__construct** (string *$name*,string *$email*, \\DateTime *$when*)


Parameters
***********************************************************

*name*
  full name. e.g) John Smith

*email*
  email. e.g) john.smith@example.com

*when*
  commit time


Return Values
***********************************************************

:doc:`Git\\Signature </classes/signature/index>`

Examples
***********************************************************

.. code-block:: php

   <?php
   $sig = new Git\Signature("John Smith","john.smith@example.com",new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo")))));


.. note::
   should not specified unixtime. e.g) new DateTime("@1294147094")

See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`