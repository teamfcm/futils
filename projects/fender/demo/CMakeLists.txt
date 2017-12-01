cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(demo)

set(SOURCE_FILES
		src/main.cpp
		src/App/App.cpp)

add_executable(demo ${SOURCE_FILES})
include_directories(include utils)
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
if (UNIX)
target_compile_options(demo PUBLIC -W -Wall -Werror -Wextra)
find_library(FENDER fender HINTS ../release)
target_link_libraries(demo ${FENDER} dl)
endif (UNIX)
if (WIN32)
find_library(FENDER fender HINTS ./lib)
target_link_libraries(demo ${FENDER})
endif (WIN32)
