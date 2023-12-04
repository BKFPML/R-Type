##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

# Project Files
file(GLOB CLIENT_FILES "src/*.cpp")

include_directories("./includes")

# Executable
add_executable(r-type_client ${CLIENT_FILES})

# Linking with Conan packages
target_link_libraries(r-type_client ${CONAN_LIBS})
