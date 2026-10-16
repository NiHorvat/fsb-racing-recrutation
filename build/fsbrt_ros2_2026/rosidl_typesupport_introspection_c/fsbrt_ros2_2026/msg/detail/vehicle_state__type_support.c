// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "fsbrt_ros2_2026/msg/detail/vehicle_state__rosidl_typesupport_introspection_c.h"
#include "fsbrt_ros2_2026/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "fsbrt_ros2_2026/msg/detail/vehicle_state__functions.h"
#include "fsbrt_ros2_2026/msg/detail/vehicle_state__struct.h"


// Include directives for member types
// Member `horizon`
#include "geometry_msgs/msg/polygon.h"
// Member `horizon`
#include "geometry_msgs/msg/detail/polygon__rosidl_typesupport_introspection_c.h"
// Member `current_position`
#include "geometry_msgs/msg/point.h"
// Member `current_position`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  fsbrt_ros2_2026__msg__VehicleState__init(message_memory);
}

void fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_fini_function(void * message_memory)
{
  fsbrt_ros2_2026__msg__VehicleState__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array[4] = {
  {
    "horizon",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(fsbrt_ros2_2026__msg__VehicleState, horizon),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(fsbrt_ros2_2026__msg__VehicleState, current_velocity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_theta",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(fsbrt_ros2_2026__msg__VehicleState, current_theta),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(fsbrt_ros2_2026__msg__VehicleState, current_position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_members = {
  "fsbrt_ros2_2026__msg",  // message namespace
  "VehicleState",  // message name
  4,  // number of fields
  sizeof(fsbrt_ros2_2026__msg__VehicleState),
  false,  // has_any_key_member_
  fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array,  // message members
  fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_init_function,  // function to initialize message memory (memory has to be allocated)
  fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle = {
  0,
  &fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_members,
  get_message_typesupport_handle_function,
  &fsbrt_ros2_2026__msg__VehicleState__get_type_hash,
  &fsbrt_ros2_2026__msg__VehicleState__get_type_description,
  &fsbrt_ros2_2026__msg__VehicleState__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_fsbrt_ros2_2026
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, fsbrt_ros2_2026, msg, VehicleState)() {
  fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Polygon)();
  fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle.typesupport_identifier) {
    fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &fsbrt_ros2_2026__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
