
cmake_minimum_required(VERSION 3.10)
project(shogun-samples)

set(SHOGUN_PATH "/home/zcw/anaconda3/pkgs/shogun-cpp-6.1.3-blas_openblash9eb233f_1002" CACHE PATH "/home/zcw/anaconda3/pkgs/shogun-cpp-6.1.3-blas_openblash9eb233f_1002")

if(NOT DEFINED SHOGUN_PATH)
  message(FATAL_ERROR "Missing Shogun install path, please specify SHOGUN_PATH")
else()
  message("Shogun path is ${SHOGUN_PATH}")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(HDF5 REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14 -msse3 -fopenmp -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
#/home/zcw/anaconda3/envs/shogun/include
include_directories(/home/zcw/anaconda3/envs/shogun/include)
link_directories(/home/zcw/anaconda3/envs/shogun/lib)

add_executable(linreg_shogun "shogun_test.cpp")
target_link_libraries(linreg_shogun shogun)
target_link_libraries(linreg_shogun ${HDF5_LIBRARIES} json-c ${PROTOBUF_LIBRARIES} cblas lapack)




#include_directories(/home/zcw/anaconda3/pkgs/shogun-cpp-6.1.3-blas_openblash9eb233f_1002/include)
#link_directories(/home/zcw/anaconda3/pkgs/shogun-cpp-6.1.3-blas_openblash9eb233f_1002/lib)

#cmake..; cmake --build . --config Release
