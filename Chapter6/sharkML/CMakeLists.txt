

cmake_minimum_required(VERSION 3.10)
project(tst1)

find_package(Boost 1.71.0 COMPONENTS system filesystem serialization REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++17 -msse3 -fopenmp -lstdc++fs -fpermissive -lcblas -lpthread -lboost_serialization -lboost_system")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -lcblas -lboost_serialization -lboost_system")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -lcblas -lboost_serialization -lboost_system")


set(Boost_USE_MULTITHREADED ON)



include_directories($HOME/projects/opencv/build/include )

include_directories(/home/zcw/C++_MUKOEDO_LIB/Shark_clone/Shark/include)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

#cmake ..; cmake --build . --config Release

add_executable(tst1 tst1.cpp)

target_link_libraries(tst1 stdc++fs)
target_link_libraries(tst1 cblas)
target_link_libraries(tst1 /home/zcw/C++_MUKOEDO_LIB/Shark_clone/Shark/build/lib/libshark.a ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${OpenCV_LIBS})