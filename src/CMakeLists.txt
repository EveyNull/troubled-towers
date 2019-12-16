cmake_minimum_required(VERSION 3.11.4)
project(BasicReb0rn)
set(GAMEDATA_FOLDER "data")
set(ENABLE_ENET  OFF  CACHE BOOL "Adds Networking"   FORCE)
set(ENABLE_SOUND ON   CACHE BOOL "Adds SoLoud Audio" FORCE)
set(ENABLE_JSON  ON   CACHE BOOL "Adds JSON to the Project" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

## out of source builds ##
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
## out of source builds ##

## add the files to be compiled here
set(SOURCE_FILES
        "game/main.cpp"
        "game/game.cpp"
        "game/Utility/TextParser.cpp")

set(HEADER_FILES
        "game/game.h"
        "game/Utility/TextParser.h" game/Utility/ScreenDisplay.cpp game/Utility/ScreenDisplay.h game/Utility/CommandManager.cpp game/Utility/CommandManager.h game/Utility/Word.cpp game/Utility/Word.h game/Utility/WordTypes/Verb.cpp game/Utility/WordTypes/Verb.h game/Utility/WordTypes/Object.cpp game/Utility/WordTypes/Object.h game/Utility/WordTypes/ReturnAction.h game/Objects/Player.cpp game/Objects/Player.h game/Objects/Location.cpp game/Objects/Location.h game/Objects/Item.cpp game/Objects/Item.h game/Utility/Command.h game/Utility/WordTypes/Direction.h game/Utility/FindObjectHelper.cpp game/Utility/FindObjectHelper.h game/Utility/WordTypes/Reaction.h game/Utility/WordTypes/Action.h)

## the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

## these are the build directories
get_target_property(CLIENT ${PROJECT_NAME} NAME)
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/${CLIENT}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/${CLIENT}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/${CLIENT}/bin")

## important build scripts
include(build/compilation)
include(libs/asge)
include(libs/json)
include(libs/soloud)
include(tools/itch.io)

## hide console unless debug build ##
if (NOT CMAKE_BUILD_TYPE STREQUAL  "Debug" AND WIN32)
    target_compile_options(${PROJECT_NAME} -mwindows)
endif()


