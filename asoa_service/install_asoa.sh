#!/bin/bash

#
# INSTALLATION SETUP FOR MANUAL CONTROL SERVICE
# Run in terminal by executing `sudo ./install.sh`
#
# Not every dependency is installed by this script. According to README.md, some programs like Git, CMake or GCC and the ASOA dependencies
# are still required to be installed beforehand. This is because some systems might already meet those requirements anyways.
#

# Make sure the following script is executed from project root
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "$SCRIPT_DIR" || exit

sudo apt update

echo -e "\n\033[0;33m--- INSTALLING DART DEPENDENCIES ---\033[0m\n"

# Dart
dart pub get

echo -e "\n\033[0;33m--- BUILDING EXECUTABLE ---\033[0m\n"
cd scripts && ./buildService.sh
