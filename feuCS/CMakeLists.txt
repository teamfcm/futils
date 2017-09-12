cmake_minimum_required(VERSION 3.7)
project(feuCS)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp feucs.hpp)
add_executable(feuCS ${SOURCE_FILES})
target_compile_options(feuCS PUBLIC -W -Wall -Werror -Wextra)