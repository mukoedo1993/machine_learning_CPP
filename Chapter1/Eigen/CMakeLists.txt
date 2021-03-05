cmake_minimum_required(VERSION 3.0)
project(eigen_samples)

set(EIGEN_PATH "/C++_MUKOEDO_LIB/Eigen_clone/eigen/Eigen")
set(CACHE PATH "/C++_MUKOEDO_LIB/Eigen_clone/eigen/Eigen")


if(NOT EIGEN_PATH)
 message(FATAL_ERROR "Missing Eigen install path, please specify EIGEN_PATH")
else()
 message("Eigen path is ${EIGEN_PATH}")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -Wall -Wextra")
set(CAMKE_CXX_FLAGS_RELEASE "-03 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(${EIGEN_PATH})

add_executable(linalg_eigen "algorithm_eigen.cpp")
add_executable(linreg_eigen "algorithm_regres.cpp")