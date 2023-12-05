##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists client
##

# Dependencies
# include(FetchContent)

# FetchContent_Declare(
#     SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 2.5.1
# )
# FetchContent_MakeAvailable(SFML)

# Project Files
file(GLOB CLIENT_FILES "src/*.cpp")
include_directories("./includes")

add_executable(r-type_client ${CLIENT_FILES})

# target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
