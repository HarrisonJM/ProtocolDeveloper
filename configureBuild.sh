#!/bin/bash

export CC=$(which cc)
export CXX=$(which g++)

if [[ ! -e "build/" ]]; then
    mkdir ../build
fi

cd ../build

# cmake will automagically pick up the CMakeFileLists.txt and commence the build
# where it was called
cmake ../ProtocolDeveloper
