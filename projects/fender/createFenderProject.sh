#!/bin/bash

cp -r ./fenderGettingStarted "$1"
sed -i "s/TEMPLATE_NAME/$1/g" $1/CMakeLists.txt
