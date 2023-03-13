#!/bin/bash
BUILD_DIR=../build

(rm -rf $BUILD_DIR && mkdir $BUILD_DIR) || (echo "Could not create an empty build directory!"; exit)
cmake -S .. -B $BUILD_DIR
make -C $BUILD_DIR