# CMake generated Testfile for 
# Source directory: /home/yzz/kal_ws/src/path_generator_ros_tool
# Build directory: /home/yzz/kal_ws/build/path_generator_ros_tool
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(build_tests "/home/yzz/kal_ws/build/path_generator_ros_tool/catkin_generated/env_cached.sh" "bash" "-c" "\"/usr/bin/cmake\" --build /home/yzz/kal_ws/build/path_generator_ros_tool --parallel 16 --target tests && /usr/bin/python3 /opt/ros/noetic/share/mrt_cmake_modules/cmake/../scripts/init_coverage.py path_generator_ros_tool /home/yzz/kal_ws/build/path_generator_ros_tool /home/yzz/kal_ws/src/path_generator_ros_tool /home/yzz/kal_ws/build/path_generator_ros_tool/test_results/path_generator_ros_tool")
set_tests_properties(build_tests PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/mrt_cmake_modules/cmake/Modules/MrtTesting.cmake;92;add_test;/opt/ros/noetic/share/mrt_cmake_modules/cmake/mrt_cmake_modules-macros.cmake;1235;mrt_init_testing;/home/yzz/kal_ws/src/path_generator_ros_tool/CMakeLists.txt;84;mrt_add_ros_tests;/home/yzz/kal_ws/src/path_generator_ros_tool/CMakeLists.txt;0;")
subdirs("gtest")
