cmake_minimum_required(VERSION 3.0.2) 

project(catdoc DESCRIPTION "MS office old format parser (OLE file)")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

file(GLOB_RECURSE LIB_SOURCES
    "src/*.h"
    "src/*.c"

)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${LIB_SOURCES})

add_library(catdoc STATIC ${LIB_SOURCES})

target_include_directories(catdoc PUBLIC "src"
                                         "compat")
#target_include_directories(catdoc PRIVATE ${CONAN_INCLUDE_DIRS})
#target_link_libraries(catdoc Common ziplib ${CONAN_LIBS})
