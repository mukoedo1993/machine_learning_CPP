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
CMAKE_SOURCE_DIR = /home/zcw/machine_learning_CPP/Chapter5/dlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcw/machine_learning_CPP/Chapter5/dlib/build

# Include any dependencies generated for this target.
include CMakeFiles/dlib_anomaly.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dlib_anomaly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dlib_anomaly.dir/flags.make

CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.o: CMakeFiles/dlib_anomaly.dir/flags.make
CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.o: ../dlib_anomaly.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcw/machine_learning_CPP/Chapter5/dlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.o -c /home/zcw/machine_learning_CPP/Chapter5/dlib/dlib_anomaly.cc

CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcw/machine_learning_CPP/Chapter5/dlib/dlib_anomaly.cc > CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.i

CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcw/machine_learning_CPP/Chapter5/dlib/dlib_anomaly.cc -o CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.s

# Object files for target dlib_anomaly
dlib_anomaly_OBJECTS = \
"CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.o"

# External object files for target dlib_anomaly
dlib_anomaly_EXTERNAL_OBJECTS =

dlib_anomaly: CMakeFiles/dlib_anomaly.dir/dlib_anomaly.cc.o
dlib_anomaly: CMakeFiles/dlib_anomaly.dir/build.make
dlib_anomaly: dlib_build/libdlib.a
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libSM.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libICE.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libX11.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libXext.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libpng.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libz.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libjpeg.so
dlib_anomaly: /usr/lib/x86_64-linux-gnu/libopenblas.so
dlib_anomaly: CMakeFiles/dlib_anomaly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcw/machine_learning_CPP/Chapter5/dlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dlib_anomaly"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dlib_anomaly.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dlib_anomaly.dir/build: dlib_anomaly

.PHONY : CMakeFiles/dlib_anomaly.dir/build

CMakeFiles/dlib_anomaly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dlib_anomaly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dlib_anomaly.dir/clean

CMakeFiles/dlib_anomaly.dir/depend:
	cd /home/zcw/machine_learning_CPP/Chapter5/dlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcw/machine_learning_CPP/Chapter5/dlib /home/zcw/machine_learning_CPP/Chapter5/dlib /home/zcw/machine_learning_CPP/Chapter5/dlib/build /home/zcw/machine_learning_CPP/Chapter5/dlib/build /home/zcw/machine_learning_CPP/Chapter5/dlib/build/CMakeFiles/dlib_anomaly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dlib_anomaly.dir/depend
