#!/bin/bash

SERVER_NAME="r-type_server"
CLIENT_NAME="r-type_client"

rm -rf build
rm -rf ${SERVER_NAME}
rm -rf ${CLIENT_NAME}
rm -rf ./docs/html/
rm -rf ./docs/latex/
rm -rf ./vcpkg/
rm -rf ./vcpkg_installed/

# remove all .dll files
rm -rf ./*.dll