# CMake generated Testfile for 
# Source directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/flann
# Build directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/modules/flann
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_flann "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_test_flann" "--gtest_output=xml:opencv_test_flann.xml")
set_tests_properties(opencv_test_flann PROPERTIES  LABELS "Main;opencv_flann;Accuracy" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1075;ocv_add_accuracy_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/flann/CMakeLists.txt;2;ocv_define_module;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/flann/CMakeLists.txt;0;")
