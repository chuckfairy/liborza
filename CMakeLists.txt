# Jack cmake

project( liborza CXX )

cmake_minimum_required( VERSION 2.7 )

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_C_STANDARD 11 )

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
set(CMAKE_C_FLAGS "-std=c11 ${CMAKE_C_FLAGS}")


# RPATH
set( CMAKE_MACOSX_RPATH 1 )

set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )


# CPack

INCLUDE( CPack )


# Main setup

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/CMake" )


# Config

set( LIBORZA_VERSION "0.6.2" )

set( LIBORZA_ROOT_PATH "${PROJECT_SOURCE_DIR}" )

set( LIBORZA_SRC_PATH "${PROJECT_SOURCE_DIR}/src" )

set( LIBORZA_LIB_PATH "${CMAKE_MODULE_PATH}" "${PROJECT_SOURCE_DIR}/lib-src" )


# CMake Config type [Linux, Pi]
# Linux default

add_definitions(-DORZA_BUILD_TYPE=${ORZA_BUILD_TYPE})

if( ORZA_BUILD_TYPE STREQUAL "" )
    set( ORZA_BUILD_TYPE "Linux" )
endif()


# @TODO add possible OS check

set( LIBORZA_HAS_LV2 true )

set( LIBORZA_PLUGIN_TYPES
    "LV2"
)


# Boost

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


## Main includes

add_subdirectory( src )

add_subdirectory( test )
