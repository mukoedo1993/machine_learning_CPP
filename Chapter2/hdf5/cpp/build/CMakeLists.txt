cmake_minimum_required(VERSION 3.0)
project(hdf5_sample)

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra -lstdc++fs")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(SOURCES 
            ../hdf5.cpp
            ../../../json/cpp/paper.h
            ../../../json/cpp/review.h
            ../../../json/cpp/reviewsreader.h
            ../../../json/cpp/reviewsreader.cpp)

add_executable(json_sample ${SOURCES})

target_link_libraries(json_sample stdc++fs)
target_link_libraries(json_sample /home/zcw/anaconda3/pkgs/hdf5-1.10.4-hb1b8bf9_0/lib/libhdf5.so)
