Git\\Object Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git object.


Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: string Git::Object::getId()

   get current object sha1 hash.

.. cpp:function:: int Git::Object::getType()

   get current object type.

.. cpp:function:: int Git::Object::write()

   write current object to odb.
