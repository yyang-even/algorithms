#!/bin/bash

#
# This script installs required dependencies.
#

echo "Installing dependencies."
sudo apt-get update
sudo apt-get --yes install libboost-all-dev