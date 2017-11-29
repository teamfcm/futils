cmake_minimum_required(VERSION 3.7)
project(fender)
set(CMAKE_CXX_STANDARD 17)

file(GLOB UTILS
		"include/*.hpp"
		)

file(GLOB SYSTEMS
		"src/ecs/Systems/*.cpp")
file(GLOB ENTITIES
		"src/ecs/Entities/*.cpp")
file(GLOB COMPONENTS
		"src/ecs/Components/*.cpp")

set(SOURCE_FILES
		${UTILS}
		${ENTITIES}
		${COMPONENTS}
		${SYSTEMS}
		src/Manager.cpp
        src/IRender.cpp
		src/Fender.cpp
		src/renderers/sfml/SFMLRender.cpp
		src/renderers/ncurses/CursesRender.cpp
		)

if (UNIX)
	add_compile_options(-Wall -Wextra -Werror)
endif(UNIX)

add_library(fender SHARED ${SOURCE_FILES})
set_target_properties(fender PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../release")
target_link_libraries(fender ncurses)
target_link_libraries(fender sfml-window sfml-audio sfml-graphics)
include_directories(release include utils)