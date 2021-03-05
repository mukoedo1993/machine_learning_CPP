# CMake generated Testfile for 
# Source directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn
# Build directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/modules/dnn
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_dnn "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_test_dnn" "--gtest_output=xml:opencv_test_dnn.xml")
set_tests_properties(opencv_test_dnn PROPERTIES  LABELS "Main;opencv_dnn;Accuracy" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn/CMakeLists.txt;168;ocv_add_accuracy_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn/CMakeLists.txt;0;")
add_test(opencv_perf_dnn "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_perf_dnn" "--gtest_output=xml:opencv_perf_dnn.xml")
set_tests_properties(opencv_perf_dnn PROPERTIES  LABELS "Main;opencv_dnn;Performance" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/performance" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1213;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn/CMakeLists.txt;173;ocv_add_perf_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn/CMakeLists.txt;0;")
add_test(opencv_sanity_dnn "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_perf_dnn" "--gtest_output=xml:opencv_perf_dnn.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_dnn PROPERTIES  LABELS "Main;opencv_dnn;Sanity" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/sanity" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1214;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn/CMakeLists.txt;173;ocv_add_perf_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/dnn/CMakeLists.txt;0;")
