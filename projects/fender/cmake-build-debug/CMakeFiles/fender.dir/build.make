# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arroganz/cpp/futils/projects/fender

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arroganz/cpp/futils/projects/fender/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fender.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fender.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fender.dir/flags.make

CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o: ../src/renderers/ncurses/CursesRender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/renderers/ncurses/CursesRender.cpp

CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/renderers/ncurses/CursesRender.cpp > CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.i

CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/renderers/ncurses/CursesRender.cpp -o CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.s

CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.requires

CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.provides: CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.provides

CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.provides.build: CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o


CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o: ../src/renderers/sfml/SFMLRender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/renderers/sfml/SFMLRender.cpp

CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/renderers/sfml/SFMLRender.cpp > CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.i

CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/renderers/sfml/SFMLRender.cpp -o CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.s

CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.requires

CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.provides: CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.provides

CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.provides.build: CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o


CMakeFiles/fender.dir/src/Manager.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Manager.cpp.o: ../src/Manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/fender.dir/src/Manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Manager.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Manager.cpp

CMakeFiles/fender.dir/src/Manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Manager.cpp > CMakeFiles/fender.dir/src/Manager.cpp.i

CMakeFiles/fender.dir/src/Manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Manager.cpp -o CMakeFiles/fender.dir/src/Manager.cpp.s

CMakeFiles/fender.dir/src/Manager.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Manager.cpp.o.requires

CMakeFiles/fender.dir/src/Manager.cpp.o.provides: CMakeFiles/fender.dir/src/Manager.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Manager.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Manager.cpp.o.provides

CMakeFiles/fender.dir/src/Manager.cpp.o.provides.build: CMakeFiles/fender.dir/src/Manager.cpp.o


CMakeFiles/fender.dir/src/IScene.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/IScene.cpp.o: ../src/IScene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/fender.dir/src/IScene.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/IScene.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/IScene.cpp

CMakeFiles/fender.dir/src/IScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/IScene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/IScene.cpp > CMakeFiles/fender.dir/src/IScene.cpp.i

CMakeFiles/fender.dir/src/IScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/IScene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/IScene.cpp -o CMakeFiles/fender.dir/src/IScene.cpp.s

CMakeFiles/fender.dir/src/IScene.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/IScene.cpp.o.requires

CMakeFiles/fender.dir/src/IScene.cpp.o.provides: CMakeFiles/fender.dir/src/IScene.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/IScene.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/IScene.cpp.o.provides

CMakeFiles/fender.dir/src/IScene.cpp.o.provides.build: CMakeFiles/fender.dir/src/IScene.cpp.o


CMakeFiles/fender.dir/src/IRender.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/IRender.cpp.o: ../src/IRender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/fender.dir/src/IRender.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/IRender.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/IRender.cpp

CMakeFiles/fender.dir/src/IRender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/IRender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/IRender.cpp > CMakeFiles/fender.dir/src/IRender.cpp.i

CMakeFiles/fender.dir/src/IRender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/IRender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/IRender.cpp -o CMakeFiles/fender.dir/src/IRender.cpp.s

CMakeFiles/fender.dir/src/IRender.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/IRender.cpp.o.requires

CMakeFiles/fender.dir/src/IRender.cpp.o.provides: CMakeFiles/fender.dir/src/IRender.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/IRender.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/IRender.cpp.o.provides

CMakeFiles/fender.dir/src/IRender.cpp.o.provides.build: CMakeFiles/fender.dir/src/IRender.cpp.o


CMakeFiles/fender.dir/src/ecs/Entity.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/ecs/Entity.cpp.o: ../src/ecs/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/fender.dir/src/ecs/Entity.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/ecs/Entity.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/ecs/Entity.cpp

CMakeFiles/fender.dir/src/ecs/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/ecs/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/ecs/Entity.cpp > CMakeFiles/fender.dir/src/ecs/Entity.cpp.i

CMakeFiles/fender.dir/src/ecs/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/ecs/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/ecs/Entity.cpp -o CMakeFiles/fender.dir/src/ecs/Entity.cpp.s

CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.requires

CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.provides: CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.provides

CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.provides.build: CMakeFiles/fender.dir/src/ecs/Entity.cpp.o


