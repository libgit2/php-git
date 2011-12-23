.. index::
   single: setParent (Git\Commit method)


Git\\Commit::setParent
===========================================================

.. note::
   php-git can't add multiple parents now.
   this limit will fix later.

.. note::
   do not call this method when first commit.

Description
***********************************************************

public **Git\\Commit::setParent** (string *$hash*)


Parameters
***********************************************************

*hash*
  commit hash id

Return Values
***********************************************************

void

Examples
***********************************************************

- First Commit

.. code-block:: php

    <?php
    $repository = Git\Repository::init("/sample.git",true);
    $blob = new Git\Blob($repository);
    $blob->setContent("First Object1");
    $hash = $blob->write();
    $tree = new Git\Tree($repository);
    $tree->add($hash,"README",100644);
    $tree_hash = $tree->write();
    $commit = new Git\Commit($repository);
    $commit->setAuthor(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));
    $commit->setCommitter(new Git\Signature("Someone","someone@example.com", new DateTime("2011-01-01 00:00:00",new DateTimezone("Asia/Tokyo"))));
    $commit->setTree($tree->getId());
    // when first commit. do not call setParent.
    //$commit->setParent(""); 
    $commit->setMessage("initial import");
    $master_hash = $commit->write();


See Also
***********************************************************

:doc:`Git\\Signature </classes/signature/index>`
:doc:`Git\\Commit </classes/commit/index>`