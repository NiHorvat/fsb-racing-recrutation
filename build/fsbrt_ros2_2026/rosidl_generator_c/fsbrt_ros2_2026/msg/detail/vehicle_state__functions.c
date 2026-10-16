// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice
#include "fsbrt_ros2_2026/msg/detail/vehicle_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `horizon`
#include "geometry_msgs/msg/detail/polygon__functions.h"
// Member `current_position`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
fsbrt_ros2_2026__msg__VehicleState__init(fsbrt_ros2_2026__msg__VehicleState * msg)
{
  if (!msg) {
    return false;
  }
  // horizon
  if (!geometry_msgs__msg__Polygon__init(&msg->horizon)) {
    fsbrt_ros2_2026__msg__VehicleState__fini(msg);
    return false;
  }
  // current_velocity
  // current_theta
  // current_position
  if (!geometry_msgs__msg__Point__init(&msg->current_position)) {
    fsbrt_ros2_2026__msg__VehicleState__fini(msg);
    return false;
  }
  return true;
}

void
fsbrt_ros2_2026__msg__VehicleState__fini(fsbrt_ros2_2026__msg__VehicleState * msg)
{
  if (!msg) {
    return;
  }
  // horizon
  geometry_msgs__msg__Polygon__fini(&msg->horizon);
  // current_velocity
  // current_theta
  // current_position
  geometry_msgs__msg__Point__fini(&msg->current_position);
}

bool
fsbrt_ros2_2026__msg__VehicleState__are_equal(const fsbrt_ros2_2026__msg__VehicleState * lhs, const fsbrt_ros2_2026__msg__VehicleState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // horizon
  if (!geometry_msgs__msg__Polygon__are_equal(
      &(lhs->horizon), &(rhs->horizon)))
  {
    return false;
  }
  // current_velocity
  if (lhs->current_velocity != rhs->current_velocity) {
    return false;
  }
  // current_theta
  if (lhs->current_theta != rhs->current_theta) {
    return false;
  }
  // current_position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->current_position), &(rhs->current_position)))
  {
    return false;
  }
  return true;
}

bool
fsbrt_ros2_2026__msg__VehicleState__copy(
  const fsbrt_ros2_2026__msg__VehicleState * input,
  fsbrt_ros2_2026__msg__VehicleState * output)
{
  if (!input || !output) {
    return false;
  }
  // horizon
  if (!geometry_msgs__msg__Polygon__copy(
      &(input->horizon), &(output->horizon)))
  {
    return false;
  }
  // current_velocity
  output->current_velocity = input->current_velocity;
  // current_theta
  output->current_theta = input->current_theta;
  // current_position
  if (!geometry_msgs__msg__Point__copy(
      &(input->current_position), &(output->current_position)))
  {
    return false;
  }
  return true;
}

fsbrt_ros2_2026__msg__VehicleState *
fsbrt_ros2_2026__msg__VehicleState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  fsbrt_ros2_2026__msg__VehicleState * msg = (fsbrt_ros2_2026__msg__VehicleState *)allocator.allocate(sizeof(fsbrt_ros2_2026__msg__VehicleState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(fsbrt_ros2_2026__msg__VehicleState));
  bool success = fsbrt_ros2_2026__msg__VehicleState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
fsbrt_ros2_2026__msg__VehicleState__destroy(fsbrt_ros2_2026__msg__VehicleState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    fsbrt_ros2_2026__msg__VehicleState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
fsbrt_ros2_2026__msg__VehicleState__Sequence__init(fsbrt_ros2_2026__msg__VehicleState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  fsbrt_ros2_2026__msg__VehicleState * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(fsbrt_ros2_2026__msg__VehicleState)) {
      return false;
    }
    data = (fsbrt_ros2_2026__msg__VehicleState *)allocator.zero_allocate(size, sizeof(fsbrt_ros2_2026__msg__VehicleState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = fsbrt_ros2_2026__msg__VehicleState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        fsbrt_ros2_2026__msg__VehicleState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
fsbrt_ros2_2026__msg__VehicleState__Sequence__fini(fsbrt_ros2_2026__msg__VehicleState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      fsbrt_ros2_2026__msg__VehicleState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

fsbrt_ros2_2026__msg__VehicleState__Sequence *
fsbrt_ros2_2026__msg__VehicleState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  fsbrt_ros2_2026__msg__VehicleState__Sequence * array = (fsbrt_ros2_2026__msg__VehicleState__Sequence *)allocator.allocate(sizeof(fsbrt_ros2_2026__msg__VehicleState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = fsbrt_ros2_2026__msg__VehicleState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
fsbrt_ros2_2026__msg__VehicleState__Sequence__destroy(fsbrt_ros2_2026__msg__VehicleState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    fsbrt_ros2_2026__msg__VehicleState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
fsbrt_ros2_2026__msg__VehicleState__Sequence__are_equal(const fsbrt_ros2_2026__msg__VehicleState__Sequence * lhs, const fsbrt_ros2_2026__msg__VehicleState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!fsbrt_ros2_2026__msg__VehicleState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
fsbrt_ros2_2026__msg__VehicleState__Sequence__copy(
  const fsbrt_ros2_2026__msg__VehicleState__Sequence * input,
  fsbrt_ros2_2026__msg__VehicleState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(fsbrt_ros2_2026__msg__VehicleState)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(fsbrt_ros2_2026__msg__VehicleState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    fsbrt_ros2_2026__msg__VehicleState * data =
      (fsbrt_ros2_2026__msg__VehicleState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!fsbrt_ros2_2026__msg__VehicleState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          fsbrt_ros2_2026__msg__VehicleState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!fsbrt_ros2_2026__msg__VehicleState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
