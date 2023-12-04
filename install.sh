#!/bin/bash

SERVER_NAME="r-type_server"
CLIENT_NAME="r-type_client"

# Function to check if a program exists
program_exists () {
    type "$1" &> /dev/null ;
}

# Check for Python and pip
if program_exists python3 && program_exists pip3 ; then
    echo "Python and pip are installed."
else
    echo "Please install Python and pip."
    exit 1
fi

# Install Conan if it's not installed
if program_exists conan ; then
    echo "Conan is already installed."
else
    echo "Installing Conan..."
    pip3 install conan || { echo "Failed to install Conan."; exit 1; }
    export PATH=$PATH:~/.local/bin
fi

# Ensure the default Conan profile exists or create it if it doesn't
if [ ! -f "$HOME/.conan2/profiles/default" ]; then
    conan profile detect || { echo "Failed to create default Conan profile."; exit 1; }
else
    echo "Default Conan profile already exists."
fi

# Add the Bincrafters remote for Conan
# conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan || { echo "Failed to add the Bincrafters remote."; exit 1; }

# Function to install CMake based on the Linux distribution
install_cmake () {
    if [ -f /etc/debian_version ]; then
        # Debian-based systems
        echo "Debian-based system detected. Installing CMake..."
        sudo apt-get update
        sudo apt-get install -y cmake
    elif [ -f /etc/redhat-release ]; then
        # Fedora systems
        echo "Fedora system detected. Installing CMake..."
        sudo dnf install -y cmake
    else
        echo "Unsupported Linux distribution. Please manually install CMake."
        exit 1
    fi
}

# Install CMake if it's not installed
if program_exists cmake ; then
    echo "CMake is already installed."
else
    install_cmake
fi

# Create a build directory and navigate into it
mkdir -p build && cd build || exit

# Run Conan to install dependencies
conan install .. --build=missing --output-folder=. -c tools.system.package_manager:mode=install

# Run CMake to configure the project
cmake ..

# Build the project
make

# Move the executables to the desired location
mv "./server/${SERVER_NAME}" ../
mv "./client/${CLIENT_NAME}" ../

echo "Installation and build complete."
