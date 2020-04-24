#!/bin/bash

#
# This script setup develop environment by installing required libraries
#

echo "Installing dependencies."
sudo apt-get --yes install libboost-all-dev


echo "Setup submodules."
git submodule update --init
