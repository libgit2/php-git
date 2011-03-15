.. index::
   single: setCommitter (Git\Commit method)


Git\\Commit::setCommitter
===========================================================

Description
***********************************************************

public **Git\\Commit::setCommitter** (Git\\Signature *$committer*)


Parameters
***********************************************************

*committer*
  committer signature


Return Values
***********************************************************

void

Examples
***********************************************************

.. code-block:: php

   <?php
   $commit = new Git\Commit($repository);
   $commit->setCommitter(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));

See Also
***********************************************************

:doc:`Git\\Signature </classes/signature/index>`
:doc:`Git\\Commit::setAuthor </classes/commit/set_committer>`
`DateTime(PHP Documents) <http://jp.php.net/manual/en/class.datetime.php>`_
`DateTimeZone(PHP Documents) <http://jp.php.net/manual/en/class.datetimezone.php>`_