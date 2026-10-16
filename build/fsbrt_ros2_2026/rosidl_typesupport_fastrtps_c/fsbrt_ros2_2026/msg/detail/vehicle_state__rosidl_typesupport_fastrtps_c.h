// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice
#ifndef FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "fsbrt_ros2_2026/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "fsbrt_ros2_2026/msg/detail/vehicle_state__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
bool cdr_serialize_fsbrt_ros2_2026__msg__VehicleState(
  const fsbrt_ros2_2026__msg__VehicleState * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
bool cdr_deserialize_fsbrt_ros2_2026__msg__VehicleState(
  eprosima::fastcdr::Cdr &,
  fsbrt_ros2_2026__msg__VehicleState * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
size_t get_serialized_size_fsbrt_ros2_2026__msg__VehicleState(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
size_t max_serialized_size_fsbrt_ros2_2026__msg__VehicleState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
bool cdr_serialize_key_fsbrt_ros2_2026__msg__VehicleState(
  const fsbrt_ros2_2026__msg__VehicleState * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
size_t get_serialized_size_key_fsbrt_ros2_2026__msg__VehicleState(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
size_t max_serialized_size_key_fsbrt_ros2_2026__msg__VehicleState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_fsbrt_ros2_2026
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, fsbrt_ros2_2026, msg, VehicleState)();

#ifdef __cplusplus
}
#endif

#endif  // FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
