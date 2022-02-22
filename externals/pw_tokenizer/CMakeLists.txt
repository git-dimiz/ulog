cmake_minimum_required(VERSION 3.13)

project(pw_tokenizer
    VERSION
        1.0.0
    DESCRIPTION 
        "hash functions"
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
