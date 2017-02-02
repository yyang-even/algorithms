#!/bin/bash

#
# This script setup develop environment by installing required libraries
#

Echo_Error() {
    cat <<< "$@" 1>&2;
}

Install_or_Update_Packages() {
    operating_system=$(uname)
    if [ $operating_system == "Linux" ]; then
        if [ -f /etc/redhat-release ]; then
            sudo yum --assumeyes install "$@"
        elif [ -f /etc/debian_version ]; then
            sudo apt-get --yes install "$@"
        else
            Echo_Error "Error: Unsupported distribution"
            cat /etc/*-release
            return 1
        fi
    else
        Echo_Error "Error: Unsupported OS: " $operating_system
        return 1
    fi
    return $?
}

# Install third-party libraries
Install_or_Update_Packages libboost-all-dev
# Copy git hooks
SCRIPT_DIR=$(dirname "$0")
cp --interactive $SCRIPT_DIR/git_hooks/* $SCRIPT_DIR/../.git/hooks/
