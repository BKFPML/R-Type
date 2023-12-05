#!/bin/bash

SERVER_NAME="r-type_server"
CLIENT_NAME="r-type_client"

# mkdir -p build
# cd build || exit

# cmake ..

# make

# mv ./server/${SERVER_NAME} ../
# mv ./client/${CLIENT_NAME} ../

# vcpkg
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/microsoft/vcpkg.git
else
    cd vcpkg
    git pull origin master
    cd ..
fi

# Bootstrap vcpkg
cd vcpkg
./bootstrap-vcpkg.sh

# Install dependencies
./vcpkg install sfml boost-asio

cd ..

mkdir -p build
cd build || exit

cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build .

mv ./server/${SERVER_NAME} ../
mv ./client/${CLIENT_NAME} ../
