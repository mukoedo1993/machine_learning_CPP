# CMake generated Testfile for 
# Source directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/highgui
# Build directory: /home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/bin/opencv_test_highgui" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVUtils.cmake;1677;add_test;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/highgui/CMakeLists.txt;165;ocv_add_accuracy_tests;/home/zcw/C++_MUKOEDO_LIB/pytorch_clone/opencv-master/modules/highgui/CMakeLists.txt;0;")
