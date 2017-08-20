cmake_minimum_required(VERSION 3.7)
project(fender)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES release/fender.h src/ncurses/CursesRender.cpp src/sfml/SFMLRender.cpp src/sfml/SFMLRender.hpp src/Manager.cpp src/IScene.cpp)
add_library(fender SHARED ${SOURCE_FILES})
set_target_properties(fender PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../release")
target_link_libraries(fender ncurses)
target_link_libraries(fender sfml-window sfml-audio sfml-graphics)
include_directories(release include)