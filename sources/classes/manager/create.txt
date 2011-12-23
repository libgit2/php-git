.. index::
   single: create (Git\Reference\Manager method)


Git\\Reference\\Manager::create
===========================================================

.. note::
   Currentry can create non symbolic reference only.
   (this is php-git limits. this issue fix soon)

Description
***********************************************************

public **Git\\Reference\\Manager::create** (string *$name*,string *$oid*)


Parameters
***********************************************************

*name*
  reference name (e.g.  refs/heads/reference-name)

*oid*
  target commit id

Return Values
***********************************************************

boolean

Examples
***********************************************************

.. code-block:: php

   <?php
   $repo = new Git\Repository("/path/to/repository/.git");
   $manager = new Git\Reference\Manager($repo);
   $master = $repo->lookupRef("refs/heads/master");
   //create new branch `new-branch` what targets `master` commit.
   $manager->create("refs/heads/new-branch",$master->getId());

See Also
***********************************************************

:doc:`Git\\Commit </classes/commit/index>`
:doc:`Git\\Reference </classes/reference/index>`
