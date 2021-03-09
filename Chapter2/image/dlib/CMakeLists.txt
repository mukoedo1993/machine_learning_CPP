cmake_minimum_required(VERSION 3.10)
project(examples)

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-O3 -std=c++17 -msse3 -fopenmp -lstdc++fs")



add_subdirectory(/home/zcw/C++_MUKOEDO_LIB/Dlib_clone/dlib-19.21/dlib dlib_build)




add_executable(linalg_dlib img_dlib.cpp)


target_link_libraries(linalg_dlib dlib)
target_link_libraries(linalg_dlib stdc++fs)