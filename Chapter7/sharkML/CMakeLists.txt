cmake_minimum_required(VERSION 3.10)
project(sharkml_classify)

set(SHARK_PATH "/home/zcw/C++_MUKOEDO_LIB/Shark_clone/Shark/build" CACHE PATH "path to SharkML install dir")

if(NOT SHARK_PATH)
  message(FATAL_ERROR "Missing SharkML install path, please specify SHARK_PATH")
else()
  message("SharkML path is ${SHARK_PATH}")
endif()

find_package(Boost 1.71.0 COMPONENTS system filesystem serialization REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED serialization)

set(CMAKE_CXX_FLAGS "-msse3 -fopenmp ")#-Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(${SHARK_PATH}/include)
link_directories(${SHARK_PATH}/lib)


set(SOURCES sharkml_classify.cc)

add_executable(sharkml_classify ${SOURCES})
target_link_libraries(sharkml_classify shark cblas ${Boost_LIBRARIES} stdc++fs )