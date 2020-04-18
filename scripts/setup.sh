#!/bin/bash

#
# This script sets up a project to be used for the first time
#


THIS_DIR=$(dirname "$0")
PROJECT_ROOT_DIR="$THIS_DIR/.."


pushd "$PROJECT_ROOT_DIR"
    PROJECT_NAME=$( basename `git rev-parse --show-toplevel` )
    echo "Setting up project \"$PROJECT_NAME\"."

    ./scripts/bootstrap.sh

    mkdir build
    pushd build
        ccmake ..
    popd
    ./scripts/astyle_and_build.sh


    ../yyLinuxConfig/scripts/setup_ctags_for.sh


    ./scripts/open_urls.sh docs/done_list.md
popd
