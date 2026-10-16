// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "fsbrt_ros2_2026/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "fsbrt_ros2_2026/msg/detail/vehicle_state__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace fsbrt_ros2_2026
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
cdr_serialize(
  const fsbrt_ros2_2026::msg::VehicleState & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  fsbrt_ros2_2026::msg::VehicleState & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
get_serialized_size(
  const fsbrt_ros2_2026::msg::VehicleState & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
max_serialized_size_VehicleState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
cdr_serialize_key(
  const fsbrt_ros2_2026::msg::VehicleState & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
get_serialized_size_key(
  const fsbrt_ros2_2026::msg::VehicleState & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
max_serialized_size_key_VehicleState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace fsbrt_ros2_2026

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_fsbrt_ros2_2026
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, fsbrt_ros2_2026, msg, VehicleState)();

#ifdef __cplusplus
}
#endif

#endif  // FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
