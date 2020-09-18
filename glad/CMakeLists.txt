cmake_minimum_required(VERSION 3.10)

project(glad C)


add_library(glad STATIC src/glad.c include/glad/glad.h)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)