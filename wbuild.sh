#!/bin/bash

SERVER_NAME="r-type_server"
CLIENT_NAME="r-type_client"

# Check for CMake
if ! command -v cmake &> /dev/null
then
    echo "CMake not found. Please install CMake from https://cmake.org/download/ and add it to your PATH."
    exit
fi

echo "Checking for vcpkg directory..."
if [ ! -d "vcpkg" ]; then
    echo "Cloning vcpkg..."
    git clone https://github.com/microsoft/vcpkg.git
else
    echo "Updating vcpkg..."
    (cd vcpkg && git pull origin master)
fi

echo "Bootstrapping vcpkg..."
(cd vcpkg && ./bootstrap-vcpkg.sh)

echo "Installing dependencies..."
(cd vcpkg && ./vcpkg install --feature-flags=manifests,versions)

echo "Creating build directory..."
mkdir -p build
cd build

echo "Configuring and building project..."
cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build .

echo "Moving executables..."
mv server/Debug/$SERVER_NAME.exe ../
mv client/Debug/$CLIENT_NAME.exe ../

echo "Build script completed."
