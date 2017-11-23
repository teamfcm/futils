#
# Futils Project - Unit tests
# Created by Ganzf on 21/11/17
#

cmake_minimum_required(VERSION 3.9)
project(tests)
set(CMAKE_CXX_STANDARD 17)

# utils/Header.hpp TestFile.cpp
set(SOURCES
        utils/callback.hpp Callback.cpp
        )
add_executable(tests ${SOURCES})
include_directories(utils)
target_link_libraries(tests criterion pthread dl)
