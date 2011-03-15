Installation
==================================================

.. code-block:: bash

   cd /tmp
   git clone https://github.com/libgit2/libgit2 libgit2
   git clone https://github.com/libgit2/php-git php-git
   cd libgit2
   git checkout `cat ../php-git/LIBGIT2_VERSION`
   ./waf configure
   ./waf build-shared
   sudo ./waf install-shared

   cd ../php-git/src
   phpize
   ./configure && make
   sudo make install
   # add your php.ini
   # extension=git.so

.. note::
   php-git still under development status.
   should not use production environment.