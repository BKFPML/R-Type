@echo off
SET SERVER_NAME=r-type_server
SET CLIENT_NAME=r-type_client

REM Check for CMake
where cmake >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    echo CMake not found. Please install CMake from https://cmake.org/download/ and add it to your PATH.
    exit /b
)

echo Checking for vcpkg directory...
IF NOT EXIST vcpkg (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
) ELSE (
    cd vcpkg
    git pull origin master
    cd ..
)

echo Bootstrapping vcpkg...
cd vcpkg
bootstrap-vcpkg.bat
cd ..

pause

echo Installing dependencies...
cd vcpkg
vcpkg install --feature-flags=manifests,versions
cd ..

pause

echo Creating build directory...
mkdir build
cd build

echo Configuring and building project...
cmake -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake ..
cmake --build .

echo Moving executables...
move .\server\Debug\%SERVER_NAME%.exe ..
move .\client\Debug\%CLIENT_NAME%.exe ..

echo Build script completed.
