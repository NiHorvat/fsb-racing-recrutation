// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "fsbrt_ros2_2026/msg/vehicle_state.hpp"


#ifndef FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
#define FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "fsbrt_ros2_2026/msg/detail/vehicle_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace fsbrt_ros2_2026
{

namespace msg
{

namespace builder
{

class Init_VehicleState_current_position
{
public:
  explicit Init_VehicleState_current_position(::fsbrt_ros2_2026::msg::VehicleState & msg)
  : msg_(msg)
  {}
  ::fsbrt_ros2_2026::msg::VehicleState current_position(::fsbrt_ros2_2026::msg::VehicleState::_current_position_type arg)
  {
    msg_.current_position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::fsbrt_ros2_2026::msg::VehicleState msg_;
};

class Init_VehicleState_current_theta
{
public:
  explicit Init_VehicleState_current_theta(::fsbrt_ros2_2026::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_current_position current_theta(::fsbrt_ros2_2026::msg::VehicleState::_current_theta_type arg)
  {
    msg_.current_theta = std::move(arg);
    return Init_VehicleState_current_position(msg_);
  }

private:
  ::fsbrt_ros2_2026::msg::VehicleState msg_;
};

class Init_VehicleState_current_velocity
{
public:
  explicit Init_VehicleState_current_velocity(::fsbrt_ros2_2026::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_current_theta current_velocity(::fsbrt_ros2_2026::msg::VehicleState::_current_velocity_type arg)
  {
    msg_.current_velocity = std::move(arg);
    return Init_VehicleState_current_theta(msg_);
  }

private:
  ::fsbrt_ros2_2026::msg::VehicleState msg_;
};

class Init_VehicleState_horizon
{
public:
  Init_VehicleState_horizon()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleState_current_velocity horizon(::fsbrt_ros2_2026::msg::VehicleState::_horizon_type arg)
  {
    msg_.horizon = std::move(arg);
    return Init_VehicleState_current_velocity(msg_);
  }

private:
  ::fsbrt_ros2_2026::msg::VehicleState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::fsbrt_ros2_2026::msg::VehicleState>()
{
  return fsbrt_ros2_2026::msg::builder::Init_VehicleState_horizon();
}

}  // namespace fsbrt_ros2_2026

#endif  // FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
