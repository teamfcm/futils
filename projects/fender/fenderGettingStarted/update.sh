#!/bin/bash

# Cloning into teamfcm/futils

rm -rf dl_futils
git clone -b master --single-branch http://github.com/teamfcm/futils dl_futils --depth=1

# Cloning ok
echo "Ok - Recovered latest Futils version."

rm -rf ./futils
cp -r dl_futils/utils ./futils
cp dl_futils/projects/fender/release/libfender.a ./lib
cp dl_futils/projects/fender/include/*.hpp ./include
rm -rf dl_futils
