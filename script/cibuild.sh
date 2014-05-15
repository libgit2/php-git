export NO_INTERACTION=1
export TESTS="--show-diff -q"

mkdir $TRAVIS_BUILD_DIR/libgit2/build
cd $TRAVIS_BUILD_DIR/libgit2/build
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DCMAKE_C_FLAGS=-fPIC ..
cmake --build .
cd $TRAVIS_BUILD_DIR

phpize
./configure
make
make test
