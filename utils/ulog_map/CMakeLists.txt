cmake_minimum_required(VERSION 3.13)

project(ulog_map
    VERSION
        1.0.0
    DESCRIPTION 
        ""
)

# workaround for elfio
add_library(elfio INTERFACE)
target_include_directories(elfio
    INTERFACE
        "../../externals/ELFIO/"
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        "src/main.cpp"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "include"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ulog
        CLI11
        nlohmann_json
        elfio
)
