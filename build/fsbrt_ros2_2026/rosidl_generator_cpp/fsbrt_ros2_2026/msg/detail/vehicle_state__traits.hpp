// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "fsbrt_ros2_2026/msg/vehicle_state.hpp"


#ifndef FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_
#define FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "fsbrt_ros2_2026/msg/detail/vehicle_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'horizon'
#include "geometry_msgs/msg/detail/polygon__traits.hpp"
// Member 'current_position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace fsbrt_ros2_2026
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleState & msg,
  std::ostream & out)
{
  out << "{";
  // member: horizon
  {
    out << "horizon: ";
    to_flow_style_yaml(msg.horizon, out);
    out << ", ";
  }

  // member: current_velocity
  {
    out << "current_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.current_velocity, out);
    out << ", ";
  }

  // member: current_theta
  {
    out << "current_theta: ";
    rosidl_generator_traits::value_to_yaml(msg.current_theta, out);
    out << ", ";
  }

  // member: current_position
  {
    out << "current_position: ";
    to_flow_style_yaml(msg.current_position, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: horizon
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "horizon:\n";
    to_block_style_yaml(msg.horizon, out, indentation + 2);
  }

  // member: current_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.current_velocity, out);
    out << "\n";
  }

  // member: current_theta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_theta: ";
    rosidl_generator_traits::value_to_yaml(msg.current_theta, out);
    out << "\n";
  }

  // member: current_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_position:\n";
    to_block_style_yaml(msg.current_position, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace fsbrt_ros2_2026

namespace rosidl_generator_traits
{

[[deprecated("use fsbrt_ros2_2026::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const fsbrt_ros2_2026::msg::VehicleState & msg,
  std::ostream & out, size_t indentation = 0)
{
  fsbrt_ros2_2026::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use fsbrt_ros2_2026::msg::to_yaml() instead")]]
inline std::string to_yaml(const fsbrt_ros2_2026::msg::VehicleState & msg)
{
  return fsbrt_ros2_2026::msg::to_yaml(msg);
}

template<>
inline const char * data_type<fsbrt_ros2_2026::msg::VehicleState>()
{
  return "fsbrt_ros2_2026::msg::VehicleState";
}

template<>
inline const char * name<fsbrt_ros2_2026::msg::VehicleState>()
{
  return "fsbrt_ros2_2026/msg/VehicleState";
}

template<>
struct has_fixed_size<fsbrt_ros2_2026::msg::VehicleState>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<geometry_msgs::msg::Polygon>::value> {};

template<>
struct has_bounded_size<fsbrt_ros2_2026::msg::VehicleState>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<geometry_msgs::msg::Polygon>::value> {};

template<>
struct is_message<fsbrt_ros2_2026::msg::VehicleState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_
