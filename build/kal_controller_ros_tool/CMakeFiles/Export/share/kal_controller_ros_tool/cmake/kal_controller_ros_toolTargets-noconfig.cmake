#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kal_controller_ros_tool::kal_controller_ros_tool-controller-nodelet" for configuration ""
set_property(TARGET kal_controller_ros_tool::kal_controller_ros_tool-controller-nodelet APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(kal_controller_ros_tool::kal_controller_ros_tool-controller-nodelet PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libkal_controller_ros_tool-controller-nodelet.so.0.0.0"
  IMPORTED_SONAME_NOCONFIG "libkal_controller_ros_tool-controller-nodelet.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS kal_controller_ros_tool::kal_controller_ros_tool-controller-nodelet )
list(APPEND _IMPORT_CHECK_FILES_FOR_kal_controller_ros_tool::kal_controller_ros_tool-controller-nodelet "${_IMPORT_PREFIX}/lib/libkal_controller_ros_tool-controller-nodelet.so.0.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
