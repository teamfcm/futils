cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(demo)

set(SOURCE_FILES
		src/main.cpp
		src/App/App.cpp)

add_executable(demo ${SOURCE_FILES})
target_compile_options(demo PUBLIC -W -Wall -Werror -Wextra)
include_directories(include utils)
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
find_library(FENDER fender HINTS ../release)
target_link_libraries(demo ${FENDER} dl)