cmake_minimum_required(VERSION 3.7)
project(Fson)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(SOURCE_FILES main.cpp Fini.hpp)
add_executable(Fson ${SOURCE_FILES})