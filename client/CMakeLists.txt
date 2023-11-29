##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

file(GLOB CLIENT_FILES "src/*.cpp")

include_directories("./includes")

add_executable(r-type_client ${CLIENT_FILES})
