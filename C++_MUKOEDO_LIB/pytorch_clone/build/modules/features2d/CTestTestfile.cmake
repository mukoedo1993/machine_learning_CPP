# CMake generated Testfile for 
# Source directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d
# Build directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/modules/features2d
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_features2d "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_test_features2d" "--gtest_output=xml:opencv_test_features2d.xml")
set_tests_properties(opencv_test_features2d PROPERTIES  LABELS "Main;opencv_features2d;Accuracy" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1075;ocv_add_accuracy_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d/CMakeLists.txt;9;ocv_define_module;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d/CMakeLists.txt;0;")
add_test(opencv_perf_features2d "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_perf_features2d" "--gtest_output=xml:opencv_perf_features2d.xml")
set_tests_properties(opencv_perf_features2d PROPERTIES  LABELS "Main;opencv_features2d;Performance" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/performance" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1213;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1076;ocv_add_perf_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d/CMakeLists.txt;9;ocv_define_module;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d/CMakeLists.txt;0;")
add_test(opencv_sanity_features2d "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_perf_features2d" "--gtest_output=xml:opencv_perf_features2d.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_features2d PROPERTIES  LABELS "Main;opencv_features2d;Sanity" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/sanity" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1214;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1076;ocv_add_perf_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d/CMakeLists.txt;9;ocv_define_module;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/features2d/CMakeLists.txt;0;")
