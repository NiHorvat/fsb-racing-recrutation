#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to fsbrt_ros2_2026__msg__VehicleState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub horizon: geometry_msgs::msg::Polygon,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_velocity: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_theta: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_position: geometry_msgs::msg::Point,

}



impl Default for VehicleState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VehicleState::default())
  }
}

impl rosidl_runtime_rs::Message for VehicleState {
  type RmwMsg = super::msg::rmw::VehicleState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        horizon: geometry_msgs::msg::Polygon::into_rmw_message(std::borrow::Cow::Owned(msg.horizon)).into_owned(),
        current_velocity: msg.current_velocity,
        current_theta: msg.current_theta,
        current_position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.current_position)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        horizon: geometry_msgs::msg::Polygon::into_rmw_message(std::borrow::Cow::Borrowed(&msg.horizon)).into_owned(),
      current_velocity: msg.current_velocity,
      current_theta: msg.current_theta,
        current_position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.current_position)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      horizon: geometry_msgs::msg::Polygon::from_rmw_message(msg.horizon),
      current_velocity: msg.current_velocity,
      current_theta: msg.current_theta,
      current_position: geometry_msgs::msg::Point::from_rmw_message(msg.current_position),
    }
  }
}


