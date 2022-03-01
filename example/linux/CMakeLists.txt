cmake_minimum_required(VERSION 3.13)

project(example_linux
    VERSION
        1.0.0
    DESCRIPTION 
        ""
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.c
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ulog
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -std=gnu11
        -O0
        -Wall
        -Wextra
        -Wpedantic
        -Wno-gnu-zero-variadic-macro-arguments
)