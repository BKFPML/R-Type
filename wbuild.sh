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

echo "Configuring and building project in Release mode..."
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Release

# Assuming vcpkg installs SFML to this path
SFML_DLL_PATH="./client/Release/"

# echo "Copying SFML DLLs..."
cp ./client/Release/*.dll ../ || echo "Failed to copy SFML DLLs."

echo "Moving executables..."
cp server/Release/$SERVER_NAME.exe ../
cp client/Release/$CLIENT_NAME.exe ../

echo copy levels to build dir
cp -r ../levels/ ./server/Release/

echo "Build script completed."
