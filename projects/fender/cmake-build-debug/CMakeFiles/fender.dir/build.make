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

CMakeFiles/fender.dir/src/Entities/Input.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Entities/Input.cpp.o: ../src/Entities/Input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fender.dir/src/Entities/Input.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Entities/Input.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Entities/Input.cpp

CMakeFiles/fender.dir/src/Entities/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Entities/Input.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Entities/Input.cpp > CMakeFiles/fender.dir/src/Entities/Input.cpp.i

CMakeFiles/fender.dir/src/Entities/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Entities/Input.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Entities/Input.cpp -o CMakeFiles/fender.dir/src/Entities/Input.cpp.s

CMakeFiles/fender.dir/src/Entities/Input.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Entities/Input.cpp.o.requires

CMakeFiles/fender.dir/src/Entities/Input.cpp.o.provides: CMakeFiles/fender.dir/src/Entities/Input.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Entities/Input.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Entities/Input.cpp.o.provides

CMakeFiles/fender.dir/src/Entities/Input.cpp.o.provides.build: CMakeFiles/fender.dir/src/Entities/Input.cpp.o


CMakeFiles/fender.dir/src/Entities/Window.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Entities/Window.cpp.o: ../src/Entities/Window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fender.dir/src/Entities/Window.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Entities/Window.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Entities/Window.cpp

CMakeFiles/fender.dir/src/Entities/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Entities/Window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Entities/Window.cpp > CMakeFiles/fender.dir/src/Entities/Window.cpp.i

CMakeFiles/fender.dir/src/Entities/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Entities/Window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Entities/Window.cpp -o CMakeFiles/fender.dir/src/Entities/Window.cpp.s

CMakeFiles/fender.dir/src/Entities/Window.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Entities/Window.cpp.o.requires

CMakeFiles/fender.dir/src/Entities/Window.cpp.o.provides: CMakeFiles/fender.dir/src/Entities/Window.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Entities/Window.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Entities/Window.cpp.o.provides

CMakeFiles/fender.dir/src/Entities/Window.cpp.o.provides.build: CMakeFiles/fender.dir/src/Entities/Window.cpp.o


CMakeFiles/fender.dir/src/Components/Input.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Components/Input.cpp.o: ../src/Components/Input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/fender.dir/src/Components/Input.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Components/Input.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Components/Input.cpp

CMakeFiles/fender.dir/src/Components/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Components/Input.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Components/Input.cpp > CMakeFiles/fender.dir/src/Components/Input.cpp.i

CMakeFiles/fender.dir/src/Components/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Components/Input.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Components/Input.cpp -o CMakeFiles/fender.dir/src/Components/Input.cpp.s

CMakeFiles/fender.dir/src/Components/Input.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Components/Input.cpp.o.requires

CMakeFiles/fender.dir/src/Components/Input.cpp.o.provides: CMakeFiles/fender.dir/src/Components/Input.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Components/Input.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Components/Input.cpp.o.provides

CMakeFiles/fender.dir/src/Components/Input.cpp.o.provides.build: CMakeFiles/fender.dir/src/Components/Input.cpp.o


CMakeFiles/fender.dir/src/Components/Window.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Components/Window.cpp.o: ../src/Components/Window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/fender.dir/src/Components/Window.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Components/Window.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Components/Window.cpp

CMakeFiles/fender.dir/src/Components/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Components/Window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Components/Window.cpp > CMakeFiles/fender.dir/src/Components/Window.cpp.i

CMakeFiles/fender.dir/src/Components/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Components/Window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Components/Window.cpp -o CMakeFiles/fender.dir/src/Components/Window.cpp.s

CMakeFiles/fender.dir/src/Components/Window.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Components/Window.cpp.o.requires

CMakeFiles/fender.dir/src/Components/Window.cpp.o.provides: CMakeFiles/fender.dir/src/Components/Window.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Components/Window.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Components/Window.cpp.o.provides

CMakeFiles/fender.dir/src/Components/Window.cpp.o.provides.build: CMakeFiles/fender.dir/src/Components/Window.cpp.o


CMakeFiles/fender.dir/src/Systems/Log.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Systems/Log.cpp.o: ../src/Systems/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/fender.dir/src/Systems/Log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Systems/Log.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Systems/Log.cpp

CMakeFiles/fender.dir/src/Systems/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Systems/Log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Systems/Log.cpp > CMakeFiles/fender.dir/src/Systems/Log.cpp.i

CMakeFiles/fender.dir/src/Systems/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Systems/Log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Systems/Log.cpp -o CMakeFiles/fender.dir/src/Systems/Log.cpp.s

CMakeFiles/fender.dir/src/Systems/Log.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Systems/Log.cpp.o.requires

