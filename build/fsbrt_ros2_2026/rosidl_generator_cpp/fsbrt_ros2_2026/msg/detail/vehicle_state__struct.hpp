// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "fsbrt_ros2_2026/msg/vehicle_state.hpp"


#ifndef FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_
#define FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'horizon'
#include "geometry_msgs/msg/detail/polygon__struct.hpp"
// Member 'current_position'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__fsbrt_ros2_2026__msg__VehicleState __attribute__((deprecated))
#else
# define DEPRECATED__fsbrt_ros2_2026__msg__VehicleState __declspec(deprecated)
#endif

namespace fsbrt_ros2_2026
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleState_
{
  using Type = VehicleState_<ContainerAllocator>;

  explicit VehicleState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : horizon(_init),
    current_position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_velocity = 0.0;
      this->current_theta = 0.0;
    }
  }

  explicit VehicleState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : horizon(_alloc, _init),
    current_position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_velocity = 0.0;
      this->current_theta = 0.0;
    }
  }

  // field types and members
  using _horizon_type =
    geometry_msgs::msg::Polygon_<ContainerAllocator>;
  _horizon_type horizon;
  using _current_velocity_type =
    double;
  _current_velocity_type current_velocity;
  using _current_theta_type =
    double;
  _current_theta_type current_theta;
  using _current_position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _current_position_type current_position;

  // setters for named parameter idiom
  Type & set__horizon(
    const geometry_msgs::msg::Polygon_<ContainerAllocator> & _arg)
  {
    this->horizon = _arg;
    return *this;
  }
  Type & set__current_velocity(
    const double & _arg)
  {
    this->current_velocity = _arg;
    return *this;
  }
  Type & set__current_theta(
    const double & _arg)
  {
    this->current_theta = _arg;
    return *this;
  }
  Type & set__current_position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->current_position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator> *;
  using ConstRawPtr =
    const fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__fsbrt_ros2_2026__msg__VehicleState
    std::shared_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__fsbrt_ros2_2026__msg__VehicleState
    std::shared_ptr<fsbrt_ros2_2026::msg::VehicleState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleState_ & other) const
  {
    if (this->horizon != other.horizon) {
      return false;
    }
    if (this->current_velocity != other.current_velocity) {
      return false;
    }
    if (this->current_theta != other.current_theta) {
      return false;
    }
    if (this->current_position != other.current_position) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleState_

// alias to use template instance with default allocator
using VehicleState =
  fsbrt_ros2_2026::msg::VehicleState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace fsbrt_ros2_2026

#endif  // FSBRT_ROS2_2026__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_
