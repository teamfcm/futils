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
CMAKE_SOURCE_DIR = /home/arroganz/cpp/futils/projects/fender/demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/main.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/main.cpp.o -c /home/arroganz/cpp/futils/projects/fender/demo/main.cpp

CMakeFiles/demo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/demo/main.cpp > CMakeFiles/demo.dir/main.cpp.i

CMakeFiles/demo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/demo/main.cpp -o CMakeFiles/demo.dir/main.cpp.s

CMakeFiles/demo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/demo.dir/main.cpp.o.requires

CMakeFiles/demo.dir/main.cpp.o.provides: CMakeFiles/demo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo.dir/build.make CMakeFiles/demo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/demo.dir/main.cpp.o.provides

CMakeFiles/demo.dir/main.cpp.o.provides.build: CMakeFiles/demo.dir/main.cpp.o


CMakeFiles/demo.dir/include/Factory.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/include/Factory.cpp.o: ../include/Factory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/demo.dir/include/Factory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/include/Factory.cpp.o -c /home/arroganz/cpp/futils/projects/fender/demo/include/Factory.cpp

CMakeFiles/demo.dir/include/Factory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/include/Factory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/demo/include/Factory.cpp > CMakeFiles/demo.dir/include/Factory.cpp.i

CMakeFiles/demo.dir/include/Factory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/include/Factory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/demo/include/Factory.cpp -o CMakeFiles/demo.dir/include/Factory.cpp.s

CMakeFiles/demo.dir/include/Factory.cpp.o.requires:

.PHONY : CMakeFiles/demo.dir/include/Factory.cpp.o.requires

CMakeFiles/demo.dir/include/Factory.cpp.o.provides: CMakeFiles/demo.dir/include/Factory.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo.dir/build.make CMakeFiles/demo.dir/include/Factory.cpp.o.provides.build
.PHONY : CMakeFiles/demo.dir/include/Factory.cpp.o.provides

CMakeFiles/demo.dir/include/Factory.cpp.o.provides.build: CMakeFiles/demo.dir/include/Factory.cpp.o


CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o: ../Scenes/Splashscreen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o -c /home/arroganz/cpp/futils/projects/fender/demo/Scenes/Splashscreen.cpp

CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/demo/Scenes/Splashscreen.cpp > CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.i

CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/demo/Scenes/Splashscreen.cpp -o CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.s

CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.requires:

.PHONY : CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.requires

CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.provides: CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo.dir/build.make CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.provides.build
.PHONY : CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.provides

CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.provides.build: CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o


CMakeFiles/demo.dir/include/Demo.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/include/Demo.cpp.o: ../include/Demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/demo.dir/include/Demo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/include/Demo.cpp.o -c /home/arroganz/cpp/futils/projects/fender/demo/include/Demo.cpp

CMakeFiles/demo.dir/include/Demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/include/Demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/demo/include/Demo.cpp > CMakeFiles/demo.dir/include/Demo.cpp.i

CMakeFiles/demo.dir/include/Demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/include/Demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/demo/include/Demo.cpp -o CMakeFiles/demo.dir/include/Demo.cpp.s

CMakeFiles/demo.dir/include/Demo.cpp.o.requires:

.PHONY : CMakeFiles/demo.dir/include/Demo.cpp.o.requires

CMakeFiles/demo.dir/include/Demo.cpp.o.provides: CMakeFiles/demo.dir/include/Demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo.dir/build.make CMakeFiles/demo.dir/include/Demo.cpp.o.provides.build
.PHONY : CMakeFiles/demo.dir/include/Demo.cpp.o.provides

CMakeFiles/demo.dir/include/Demo.cpp.o.provides.build: CMakeFiles/demo.dir/include/Demo.cpp.o


CMakeFiles/demo.dir/Scenes/Menu.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/Scenes/Menu.cpp.o: ../Scenes/Menu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/demo.dir/Scenes/Menu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/Scenes/Menu.cpp.o -c /home/arroganz/cpp/futils/projects/fender/demo/Scenes/Menu.cpp

CMakeFiles/demo.dir/Scenes/Menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/Scenes/Menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/demo/Scenes/Menu.cpp > CMakeFiles/demo.dir/Scenes/Menu.cpp.i

CMakeFiles/demo.dir/Scenes/Menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/Scenes/Menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/demo/Scenes/Menu.cpp -o CMakeFiles/demo.dir/Scenes/Menu.cpp.s

CMakeFiles/demo.dir/Scenes/Menu.cpp.o.requires:

.PHONY : CMakeFiles/demo.dir/Scenes/Menu.cpp.o.requires

CMakeFiles/demo.dir/Scenes/Menu.cpp.o.provides: CMakeFiles/demo.dir/Scenes/Menu.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo.dir/build.make CMakeFiles/demo.dir/Scenes/Menu.cpp.o.provides.build
.PHONY : CMakeFiles/demo.dir/Scenes/Menu.cpp.o.provides

CMakeFiles/demo.dir/Scenes/Menu.cpp.o.provides.build: CMakeFiles/demo.dir/Scenes/Menu.cpp.o


# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/main.cpp.o" \
"CMakeFiles/demo.dir/include/Factory.cpp.o" \
"CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o" \
"CMakeFiles/demo.dir/include/Demo.cpp.o" \
"CMakeFiles/demo.dir/Scenes/Menu.cpp.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

../demo: CMakeFiles/demo.dir/main.cpp.o
../demo: CMakeFiles/demo.dir/include/Factory.cpp.o
../demo: CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o
../demo: CMakeFiles/demo.dir/include/Demo.cpp.o
../demo: CMakeFiles/demo.dir/Scenes/Menu.cpp.o
../demo: CMakeFiles/demo.dir/build.make
../demo: /home/arroganz/cpp/futils/projects/fender/release/libfender.so
../demo: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: ../demo

.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/requires: CMakeFiles/demo.dir/main.cpp.o.requires
CMakeFiles/demo.dir/requires: CMakeFiles/demo.dir/include/Factory.cpp.o.requires
CMakeFiles/demo.dir/requires: CMakeFiles/demo.dir/Scenes/Splashscreen.cpp.o.requires
CMakeFiles/demo.dir/requires: CMakeFiles/demo.dir/include/Demo.cpp.o.requires
CMakeFiles/demo.dir/requires: CMakeFiles/demo.dir/Scenes/Menu.cpp.o.requires

.PHONY : CMakeFiles/demo.dir/requires

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	cd /home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arroganz/cpp/futils/projects/fender/demo /home/arroganz/cpp/futils/projects/fender/demo /home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug /home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug /home/arroganz/cpp/futils/projects/fender/demo/cmake-build-debug/CMakeFiles/demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo.dir/depend

