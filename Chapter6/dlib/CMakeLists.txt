cmake_minimum_required(VERSION 3.10)
project(example)


set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -lstdc++fs -fpermissive")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


add_subdirectory(/home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib dlib_build)




add_executable(dlib_dr1 dlib_dr1.cc)


target_link_libraries(dlib_dr1 dlib::dlib)
target_link_libraries(dlib_dr1 stdc++fs)