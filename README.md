php-git
=======================================================

php-git is a set of PHP 5.3+ bindings to the libgit2 linkable C Git library.

How Can I Contribute?
=======================================================

* fork our repository.

<https://github.com/libgit2/php-git>

Current Development Status
=======================================================

* EXPERIMENTAL

DEPENDENCIES
=======================================================

* libgit2
* php5
* pcre

INSTALL
=======================================================

== Quick Instructions

* Install libgit2, pcre, and a build chain (Ubuntu: build-essential; Mac: xcode)
* `git clone git://github.com/libgit2/php-git.git && cd php-git/src`
* `phpize`
* `./configure`
* `make`
* `sudo make install`
* Add the extension to your /etc/php.ini
````
extension=git.so
````

Documents
=======================================================

see php-git Documents: <http://libgit2.github.com/php-git/>

you can build with sphinx.

````
# if you haven't installed php-domain yet, please install sphinxcontrib-phpdomain first.
# sudo easy_install -U sphinxcontrib-phpdomain

cd docs
make html
````
AUTHORS
=======================================================

* Shuhei Tanuma <chobieee@gmail.com>

LICENSE
=======================================================

MIT Licence.


Links
=======================================================

* libgit2: <https://github.com/libgit2/libgit2>
* php-git documents: <http://libgit2.github.com/php-git/>
