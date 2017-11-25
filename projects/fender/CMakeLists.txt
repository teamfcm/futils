cmake_minimum_required(VERSION 3.7)
project(fender)
set(CMAKE_CXX_STANDARD 17)

file(GLOB UTILS
		"include/*.hpp"
		)

set(SOURCE_FILES
		${UTILS}
        src/renderers/ncurses/CursesRender.cpp
		src/renderers/sfml/SFMLRender.cpp
		src/Manager.cpp
        src/IRender.cpp
        src/ecs/Entity.cpp
        src/ecs/Component.cpp
        src/ecs/System.cpp
        src/ecs/Components/Object2d.cpp)

if (UNIX)
	add_compile_options(-Wall -Wextra -Werror)
endif(UNIX)

add_library(fender SHARED ${SOURCE_FILES})
set_target_properties(fender PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../release")
target_link_libraries(fender ncurses)
target_link_libraries(fender sfml-window sfml-audio sfml-graphics)
include_directories(release include utils)