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
CMAKE_SOURCE_DIR = /home/zcw/machine_learning_CPP/Chapter1/sharkML

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcw/machine_learning_CPP/Chapter1/sharkML

# Include any dependencies generated for this target.
include CMakeFiles/linalg-shark.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linalg-shark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linalg-shark.dir/flags.make

CMakeFiles/linalg-shark.dir/linalg_shark.cc.o: CMakeFiles/linalg-shark.dir/flags.make
CMakeFiles/linalg-shark.dir/linalg_shark.cc.o: linalg_shark.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcw/machine_learning_CPP/Chapter1/sharkML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/linalg-shark.dir/linalg_shark.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/linalg-shark.dir/linalg_shark.cc.o -c /home/zcw/machine_learning_CPP/Chapter1/sharkML/linalg_shark.cc

CMakeFiles/linalg-shark.dir/linalg_shark.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/linalg-shark.dir/linalg_shark.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcw/machine_learning_CPP/Chapter1/sharkML/linalg_shark.cc > CMakeFiles/linalg-shark.dir/linalg_shark.cc.i

CMakeFiles/linalg-shark.dir/linalg_shark.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/linalg-shark.dir/linalg_shark.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcw/machine_learning_CPP/Chapter1/sharkML/linalg_shark.cc -o CMakeFiles/linalg-shark.dir/linalg_shark.cc.s

# Object files for target linalg-shark
linalg__shark_OBJECTS = \
"CMakeFiles/linalg-shark.dir/linalg_shark.cc.o"

# External object files for target linalg-shark
linalg__shark_EXTERNAL_OBJECTS =

linalg-shark: CMakeFiles/linalg-shark.dir/linalg_shark.cc.o
linalg-shark: CMakeFiles/linalg-shark.dir/build.make
linalg-shark: CMakeFiles/linalg-shark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcw/machine_learning_CPP/Chapter1/sharkML/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable linalg-shark"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linalg-shark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linalg-shark.dir/build: linalg-shark

.PHONY : CMakeFiles/linalg-shark.dir/build

CMakeFiles/linalg-shark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/linalg-shark.dir/cmake_clean.cmake
.PHONY : CMakeFiles/linalg-shark.dir/clean

CMakeFiles/linalg-shark.dir/depend:
	cd /home/zcw/machine_learning_CPP/Chapter1/sharkML && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcw/machine_learning_CPP/Chapter1/sharkML /home/zcw/machine_learning_CPP/Chapter1/sharkML /home/zcw/machine_learning_CPP/Chapter1/sharkML /home/zcw/machine_learning_CPP/Chapter1/sharkML /home/zcw/machine_learning_CPP/Chapter1/sharkML/CMakeFiles/linalg-shark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/linalg-shark.dir/depend

