cmake_minimum_required(VERSION 3.7)
project(fender)
set(CMAKE_CXX_STANDARD 17)

file(GLOB INCLUDE
		"include/*.hpp"
		)
file(GLOB UTILS
		"utils/*.hpp")
file(GLOB SYSTEMS
		"src/engine/Systems/*.cpp")
file(GLOB ENTITIES
		"src/engine/Entities/*.cpp")
file(GLOB COMPONENTS
		"src/engine/Components/*.cpp")
file(GLOB SRC
		"src/*.cpp")


set(SOURCE_FILES
		${INCLUDE}
		${UTILS}
		${ENTITIES}
		${COMPONENTS}
		${SYSTEMS}
		${SRC}
		)

if (UNIX)
	add_compile_options(-Wall -Wextra -Werror)
endif(UNIX)

add_executable(fender ${SOURCE_FILES})
set_target_properties(fender PROPERTIES BINARY_OUTPUT_DIRECTORY "../release")
#if (UNIX)
#	target_link_libraries(fender ncurses)
#endif (UNIX)
#target_link_libraries(fender sfml-window sfml-audio sfml-graphics)
#target_link_libraries(fender -lstdc++fs)
include_directories(release include utils)