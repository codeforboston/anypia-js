
export LLVM=/usr/local/opt/emscripten/libexec/llvm/bin
export BINARYEN=/usr/local/opt/binaryen
#curl -L -O "https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.zip"
#unzip -q boost_1_64_0.zip
cd boost_1_64_0
./bootstrap.sh

export BOOST_INCL=`pwd`
export BOOST_LIB=`pwd`/stage/lib
cd ..
mkdir anypiab/build
cd anypiab/build
emcmake cmake -DBOOST_INCLUDEDIR=$BOOST_INCL -DBOOST_LIBRARYDIR=$BOOST_LIB ..
make -j2
cd ../..
mkdir anypiajs/build
cd anypiajs/build
emcmake cmake -DBOOST_INCLUDEDIR=$BOOST_INCL -DBOOST_LIBRARYDIR=$BOOST_LIB ..
make -j2
