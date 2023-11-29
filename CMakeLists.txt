##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeList.txt
##

cmake_minimum_required(VERSION 3.12)
project(R-Type)

set(CMAKE_CXX_STANDARD 17)

# Dependencies
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/external")

# Source files
file(GLOB SOURCES "src/*.cpp")

# Executable
add_executable(r-type ${SOURCES})
