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

if [ -f "/etc/debian_version" ]; then
    sudo apt-get install pkg-config
    sudo apt install autoconf libtool
    sudo apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev
fi

# Install dependencies from vcpkg.json

./vcpkg install
./vcpkg update



cd ..
mkdir -p build
cd build || exit

cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build .

mv ./server/${SERVER_NAME} ../
mv ./client/${CLIENT_NAME} ../
