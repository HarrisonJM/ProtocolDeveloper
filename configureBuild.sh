#!/bin/bash

export CC=$(which cc)
export CXX=$(which g++)

if [[ ! -e "build/" ]]; then
    mkdir build
fi

    cd build

cmake ../
