#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "fsbrt_ros2_2026__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__fsbrt_ros2_2026__msg__VehicleState() -> *const std::ffi::c_void;
}

#[link(name = "fsbrt_ros2_2026__rosidl_generator_c")]
extern "C" {
    fn fsbrt_ros2_2026__msg__VehicleState__init(msg: *mut VehicleState) -> bool;
    fn fsbrt_ros2_2026__msg__VehicleState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VehicleState>, size: usize) -> bool;
    fn fsbrt_ros2_2026__msg__VehicleState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VehicleState>);
    fn fsbrt_ros2_2026__msg__VehicleState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VehicleState>, out_seq: *mut rosidl_runtime_rs::Sequence<VehicleState>) -> bool;
}

// Corresponds to fsbrt_ros2_2026__msg__VehicleState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub horizon: geometry_msgs::msg::rmw::Polygon,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_velocity: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_theta: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_position: geometry_msgs::msg::rmw::Point,

}



impl Default for VehicleState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !fsbrt_ros2_2026__msg__VehicleState__init(&mut msg as *mut _) {
        panic!("Call to fsbrt_ros2_2026__msg__VehicleState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VehicleState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { fsbrt_ros2_2026__msg__VehicleState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { fsbrt_ros2_2026__msg__VehicleState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { fsbrt_ros2_2026__msg__VehicleState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VehicleState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VehicleState where Self: Sized {
  const TYPE_NAME: &'static str = "fsbrt_ros2_2026/msg/VehicleState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__fsbrt_ros2_2026__msg__VehicleState() }
  }
}


