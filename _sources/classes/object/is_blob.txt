.. index::
   single: isBlob (Git\Object method)


Git\\Object::isBlob
===========================================================

return true when object is blob.

Description
***********************************************************

public **Git\\Object::isBlob** ()


Parameters
***********************************************************


Return Values
***********************************************************

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

:doc:`Git\\Object::isTree </classes/object/is_tree>`
:doc:`Git\\Object::getType </classes/object/get_type>`