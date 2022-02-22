cmake_minimum_required(VERSION 3.13)

project(ulog_cat
    VERSION
        1.0.0
    DESCRIPTION 
        ""
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        "src/main.cpp"
        "src/ulog_decoder.cpp"
        "../../externals/nanopb/pb_common.c"
        "../../externals/nanopb/pb_decode.c"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "include"
        "../../externals/nanopb"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ulog
        CLI11
        nlohmann_json
)
