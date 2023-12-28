##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

# Project Files
file(GLOB CLIENT_FILES "src/*.cpp")
file(GLOB EXTERNAL_FILES "external/*.cpp")
include_directories("./includes")

add_executable(r-type_client ${CLIENT_FILES} ${EXTERNAL_FILES})

# Linking Dependencies
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
