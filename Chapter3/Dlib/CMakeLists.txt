cmake_minimum_required(VERSION 3.10)
project(examples)


set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -lstdc++fs")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


add_subdirectory(/home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib dlib_build)




add_executable(linalg_dlib grid_dlib.cpp)


target_link_libraries(linalg_dlib dlib::dlib)
target_link_libraries(linalg_dlib stdc++fs)


#Read the README.txt