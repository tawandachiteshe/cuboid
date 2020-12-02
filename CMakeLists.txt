cmake_minimum_required(VERSION 3.10)

project(Cuboid LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin-int/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_DATADIR "${PROJECT_SOURCE_DIR}/bin-int/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)



add_subdirectory(vendor/assimp)
#add_subdirectory(entt)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/luac)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/spdlog)
add_subdirectory(ENGINE)
add_subdirectory(Sandbox)
add_subdirectory(vendor/yaml-cpp)
add_subdirectory(Cuboid-Editor)

set_target_properties(assimp assimp_cmd glad luac imgui spdlog yaml-cpp zlib zlibstatic unit uninstall IrrXML lua UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER HiddenTargets)


