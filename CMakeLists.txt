##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.12)
project(R-Type)

set(CMAKE_CXX_STANDARD 17)

# Include the Conan-generated file
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
endif()

add_subdirectory(client)
add_subdirectory(server)
