#!/bin/bash

# Exit on any error
set -e

# Create build directory if it doesn't exist
mkdir -p build

# Change to build directory
cd build

# Run CMake to generate build files
cmake ..

# Build the project
cmake --build .

# Optionally run tests
ctest --output-on-failure
