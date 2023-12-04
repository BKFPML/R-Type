##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

file(GLOB CLIENT_FILES "src/*.cpp")
include_directories("./includes")

add_executable(r-type_client ${CLIENT_FILES})

# Linking with Conan packages
target_link_libraries(r-type_client PRIVATE ${CONAN_LIBS} sfml-graphics sfml-window sfml-system)

