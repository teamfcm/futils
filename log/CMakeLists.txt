cmake_minimum_required(VERSION 3.7)
project(log)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp flog.hpp)
add_executable(log ${SOURCE_FILES})