##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## CMakeLists server
##

file(GLOB SERVER_FILES "src/*.cpp")

include_directories("./includes")

add_executable(r-type_server ${SERVER_FILES})

# link boost.asio packages
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(r-type_server ${Boost_LIBRARIES})
