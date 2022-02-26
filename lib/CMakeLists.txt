cmake_minimum_required(VERSION 3.13)

project(ulog
    VERSION
        1.0.0
    DESCRIPTION 
        ""
)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        "src/gen/ulog_msg.pb.c"
        "src/ulog_encoder.c"
        "src/ulog.c"
        "../externals/nanopb/pb_common.c"
        "../externals/nanopb/pb_encode.c"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "include"
        "src/gen"
    PRIVATE
        "include/ulog"
        "../externals/nanopb"
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        c_std_11
)
