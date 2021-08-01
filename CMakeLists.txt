cmake_minimum_required(VERSION 3.0.2) 

project(catdoc DESCRIPTION "MS office old format parser (OLE file)")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DHAVE_STDINT_H)

file(GLOB_RECURSE LIB_SOURCES
    "src/*.h"
    "src/*.c"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${LIB_SOURCES})

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        src
        compat
)
