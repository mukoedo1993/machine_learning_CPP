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
CMAKE_SOURCE_DIR = /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build

# Include any dependencies generated for this target.
include CMakeFiles/libjpeg_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libjpeg_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libjpeg_test.dir/flags.make

CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.o: CMakeFiles/libjpeg_test.dir/flags.make
CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.o: /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg/libjpeg_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.o -c /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg/libjpeg_test.cpp

CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg/libjpeg_test.cpp > CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.i

CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg/libjpeg_test.cpp -o CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.s

# Object files for target libjpeg_test
libjpeg_test_OBJECTS = \
"CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.o"

# External object files for target libjpeg_test
libjpeg_test_EXTERNAL_OBJECTS =

libjpeg_test: CMakeFiles/libjpeg_test.dir/libjpeg_test.cpp.o
libjpeg_test: CMakeFiles/libjpeg_test.dir/build.make
libjpeg_test: /usr/lib/x86_64-linux-gnu/libjpeg.so
libjpeg_test: CMakeFiles/libjpeg_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable libjpeg_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libjpeg_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libjpeg_test.dir/build: libjpeg_test

.PHONY : CMakeFiles/libjpeg_test.dir/build

CMakeFiles/libjpeg_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libjpeg_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libjpeg_test.dir/clean

CMakeFiles/libjpeg_test.dir/depend:
	cd /home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg /home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib/cmake_utils/test_for_libjpeg /home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build /home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build /home/zcw/machine_learning_CPP/Chapter7/dlib/build/dlib_build/test_for_libjpeg_build/CMakeFiles/libjpeg_test.dir/DependInfo.cmake
.PHONY : CMakeFiles/libjpeg_test.dir/depend

