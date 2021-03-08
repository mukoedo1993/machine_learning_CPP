cmake_minimum_required(VERSION 3.0)
project(json_sample)

#According to the document, both rapidjson lib. and Eigen lib. are 

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra -lstdc++fs")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


set(SOURCES ../json.cc
            ../review.h
            ../paper.h
            ../reviewsreader.h
            ../reviewsreader.cpp)




add_executable(json_sample ${SOURCES})

#I must do that, otherwise, 
target_link_libraries(json_sample stdc++fs)