#!/bin/bash

# Script to run all tests

CMAKE="/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake"
CTEST="/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/ctest"

echo "Building tests..."
$CMAKE --build cmake-build-debug --target EngineTests

echo ""
echo "Running tests..."
$CTEST --test-dir cmake-build-debug/engine_build/tests --output-on-failure
