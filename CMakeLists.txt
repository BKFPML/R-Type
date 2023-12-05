##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.12)
project(R-Type)

set(CMAKE_CXX_STANDARD 17)

# Vcpkg
if(MSVC)
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
else()
    set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "")
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

# Subdirectories
add_subdirectory(client)
add_subdirectory(server)
