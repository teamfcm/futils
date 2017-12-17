cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(demo)

function(find_static_library LIB_NAME OUT)
	if (WIN32 OR MSVC)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	elseif (UNIX)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	endif()
	find_library(
			FOUND_${LIB_NAME}_STATIC
			${LIB_NAME}
	)
	if (FOUND_${LIB_NAME}_STATIC)
		get_filename_component(ABS_FILE ${FOUND_${LIB_NAME}_STATIC} ABSOLUTE)
	else()
		message(SEND_ERROR "Unable to find library ${LIB_NAME}")
	endif()
	set(${OUT} ${ABS_FILE} PARENT_SCOPE)
endfunction()

set(SOURCE_FILES
		src/main.cpp
		src/App/App.cpp)

add_executable(demo ${SOURCE_FILES})
include_directories(include utils)
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
if (UNIX)
target_compile_options(demo PUBLIC -W -Wall -Werror -Wextra)
target_link_libraries(demo ${CMAKE_SOURCE_DIR}/libfender.a dl)
endif (UNIX)
if (WIN32)
find_library(FENDER fender HINTS ./lib)
target_link_libraries(demo ${FENDER})
endif (WIN32)
target_link_libraries(demo sfml-system sfml-window sfml-audio sfml-graphics)
target_link_libraries(demo -lstdc++fs)