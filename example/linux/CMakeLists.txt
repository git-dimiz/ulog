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
        -g3
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Wpedantic # warn if non-standard C is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wno-gnu-zero-variadic-macro-arguments
)