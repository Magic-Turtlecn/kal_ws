# CMake generated Testfile for 
# Source directory: /home/yzz/kal_ws/src/kal
# Build directory: /home/yzz/kal_ws/build/kal
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(build_tests "/home/yzz/kal_ws/build/kal/catkin_generated/env_cached.sh" "bash" "-c" "\"/usr/bin/cmake\" --build /home/yzz/kal_ws/build/kal --parallel 16 --target tests && /usr/bin/python3 /opt/ros/noetic/share/mrt_cmake_modules/cmake/../scripts/init_coverage.py kal /home/yzz/kal_ws/build/kal /home/yzz/kal_ws/src/kal /home/yzz/kal_ws/build/kal/test_results/kal")
set_tests_properties(build_tests PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/mrt_cmake_modules/cmake/Modules/MrtTesting.cmake;92;add_test;/opt/ros/noetic/share/mrt_cmake_modules/cmake/mrt_cmake_modules-macros.cmake;1295;mrt_init_testing;/home/yzz/kal_ws/src/kal/CMakeLists.txt;69;mrt_add_tests;/home/yzz/kal_ws/src/kal/CMakeLists.txt;0;")
subdirs("gtest")
