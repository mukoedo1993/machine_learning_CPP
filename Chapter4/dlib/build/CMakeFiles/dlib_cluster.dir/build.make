# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/zcw/machine_learning_CPP/Chapter4/dlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcw/machine_learning_CPP/Chapter4/dlib/build

# Include any dependencies generated for this target.
include CMakeFiles/dlib_cluster.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dlib_cluster.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dlib_cluster.dir/flags.make

CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.o: CMakeFiles/dlib_cluster.dir/flags.make
CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.o: ../dlib_cluster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcw/machine_learning_CPP/Chapter4/dlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.o -c /home/zcw/machine_learning_CPP/Chapter4/dlib/dlib_cluster.cpp

CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcw/machine_learning_CPP/Chapter4/dlib/dlib_cluster.cpp > CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.i

CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcw/machine_learning_CPP/Chapter4/dlib/dlib_cluster.cpp -o CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.s

# Object files for target dlib_cluster
dlib_cluster_OBJECTS = \
"CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.o"

# External object files for target dlib_cluster
dlib_cluster_EXTERNAL_OBJECTS =

dlib_cluster: CMakeFiles/dlib_cluster.dir/dlib_cluster.cpp.o
dlib_cluster: CMakeFiles/dlib_cluster.dir/build.make
dlib_cluster: dlib_build/libdlib.a
dlib_cluster: /usr/lib/x86_64-linux-gnu/libSM.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libICE.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libX11.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libXext.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libpng.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libz.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libjpeg.so
dlib_cluster: /usr/lib/x86_64-linux-gnu/libopenblas.so
dlib_cluster: CMakeFiles/dlib_cluster.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcw/machine_learning_CPP/Chapter4/dlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dlib_cluster"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dlib_cluster.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dlib_cluster.dir/build: dlib_cluster

.PHONY : CMakeFiles/dlib_cluster.dir/build

CMakeFiles/dlib_cluster.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dlib_cluster.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dlib_cluster.dir/clean

CMakeFiles/dlib_cluster.dir/depend:
	cd /home/zcw/machine_learning_CPP/Chapter4/dlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcw/machine_learning_CPP/Chapter4/dlib /home/zcw/machine_learning_CPP/Chapter4/dlib /home/zcw/machine_learning_CPP/Chapter4/dlib/build /home/zcw/machine_learning_CPP/Chapter4/dlib/build /home/zcw/machine_learning_CPP/Chapter4/dlib/build/CMakeFiles/dlib_cluster.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dlib_cluster.dir/depend
