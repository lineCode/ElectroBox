# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/lucian/.clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lucian/.clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /var/www/canvas-native

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /var/www/canvas-native/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/canvas-native.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/canvas-native.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/canvas-native.dir/flags.make

CMakeFiles/canvas-native.dir/src/main.cpp.o: CMakeFiles/canvas-native.dir/flags.make
CMakeFiles/canvas-native.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/www/canvas-native/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/canvas-native.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/canvas-native.dir/src/main.cpp.o -c /var/www/canvas-native/src/main.cpp

CMakeFiles/canvas-native.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/canvas-native.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /var/www/canvas-native/src/main.cpp > CMakeFiles/canvas-native.dir/src/main.cpp.i

CMakeFiles/canvas-native.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/canvas-native.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /var/www/canvas-native/src/main.cpp -o CMakeFiles/canvas-native.dir/src/main.cpp.s

CMakeFiles/canvas-native.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/canvas-native.dir/src/main.cpp.o.requires

CMakeFiles/canvas-native.dir/src/main.cpp.o.provides: CMakeFiles/canvas-native.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/canvas-native.dir/build.make CMakeFiles/canvas-native.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/canvas-native.dir/src/main.cpp.o.provides

CMakeFiles/canvas-native.dir/src/main.cpp.o.provides.build: CMakeFiles/canvas-native.dir/src/main.cpp.o


# Object files for target canvas-native
canvas__native_OBJECTS = \
"CMakeFiles/canvas-native.dir/src/main.cpp.o"

# External object files for target canvas-native
canvas__native_EXTERNAL_OBJECTS =

canvas-native: CMakeFiles/canvas-native.dir/src/main.cpp.o
canvas-native: CMakeFiles/canvas-native.dir/build.make
canvas-native: ../libs/libv8_base.a
canvas-native: ../libs/libv8_libbase.a
canvas-native: ../libs/libv8_libplatform.a
canvas-native: CMakeFiles/canvas-native.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/var/www/canvas-native/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable canvas-native"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/canvas-native.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/canvas-native.dir/build: canvas-native

.PHONY : CMakeFiles/canvas-native.dir/build

CMakeFiles/canvas-native.dir/requires: CMakeFiles/canvas-native.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/canvas-native.dir/requires

CMakeFiles/canvas-native.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/canvas-native.dir/cmake_clean.cmake
.PHONY : CMakeFiles/canvas-native.dir/clean

CMakeFiles/canvas-native.dir/depend:
	cd /var/www/canvas-native/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /var/www/canvas-native /var/www/canvas-native /var/www/canvas-native/cmake-build-debug /var/www/canvas-native/cmake-build-debug /var/www/canvas-native/cmake-build-debug/CMakeFiles/canvas-native.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/canvas-native.dir/depend
