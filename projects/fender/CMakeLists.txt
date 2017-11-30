cmake_minimum_required(VERSION 3.7)
project(fender)
set(CMAKE_CXX_STANDARD 17)

file(GLOB UTILS
		"include/*.hpp"
		)

file(GLOB SYSTEMS
		"src/engine/Systems/*.cpp")
file(GLOB ENTITIES
		"src/engine/Entities/*.cpp")
file(GLOB COMPONENTS
		"src/engine/Components/*.cpp")
file(GLOB SFML
		"src/renderers/sfml/*.*pp")
file(GLOB CURSES
		"src/renderers/ncurses/*.*pp")
file(GLOB SRC
		"src/*.cpp")

set(SOURCE_FILES
		${UTILS}
		${ENTITIES}
		${COMPONENTS}
		${SYSTEMS}
		${SFML}
		${CURSES}
		${SRC}
		)

if (UNIX)
	add_compile_options(-Wall -Wextra -Werror)
endif(UNIX)

add_library(fender SHARED ${SOURCE_FILES})
set_target_properties(fender PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../release")
target_link_libraries(fender ncurses)
target_link_libraries(fender sfml-window sfml-audio sfml-graphics)
include_directories(release include utils)