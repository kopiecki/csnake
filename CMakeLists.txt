cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    csnake
    VERSION "${GIT_VERSION_WO_TWEAK}"
    DESCRIPTION "Yet another snake clone"
    LANGUAGES C ASM)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

add_subdirectory(lib)
add_subdirectory(app)
