#!/bin/bash

#
# This script sets up a project to be used for the first time
#

source ~/.bash_util.sh


THIS_DIR=$(dirname "$0")

QuietRun pushd "$THIS_DIR"
    PROJECT_ROOT_DIR=$(git rev-parse --show-toplevel)
QuietRun popd

QuietRun pushd "$PROJECT_ROOT_DIR"
    PROJECT_NAME=$( basename "$PROJECT_ROOT_DIR" )
    echo "Setting up project \"$PROJECT_NAME\"."

    ./scripts/bootstrap.sh

    mkdir build
    pushd build
        ccmake ..
    popd
    ./scripts/astyle_and_build.sh


    ../yyLinuxConfig/scripts/setup_ctags_for.sh


    ./scripts/open_urls.sh docs/done_list.md
QuietRun popd