CMakeFiles/fender.dir/src/Systems/Log.cpp.o.provides: CMakeFiles/fender.dir/src/Systems/Log.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Systems/Log.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Systems/Log.cpp.o.provides

CMakeFiles/fender.dir/src/Systems/Log.cpp.o.provides.build: CMakeFiles/fender.dir/src/Systems/Log.cpp.o


CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o: ../src/Systems/SFML/Input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/Input.cpp

CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/Input.cpp > CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.i

CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/Input.cpp -o CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.s

CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.requires

CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.provides: CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.provides

CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.provides.build: CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o


CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o: ../src/Systems/SFML/SFMLRenderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/SFMLRenderer.cpp

CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/SFMLRenderer.cpp > CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.i

CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/SFMLRenderer.cpp -o CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.s

CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.requires

CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.provides: CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.provides

CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.provides.build: CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o


CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o: ../src/Systems/SFML/Window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/Window.cpp

CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/Window.cpp > CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.i

CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Systems/SFML/Window.cpp -o CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.s

CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.requires

CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.provides: CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.provides

CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.provides.build: CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o


CMakeFiles/fender.dir/src/Fender.cpp.o: CMakeFiles/fender.dir/flags.make
CMakeFiles/fender.dir/src/Fender.cpp.o: ../src/Fender.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/fender.dir/src/Fender.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fender.dir/src/Fender.cpp.o -c /home/arroganz/cpp/futils/projects/fender/src/Fender.cpp

CMakeFiles/fender.dir/src/Fender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fender.dir/src/Fender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arroganz/cpp/futils/projects/fender/src/Fender.cpp > CMakeFiles/fender.dir/src/Fender.cpp.i

CMakeFiles/fender.dir/src/Fender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fender.dir/src/Fender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arroganz/cpp/futils/projects/fender/src/Fender.cpp -o CMakeFiles/fender.dir/src/Fender.cpp.s

CMakeFiles/fender.dir/src/Fender.cpp.o.requires:

.PHONY : CMakeFiles/fender.dir/src/Fender.cpp.o.requires

CMakeFiles/fender.dir/src/Fender.cpp.o.provides: CMakeFiles/fender.dir/src/Fender.cpp.o.requires
	$(MAKE) -f CMakeFiles/fender.dir/build.make CMakeFiles/fender.dir/src/Fender.cpp.o.provides.build
.PHONY : CMakeFiles/fender.dir/src/Fender.cpp.o.provides

CMakeFiles/fender.dir/src/Fender.cpp.o.provides.build: CMakeFiles/fender.dir/src/Fender.cpp.o


# Object files for target fender
fender_OBJECTS = \
"CMakeFiles/fender.dir/src/Entities/Input.cpp.o" \
"CMakeFiles/fender.dir/src/Entities/Window.cpp.o" \
"CMakeFiles/fender.dir/src/Components/Input.cpp.o" \
"CMakeFiles/fender.dir/src/Components/Window.cpp.o" \
"CMakeFiles/fender.dir/src/Systems/Log.cpp.o" \
"CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o" \
"CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o" \
"CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o" \
"CMakeFiles/fender.dir/src/Fender.cpp.o"

# External object files for target fender
fender_EXTERNAL_OBJECTS =

libfender.a: CMakeFiles/fender.dir/src/Entities/Input.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Entities/Window.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Components/Input.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Components/Window.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Systems/Log.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o
libfender.a: CMakeFiles/fender.dir/src/Fender.cpp.o
libfender.a: CMakeFiles/fender.dir/build.make
libfender.a: CMakeFiles/fender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libfender.a"
	$(CMAKE_COMMAND) -P CMakeFiles/fender.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fender.dir/build: libfender.a

.PHONY : CMakeFiles/fender.dir/build

CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Entities/Input.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Entities/Window.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Components/Input.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Components/Window.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Systems/Log.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Systems/SFML/Input.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Systems/SFML/SFMLRenderer.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Systems/SFML/Window.cpp.o.requires
CMakeFiles/fender.dir/requires: CMakeFiles/fender.dir/src/Fender.cpp.o.requires

.PHONY : CMakeFiles/fender.dir/requires

CMakeFiles/fender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fender.dir/clean

CMakeFiles/fender.dir/depend:
	cd /home/arroganz/cpp/futils/projects/fender/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arroganz/cpp/futils/projects/fender /home/arroganz/cpp/futils/projects/fender /home/arroganz/cpp/futils/projects/fender/cmake-build-debug /home/arroganz/cpp/futils/projects/fender/cmake-build-debug /home/arroganz/cpp/futils/projects/fender/cmake-build-debug/CMakeFiles/fender.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fender.dir/depend

