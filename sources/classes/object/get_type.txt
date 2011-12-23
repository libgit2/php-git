.. index::
   single: getType (Git\Object method)


Git\\Object::getType
===========================================================

returns current object type

Description
***********************************************************

public **Git\\Object::getType** ()


Parameters
***********************************************************


Return Values
***********************************************************

int object_type

- Git\\Object\\Tree
- Git\\Object\\Blob

Examples
***********************************************************

.. code-block:: php

   <?php

   foreach($tree->entries as $entry){
      $object = $entry->toObject();
      if($object->getType() == Git\Object\Tree){
          //
      }
   }

See Also
***********************************************************

:doc:`Git\\Object::isTree </classes/object/is_tree>`
:doc:`Git\\Object::isBlob </classes/object/is_blob>`