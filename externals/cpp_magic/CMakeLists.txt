cmake_minimum_required(VERSION 3.13)

project(cpp_magic
    VERSION
        1.0.0
    DESCRIPTION 
        "pre-processore magic library"
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
