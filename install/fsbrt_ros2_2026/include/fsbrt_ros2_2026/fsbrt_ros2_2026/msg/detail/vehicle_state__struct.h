// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "fsbrt_ros2_2026/msg/vehicle_state.h"


#ifndef FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__STRUCT_H_
#define FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'horizon'
#include "geometry_msgs/msg/detail/polygon__struct.h"
// Member 'current_position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/VehicleState in the package fsbrt_ros2_2026.
typedef struct fsbrt_ros2_2026__msg__VehicleState
{
  geometry_msgs__msg__Polygon horizon;
  double current_velocity;
  double current_theta;
  geometry_msgs__msg__Point current_position;
} fsbrt_ros2_2026__msg__VehicleState;

// Struct for a sequence of fsbrt_ros2_2026__msg__VehicleState.
typedef struct fsbrt_ros2_2026__msg__VehicleState__Sequence
{
  fsbrt_ros2_2026__msg__VehicleState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} fsbrt_ros2_2026__msg__VehicleState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__STRUCT_H_
