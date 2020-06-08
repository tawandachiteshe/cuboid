cmake_minimum_required(VERSION 3.10)
project(lua LANGUAGES C)

SET(SRC_FILES
        ../src/lua.c
        ../src/lua.h
        )

add_executable(lua ${SRC_FILES})

link_directories(${luac_BINARY_DIR})
target_include_directories(lua PUBLIC ../src)
target_link_libraries(lua PUBLIC luac)