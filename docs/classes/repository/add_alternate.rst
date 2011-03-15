.. index::
   single: addAlternate (Git\Repository method)


Git\\Repository::addAlternate
===========================================================

add alternate backend. this feature can resolve external objects.

Description
***********************************************************

public **Git\\Repository::addAlternate** (*$backend*, *$priority*)


Parameters
***********************************************************

*backend*
  Specifies a class that inherits from :doc:`Git\\Backend </classes/backend/index>`

*priority*
  [low] 1 ... 5[high]


Return Values
***********************************************************

void

Examples
***********************************************************

See Also
***********************************************************

:doc:`Git\\Backend </classes/backend/index>`