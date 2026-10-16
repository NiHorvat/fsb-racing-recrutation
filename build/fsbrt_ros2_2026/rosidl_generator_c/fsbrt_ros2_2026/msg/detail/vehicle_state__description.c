// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from fsbrt_ros2_2026:msg/VehicleState.idl
// generated code does not contain a copyright notice

#include "fsbrt_ros2_2026/msg/detail/vehicle_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_fsbrt_ros2_2026
const rosidl_type_hash_t *
fsbrt_ros2_2026__msg__VehicleState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x53, 0x92, 0xeb, 0x5f, 0xcc, 0xe2, 0x2b, 0xab,
      0xd3, 0x4e, 0x61, 0xe6, 0x98, 0xef, 0xae, 0xce,
      0x79, 0x89, 0x94, 0x91, 0x79, 0x6c, 0xcc, 0x21,
      0x88, 0x6d, 0x12, 0xfa, 0x61, 0x73, 0xe2, 0x89,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/point__functions.h"
#include "geometry_msgs/msg/detail/point32__functions.h"
#include "geometry_msgs/msg/detail/polygon__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Point32__EXPECTED_HASH = {1, {
    0x2f, 0xc4, 0xdb, 0x7c, 0xae, 0x16, 0xa4, 0x58,
    0x2c, 0x79, 0xa5, 0x6b, 0x66, 0x17, 0x3a, 0x8d,
    0x48, 0xd5, 0x2c, 0x7d, 0xc5, 0x20, 0xdd, 0xc5,
    0x5a, 0x0d, 0x4b, 0xcf, 0x2a, 0x4b, 0xfd, 0xbc,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Polygon__EXPECTED_HASH = {1, {
    0x37, 0x82, 0xf9, 0xf0, 0xbf, 0x04, 0x49, 0x64,
    0xd6, 0x92, 0xd6, 0xc0, 0x17, 0xd7, 0x05, 0xe3,
    0x76, 0x11, 0xaf, 0xb1, 0xf0, 0xbf, 0x6a, 0x9d,
    0xee, 0x24, 0x8a, 0x7d, 0xda, 0x0f, 0x78, 0x4a,
  }};
#endif

static char fsbrt_ros2_2026__msg__VehicleState__TYPE_NAME[] = "fsbrt_ros2_2026/msg/VehicleState";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";
static char geometry_msgs__msg__Point32__TYPE_NAME[] = "geometry_msgs/msg/Point32";
static char geometry_msgs__msg__Polygon__TYPE_NAME[] = "geometry_msgs/msg/Polygon";

// Define type names, field names, and default values
static char fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__horizon[] = "horizon";
static char fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__current_velocity[] = "current_velocity";
static char fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__current_theta[] = "current_theta";
static char fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__current_position[] = "current_position";

static rosidl_runtime_c__type_description__Field fsbrt_ros2_2026__msg__VehicleState__FIELDS[] = {
  {
    {fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__horizon, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Polygon__TYPE_NAME, 25, 25},
    },
    {NULL, 0, 0},
  },
  {
    {fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__current_velocity, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__current_theta, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {fsbrt_ros2_2026__msg__VehicleState__FIELD_NAME__current_position, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription fsbrt_ros2_2026__msg__VehicleState__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point32__TYPE_NAME, 25, 25},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Polygon__TYPE_NAME, 25, 25},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
fsbrt_ros2_2026__msg__VehicleState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {fsbrt_ros2_2026__msg__VehicleState__TYPE_NAME, 32, 32},
      {fsbrt_ros2_2026__msg__VehicleState__FIELDS, 4, 4},
    },
    {fsbrt_ros2_2026__msg__VehicleState__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point32__EXPECTED_HASH, geometry_msgs__msg__Point32__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Point32__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Polygon__EXPECTED_HASH, geometry_msgs__msg__Polygon__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = geometry_msgs__msg__Polygon__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "geometry_msgs/Polygon horizon\n"
  "float64 current_velocity\n"
  "float64 current_theta\n"
  "geometry_msgs/Point current_position";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
fsbrt_ros2_2026__msg__VehicleState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {fsbrt_ros2_2026__msg__VehicleState__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 113, 113},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
fsbrt_ros2_2026__msg__VehicleState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *fsbrt_ros2_2026__msg__VehicleState__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Point32__get_individual_type_description_source(NULL);
    sources[3] = *geometry_msgs__msg__Polygon__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
