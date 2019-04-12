#!/bin/bash


NUMBER_CORES=$(grep ^cpu\\scores /proc/cpuinfo | awk '{print $4}' | uniq)

astyle --recursive --options="scripts/astyle.rc" "*.cpp" "*.h"

pushd build
    echo "Compiling with jobs:" $NUMBER_CORES
    make --jobs $NUMBER_CORES
popd
