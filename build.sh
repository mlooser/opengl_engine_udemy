#!/bin/bash

# Script to build the project

CMAKE="/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake"

# Check for clean argument
if [ "$1" == "clean" ]; then
    echo "Cleaning build directory..."
    $CMAKE --build cmake-build-debug --target clean
    echo "Clean complete!"
    exit 0
fi

# Check for run argument
if [ "$1" == "run" ]; then
    echo "Building and running project..."
    echo ""

    # Build first
    BUILD_OUTPUT=$($CMAKE --build cmake-build-debug 2>&1)
    BUILD_STATUS=$?

    # Display build output
    echo "$BUILD_OUTPUT"

    if [ $BUILD_STATUS -eq 0 ]; then
        echo ""
        echo "Build successful! Running..."
        echo "========================================"
        ./cmake-build-debug/GameDevelopmentProject
        exit 0
    else
        echo ""
        echo "Build failed! Cannot run."
        exit 1
    fi
fi

echo "Building project..."
echo ""

# Build and capture output
BUILD_OUTPUT=$($CMAKE --build cmake-build-debug 2>&1)
BUILD_STATUS=$?

# Display the output
echo "$BUILD_OUTPUT"

echo ""
echo "========================================"
echo "Summary of warnings from your code:"
echo "========================================"
echo "$BUILD_OUTPUT" | grep -E "engine/source.*warning|source/.*warning" | grep -v "thirdparty"

if [ $BUILD_STATUS -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo "Run with: ./cmake-build-debug/GameDevelopmentProject"
else
    echo ""
    echo "Build failed!"
    exit 1
fi
