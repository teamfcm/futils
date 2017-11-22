cmake_minimum_required(VERSION 3.7)
project(fender)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
	get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} PATH)
	set (COMMON_DIR ${PARENT_DIR})
	message("Changing common dir to ${COMMON_DIR}")
else()
	set(COMMON_DIR ${CMAKE_SOURCE_DIR})
endif()
include_directories(${COMMON_DIR})

set(SOURCE_FILES
		${COMMON_DIR}/log.hpp
		${COMMON_DIR}/ini.hpp
        release/fender.hpp
        src/ncurses/CursesRender.cpp
		src/sfml/SFMLRender.cpp
		src/sfml/SFMLRender.hpp
		src/Manager.cpp
		src/IScene.cpp
		src/IRender.cpp
		src/ECS/Entity.cpp
		src/ECS/Component.cpp
		src/ECS/System.cpp
		src/ECS/Components/Object2d.cpp)

## TODO: ADD SOME MOTHERFUCKING COMPILE FLAGS MAYBE ?
## TODO: CrossPlatform may be important...
add_compile_options(-Wall -Wextra -Werror)
add_library(fender SHARED ${SOURCE_FILES})
set_target_properties(fender PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../release")
target_link_libraries(fender ncurses)
target_link_libraries(fender sfml-window sfml-audio sfml-graphics)
include_directories(release include)