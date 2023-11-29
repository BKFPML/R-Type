##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

file(GLOB CLIENT_FILES "src/*.cpp")

add_executable(r-type_client ${CLIENT_FILES})
