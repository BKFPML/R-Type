##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

file(GLOB CLIENT_FILES "src/*.cpp")
include_directories("./includes")

add_executable(r-type_client ${CLIENT_FILES})

# Linking with SFML and Boost
find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics network audio)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
