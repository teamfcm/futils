cmake_minimum_required(VERSION 3.9)
project(futils)

find_library(CRITERION criterion)

add_executable(futils tests/main.cpp)
target_link_libraries(futils ${CRITERION})