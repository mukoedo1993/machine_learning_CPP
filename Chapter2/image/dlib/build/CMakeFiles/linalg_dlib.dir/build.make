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
CMAKE_SOURCE_DIR = /home/zcw/machine_learning_CPP/Chapter2/image/dlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcw/machine_learning_CPP/Chapter2/image/dlib/build

# Include any dependencies generated for this target.
include CMakeFiles/linalg_dlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linalg_dlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linalg_dlib.dir/flags.make

CMakeFiles/linalg_dlib.dir/img_dlib.cpp.o: CMakeFiles/linalg_dlib.dir/flags.make
CMakeFiles/linalg_dlib.dir/img_dlib.cpp.o: ../img_dlib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcw/machine_learning_CPP/Chapter2/image/dlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/linalg_dlib.dir/img_dlib.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/linalg_dlib.dir/img_dlib.cpp.o -c /home/zcw/machine_learning_CPP/Chapter2/image/dlib/img_dlib.cpp

CMakeFiles/linalg_dlib.dir/img_dlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/linalg_dlib.dir/img_dlib.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcw/machine_learning_CPP/Chapter2/image/dlib/img_dlib.cpp > CMakeFiles/linalg_dlib.dir/img_dlib.cpp.i

CMakeFiles/linalg_dlib.dir/img_dlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/linalg_dlib.dir/img_dlib.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcw/machine_learning_CPP/Chapter2/image/dlib/img_dlib.cpp -o CMakeFiles/linalg_dlib.dir/img_dlib.cpp.s

# Object files for target linalg_dlib
linalg_dlib_OBJECTS = \
"CMakeFiles/linalg_dlib.dir/img_dlib.cpp.o"

# External object files for target linalg_dlib
linalg_dlib_EXTERNAL_OBJECTS =

linalg_dlib: CMakeFiles/linalg_dlib.dir/img_dlib.cpp.o
linalg_dlib: CMakeFiles/linalg_dlib.dir/build.make
linalg_dlib: dlib_build/libdlib.a
linalg_dlib: /usr/lib/x86_64-linux-gnu/libSM.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libICE.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libX11.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libXext.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libpng.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libz.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libjpeg.so
linalg_dlib: /usr/lib/x86_64-linux-gnu/libopenblas.so
linalg_dlib: CMakeFiles/linalg_dlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcw/machine_learning_CPP/Chapter2/image/dlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable linalg_dlib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linalg_dlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linalg_dlib.dir/build: linalg_dlib

.PHONY : CMakeFiles/linalg_dlib.dir/build

CMakeFiles/linalg_dlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/linalg_dlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/linalg_dlib.dir/clean

CMakeFiles/linalg_dlib.dir/depend:
	cd /home/zcw/machine_learning_CPP/Chapter2/image/dlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcw/machine_learning_CPP/Chapter2/image/dlib /home/zcw/machine_learning_CPP/Chapter2/image/dlib /home/zcw/machine_learning_CPP/Chapter2/image/dlib/build /home/zcw/machine_learning_CPP/Chapter2/image/dlib/build /home/zcw/machine_learning_CPP/Chapter2/image/dlib/build/CMakeFiles/linalg_dlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/linalg_dlib.dir/depend

