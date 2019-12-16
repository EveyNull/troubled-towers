cmake_minimum_required(VERSION 3.11.4)
set(CMAKE_CXX_STANDARD 14)

## project independent scripts ##
include(cmake/build/flags.cmake)
include(cmake/build/platform.cmake)
include(cmake/tools/clang.format.cmake)
include(cmake/tools/python.cmake)
include(cmake/tools/cargo.cmake)

## set to true to use dlls instead of static libs ##
option(STATIC_APP "Build a static application" ON)
if( STATIC_APP )
    message("##### BUILDING STATIC APPLICATION #####")
    set(BUILD_SHARED_LIBS false)
else()
    message("##### BUILDING SHARED APPLICATION #####")
    set(BUILD_SHARED_LIBS true)
endif()

## itch.io: enables deployment targets ##
set(GAMEDATA_FOLDER "data")
set(ITCHIO_USER     "")

## enable the game project ##
add_subdirectory(src)

