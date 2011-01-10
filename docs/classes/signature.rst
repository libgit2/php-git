Git\\Signature Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
representation of git signature.


Methods
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:function:: Git::Signature Git::Signature::__construct(name, email, DateTime time)

   create new signature.


   .. code-block:: php

      <?php
      
      $author = new Git\Signature("Someone","someone@example.com", new \DateTime());
      /*
      object(Git\Signature)#1 (3) {
        ["name"]=>
        string(7) "Someone"
        ["email"]=>
        string(19) "someone@example.com"
        ["time"]=>
        int(1294641265)
      }
      */

.. note:: setter / getter methods avaiable soon. you do not update directry.