#!/bin/bash

BUILD_DIR="b"

export PATH="/opt/local/bin/:$PATH"

if [[ ! -e "$BUILD_DIR" ]]; then
	mkdir "$BUILD_DIR";
	cd "$BUILD_DIR";
	cmake ..
	cd ..
fi;

cd "$BUILD_DIR";
make
#ctest --verbose
./lib/test_enums.cpp