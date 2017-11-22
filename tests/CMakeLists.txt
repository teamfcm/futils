#
# Futils Project - Unit tests
# Created by Ganzf on 21/11/17
#

cmake_minimum_required(VERSION 3.9)
project(tests)
set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
    get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} PATH)
    set (COMMON_DIR ${PARENT_DIR})
    message("Changing common dir to ${COMMON_DIR}")
else()
    set(COMMON_DIR ${CMAKE_SOURCE_DIR})
endif()
include_directories(${COMMON_DIR})
set(SOURCES Callback.cpp
        ${COMMON_DIR}/callback.hpp)

add_executable(unit_tests ${SOURCES})
target_link_libraries(unit_tests criterion pthread)
