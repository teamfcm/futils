cmake_minimum_required(VERSION 3.7)
project(demo)

if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
	get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} PATH)
	set (COMMON_DIR ${PARENT_DIR})
	message("Changing common dir to ${COMMON_DIR}")
else()
	set(COMMON_DIR ${CMAKE_SOURCE_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)
include_directories(${COMMON_DIR})

set(SOURCE_FILES main.cpp 
        ${COMMON_DIR}/futils.hpp
		include/Factory.cpp
		include/Factory.hpp
		include/ForwardScenes.hpp
		include/AllScenes.hpp
		Scenes/Splashscreen.hpp
		Scenes/Splashscreen.cpp
		include/Demo.cpp
		include/Demo.hpp
		Scenes/Menu.cpp
		Scenes/Menu.hpp)
add_executable(demo ${SOURCE_FILES})

set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
target_compile_options(demo PUBLIC -W -Wall -Werror -Wextra)
include_directories(include Scenes/Headers)
find_library(FENDER fender HINTS ./lib)
target_link_libraries(demo ${FENDER} dl)