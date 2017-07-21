cmake_minimum_required(VERSION 3.7)
project(SFMLRender)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES library.cpp library.h)
add_library(SFMLRender SHARED ${SOURCE_FILES})