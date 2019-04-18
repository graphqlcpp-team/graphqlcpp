#!/bin/sh
echo build result is in the out folder
rm -fr ./build
mkdir ./build
cd ./build
cmake ..
make
make install