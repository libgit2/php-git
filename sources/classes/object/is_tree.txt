.. index::
   single: isTree (Git\Object method)


Git\\Object::isTree
===========================================================

return true when object is tree.


Description
***********************************************************

public **Git\\Object::isTree** ()


Parameters
***********************************************************



Return Values
***********************************************************

boolean

Examples
***********************************************************

.. code-block:: php

   <?php

   foreach($tree->entries as $entry){
      $object = $entry->toObject();
      if($object->isTree()){
          //
      } else if($object->isBlob()){
          //
      }
   }

See Also
***********************************************************


:doc:`Git\\Object::isBlob </classes/object/is_blob>`
:doc:`Git\\Object::getType </classes/object/get_type>`