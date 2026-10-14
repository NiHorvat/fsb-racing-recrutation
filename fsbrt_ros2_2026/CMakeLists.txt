cmake_minimum_required(VERSION 3.8)
project(fsbrt_ros2_2026)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)                      # ADDED

include(FetchContent)                                        # ADDED
FetchContent_Declare(nanospline                              # ADDED
  GIT_REPOSITORY https://github.com/qnzhou/nanospline.git    # ADDED
  GIT_TAG main                                               # ADDED
  SOURCE_SUBDIR __no_cmake__)                                # ADDED
FetchContent_MakeAvailable(nanospline)                       # ADDED

#######################################
## Declare ROS messages (rosidl)     ##
#######################################
rosidl_generate_interfaces(${PROJECT_NAME}
"msg/VehicleState.msg"
  DEPENDENCIES std_msgs geometry_msgs
)

###########
## Build ##
###########

# C++ executable: velocity_logic
add_executable(velocity_logic src/velocity_logic.cpp)
ament_target_dependencies(velocity_logic
  rclcpp
  std_msgs
  geometry_msgs
)

# Link the generated messages from THIS package to the C++ node.
# (replaces catkin's add_dependencies on EXPORTED_TARGETS)
rosidl_get_typesupport_target(cpp_typesupport_target
${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(velocity_logic "${cpp_typesupport_target}")
target_link_libraries(velocity_logic Eigen3::Eigen)                                       # ADDED
target_include_directories(velocity_logic SYSTEM PRIVATE ${nanospline_SOURCE_DIR}/include) # ADDED

#############
## Install ##
#############

# Install the C++ executable
install(TARGETS velocity_logic
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules importable by other scripts (settings, world, drawer).
#
# NOTE: We deliberately do NOT use ament_python_install_package() here.
# ament_python_install_package() and rosidl_generate_interfaces() both create
# CMake targets named after the project, which collide when used in the same
# package (documented ROS2 limitation). Instead we install the python package
# manually into the correct site-packages directory.
ament_get_python_install_dir(_python_install_dir)
install(DIRECTORY ${PROJECT_NAME}/
  DESTINATION ${_python_install_dir}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.py"
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

# Install Python node scripts (executables run via ros2 run / launch)
install(PROGRAMS
  scripts/simulator.py
  scripts/controller.py
  scripts/velocity_logic.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# Install track data (csv) so world.py can locate them at runtime
install(DIRECTORY src/
  DESTINATION share/${PROJECT_NAME}/src
  FILES_MATCHING PATTERN "*.csv"
)

#############
## Testing ##
#############
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()