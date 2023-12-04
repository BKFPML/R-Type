#!/bin/bash

SERVER_NAME="r-type_server"
CLIENT_NAME="r-type_client"

mkdir -p build
cd build || exit

cmake ..

make

mv ./server/${SERVER_NAME} ../
mv ./client/${CLIENT_NAME} ../