CMakeFiles/fender.dir/src/ecs/Component.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/ecs/Component.cpp.o: ../src/ecs/Component.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/fender.dir/src/ecs/Component.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/ecs/Component.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/ecs/Component.cpp

CMakeFiles/fender.dir/src/ecs/Component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/ecs/Component.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/ecs/Component.cpp > CMakeFiles/fender.dir/src/ecs/Component.cpp.i

CMakeFiles/fender.dir/src/ecs/Component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/ecs/Component.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/ecs/Component.cpp -o CMakeFiles/fender.dir/src/ecs/Component.cpp.s

CMakeFiles/fender.dir/src/ecs/Component.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/ecs/Component.cpp.o.requires

CMakeFiles/fender.dir/src/ecs/Component.cpp.o.provides: CMakeFiles/fender.dir/src/ecs/Component.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/ecs/Component.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/ecs/Component.cpp.o.provides

CMakeFiles/fender.dir/src/ecs/Component.cpp.o.provides.build: CMakeFiles/fender.dir/src/ecs/Component.cpp.o


CMakeFiles/fender.dir/src/ecs/System.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/ecs/System.cpp.o: ../src/ecs/System.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/fender.dir/src/ecs/System.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/ecs/System.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/ecs/System.cpp

CMakeFiles/fender.dir/src/ecs/System.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/ecs/System.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/ecs/System.cpp > CMakeFiles/fender.dir/src/ecs/System.cpp.i

CMakeFiles/fender.dir/src/ecs/System.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/ecs/System.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/ecs/System.cpp -o CMakeFiles/fender.dir/src/ecs/System.cpp.s

CMakeFiles/fender.dir/src/ecs/System.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/ecs/System.cpp.o.requires

CMakeFiles/fender.dir/src/ecs/System.cpp.o.provides: CMakeFiles/fender.dir/src/ecs/System.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/ecs/System.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/ecs/System.cpp.o.provides

CMakeFiles/fender.dir/src/ecs/System.cpp.o.provides.build: CMakeFiles/fender.dir/src/ecs/System.cpp.o


CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o: ../src/ecs/Components/Object2d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/ecs/Components/Object2d.cpp

CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/ecs/Components/Object2d.cpp > CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.i

CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/ecs/Components/Object2d.cpp -o CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.s

CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.requires

CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.provides: CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.provides

CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.provides.build: CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o


# Object files for target fender
fender_OBJECTS = \
"CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o" \
"CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o" \
"CMakeFiles/fender.dir/src/Manager.cpp.o" \
"CMakeFiles/fender.dir/src/IScene.cpp.o" \
"CMakeFiles/fender.dir/src/IRender.cpp.o" \
"CMakeFiles/fender.dir/src/ecs/Entity.cpp.o" \
"CMakeFiles/fender.dir/src/ecs/Component.cpp.o" \
"CMakeFiles/fender.dir/src/ecs/System.cpp.o" \
"CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o"

# External object files for target fender
fender_EXTERNAL_OBJECTS =

../release/libfender.so: CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/Manager.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/IScene.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/IRender.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/ecs/Entity.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/ecs/Component.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/ecs/System.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o
../release/libfender.so: CMakeFiles/fender.dir/build.make
../release/libfender.so: CMakeFiles/fender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX shared library ../release/libfender.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fender.dir/build: ../release/libfender.so

.PHONY : CMakeFiles/fender.dir/build

CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/renderers/ncurses/CursesRender.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/renderers/sfml/SFMLRender.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Manager.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/IScene.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/IRender.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/ecs/Entity.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/ecs/Component.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/ecs/System.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/ecs/Components/Object2d.cpp.o.requires

.PHONY : CMakeFiles/fender.dir/requires

CMakeFiles/fender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fender.dir/clean

CMakeFiles/fender.dir/depend:
	cd /home/arroganz/cpp/futils/projects/fender/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arroganz/cpp/futils/projects/fender /home/arroganz/cpp/futils/projects/fender /home/arroganz/cpp/futils/projects/fender/cmake-build-debug /home/arroganz/cpp/futils/projects/fender/cmake-build-debug /home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles/fender.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fender.dir/depend

