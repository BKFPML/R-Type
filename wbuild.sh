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


# Assuming vcpkg installs SFML to this path
# SFML_DLL_PATH="C:/Users/felix/School/R-TYPE\R-Type/vcpkg_installed\x64-windows/bin/"
SFML_DLL_PATH="C:/Users/felix/School/R-TYPE/R-Type/build/client/Debug/"

# Temporarily add SFML DLL path to the PATH environment variable
# export PATH=$PATH:$SFML_DLL_PATH

# echo "Copying SFML DLLs..."
cp C:/Users/felix/School/R-TYPE/R-Type/build/client/Debug/*.dll ../ || echo "Failed to copy SFML DLLs."

echo "Moving executables..."
mv server/Debug/$SERVER_NAME.exe ../
mv client/Debug/$CLIENT_NAME.exe ../

echo "Build script completed."


# #!/bin/bash

# SERVER_NAME="r-type_server.exe"
# CLIENT_NAME="r-type_client.exe"

# # Check for CMake
# if ! command -v cmake &> /dev/null; then
#     echo "CMake not found. Please install CMake from https://cmake.org/download/ and add it to your PATH."
#     exit 1
# fi

# echo "Checking for vcpkg directory..."
# if [ ! -d "vcpkg" ]; then
#     echo "Cloning vcpkg..."
#     git clone https://github.com/microsoft/vcpkg.git
# else
#     echo "Updating vcpkg..."
#     (cd vcpkg && git pull origin master)
# fi

# echo "Bootstrapping vcpkg..."
# (cd vcpkg && ./bootstrap-vcpkg.sh) || exit 1

# echo "Installing dependencies..."
# (cd vcpkg && ./vcpkg integrate install --feature-flags=manifests,versions) || exit 1

# echo "Creating build directory..."
# mkdir -p build
# cd build || exit 1

# # echo "Configuring and building project..."
# # # Add -DCMAKE_BUILD_TYPE=Release to build in release mode
# # cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake .. || exit 1
# # cmake --build . || exit 1

# BUILD_TYPE=${1:-Release}

# echo "Configuring and building project for $BUILD_TYPE..."
# cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake .. || exit 1
# cmake --build . || exit 

# # Set the correct relative path to the SFML DLLs
# SFML_DLL_PATH="../vcpkg/packages/sfml_x64-windows/bin/"

# # echo "Moving executables..."
# # mv server/Release/$SERVER_NAME ../ || echo "Failed to move server executable."
# # mv client/Release/$CLIENT_NAME ../ || echo "Failed to move client executable."

# echo "Moving executables..."
# mv server/$BUILD_TYPE/$SERVER_NAME ../ || echo "Failed to move server executable."
# mv client/$BUILD_TYPE/$CLIENT_NAME ../ || echo "Failed to move client executable."

# echo "Copying SFML DLLs..."
# cp $SFML_DLL_PATH/*.dll ../ || echo "Failed to copy SFML DLLs."

# echo "Build script completed."
