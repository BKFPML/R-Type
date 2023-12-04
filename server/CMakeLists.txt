##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists server
##

file(GLOB SERVER_FILES "src/*.cpp")

include_directories("./includes")

add_executable(r-type_server ${SERVER_FILES})
