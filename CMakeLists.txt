cmake_minimum_required(VERSION 3.10)

project(Cuboid LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin-int/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")

#add_subdirectory(assimp)
#add_subdirectory(entt)
add_subdirectory(glad)
add_subdirectory(luac)
add_subdirectory(imgui)
add_subdirectory(spdlog)
add_subdirectory(ENGINE)
add_subdirectory(Sandbox)
add_subdirectory(Cuboid-Editor)


