cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(demo)

set(SOURCE_FILES
		main.cpp
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
target_compile_options(demo PUBLIC -W -Wall -Werror -Wextra)
include_directories(include utils Scenes/Headers)
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
find_library(FENDER fender HINTS ../release)
target_link_libraries(demo ${FENDER} dl)