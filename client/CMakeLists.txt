# Project Files
file(GLOB_RECURSE CLIENT_FILES "src/*.cpp")
file(GLOB_RECURSE EXTERNAL_FILES "external/*.cpp")
include_directories("./includes")

add_executable(r-type_client ${CLIENT_FILES} ${EXTERNAL_FILES})

# Linking Dependencies
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Function to embed files as C++ headers
function(embed_file input_file output_header)
    file(READ ${input_file} file_data HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," file_data ${file_data})

    # Sanitize the output_header to be a valid C++ identifier
    string(REGEX REPLACE "[^a-zA-Z0-9_]" "_" sanitized_header ${output_header})

    set(output_header_file "${CMAKE_CURRENT_BINARY_DIR}/generated_assets/${sanitized_header}.h")
    file(WRITE ${output_header_file} "unsigned char ${sanitized_header}[] = {${file_data}};\n")
    file(APPEND ${output_header_file} "unsigned int ${sanitized_header}_len = sizeof(${sanitized_header});\n")
endfunction()

# Find all asset files
file(GLOB_RECURSE ASSET_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../assets/background/*.png" "${CMAKE_CURRENT_SOURCE_DIR}/../assets/menu/*.png" "${CMAKE_CURRENT_SOURCE_DIR}/../assets/sprites/*.gif" "${CMAKE_CURRENT_SOURCE_DIR}/../assets/fonts/*.otf" "${CMAKE_CURRENT_SOURCE_DIR}/../assets/sounds/*.ogg")

# Create a directory for generated headers
set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_assets")
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Convert each asset file to a header file
foreach(ASSET_FILE ${ASSET_FILES})
    get_filename_component(FILE_NAME ${ASSET_FILE} NAME_WE)
    embed_file(${ASSET_FILE} ${FILE_NAME})
    list(APPEND GENERATED_HEADERS "${GENERATED_DIR}/${FILE_NAME}.h")
endforeach()

# Include the directory where the generated headers are
include_directories(${GENERATED_DIR})

# Add generated headers to your executable
target_sources(r-type_client PRIVATE ${GENERATED_HEADERS})
