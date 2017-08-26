cmake_minimum_required(VERSION 3.7)
project(demo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp include/DynamicLibrary.hpp include/futils.hpp include/Factory.cpp include/Factory.hpp include/ForwardScenes.hpp include/AllScenes.hpp Scenes/Splashscreen.hpp Scenes/Splashscreen.cpp include/Demo.cpp include/Demo.hpp)
add_executable(demo ${SOURCE_FILES})

set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
target_compile_options(demo PUBLIC -W -Wall -Werror -Wextra)
add_subdirectory(lib/fender)
include_directories(include Scenes/Headers)
TARGET_LINK_LIBRARIES(demo fender)
TARGET_LINK_LIBRARIES(demo dl)
