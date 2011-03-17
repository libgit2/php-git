.. index::
   single: open2 (Git\Repository method)


Git\\Repository::open2
===========================================================

Description
***********************************************************

public **Git\\Repository::open2** (string *$git_dir*, string *$git_object_dir*, string *$git_index_file*, string *$git_working_tree*)


Parameters
***********************************************************

*git_dir*
  git repository directory

*git_object_dir*
  object directory

*git_index_file*
  index file

*git_working_tree*
  working tree directory

Return Values
***********************************************************

boolean

Examples
***********************************************************

.. code-block:: php

    <?php
    
    use Git\Repository;
    
    $repo = new Repository();
    $repo->open2(
        "/home/chobie/src/libgit2/.git",        // git directory
        "/home/chobie/src/libgit2/.git/objects",// git object directory
        "/home/chobie/src/libgit2/.git/index",  // git index file
        "/home/chobie/src/libgit2/"             // git working tree
        );


See Also
***********************************************************