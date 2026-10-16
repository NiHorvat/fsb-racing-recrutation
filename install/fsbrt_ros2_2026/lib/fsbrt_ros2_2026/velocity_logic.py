#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64
from geometry_msgs.msg import Point
from fsbrt_ros2_2026.msg import VehicleState
import math
from fsbrt_ros2_2026 import settings
#import...

"""
Author:

FSBRT Autonomous - Recruitment task - solution

This node determines the desired velocity for the vehicle.
It subscribes to the vehicle's state (position, angle, velocity) and the upcoming path horizon from the controller.
Based on this information, it calculates and publishes the desired velocity.
"""

class VelocityLogic(Node):
    """
    Determines and publishes the desired velocity of the car.
    """
    def __init__(self):
        """
        Initializes subscribers, publisher, and state variables.
        """
        super().__init__('velocity_logic')

        # Subscribers
        self.create_subscription(VehicleState, 'controller/vehicle_state', self.state_callback, 1)

        # Publisher
        self.pub_desired_velocity = self.create_publisher(Float64, 'velocity_logic/desired_velocity', 1)

    def state_callback(self, msg: VehicleState):
        horizon = [(p.x, p.y) for p in msg.horizon.points]
        current_velocity = msg.current_velocity
        current_theta = msg.current_theta
        current_position = msg.current_position
        maximum_velocity = settings.MAX_VELOCITY

        # ----------------------------------------------------------
        # -YOUR CODE START------------------------------------------
        # ----------------------------------------------------------
        # TODO: Implement your logic for assigning velocity using the data from subscribers
        # Reminder: Preferred programming language for this task is C++.
        #           You can find the C++ equivalent of this node in the src directory

        desired_velocity = 1.8 # Placeholder value

        # ----------------------------------------------------------
        # -YOUR CODE END------------------------------------------
        # ----------------------------------------------------------

        self.pub_desired_velocity.publish(Float64(data=desired_velocity))


def main(args=None):
    settings.init()
    rclpy.init(args=args)
    node = VelocityLogic()
    node.get_logger().info("Velocity Logic node ready.")
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
