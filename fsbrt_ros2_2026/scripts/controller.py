#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSDurabilityPolicy, QoSReliabilityPolicy, QoSHistoryPolicy
import numpy as np
from math import sqrt, atan2, pi, dist
from geometry_msgs.msg import Pose2D, Twist, Point
from std_msgs.msg import Float64, Bool
from fsbrt_ros2_2026.msg import VehicleState
from geometry_msgs.msg import Polygon, Point32
import time
from fsbrt_ros2_2026 import world as wr
from fsbrt_ros2_2026 import settings


"""
Author: Matej Lovreković

FSBRT Autonomous - Recruitment task

Initialise controller node that sends velocity and angular velocity requests to the simulator after receiving current race car position from the simulator.
Steering request problem is solved, user must determine the desired velocity of the race car based on fixed future checkpoint's horizon.
"""


class control(Node):

    """
    Defines  behaviour of controller.
    """

    def get_ang_distance(self,goal_x ,goal_y, pose_x, pose_y, theta):

        """
        Function that computes angle form current car orientation to orientation towards next (goal / checkpoint) in order to set steering command.
        """

        ang_distance = atan2(goal_y - pose_y ,goal_x -  pose_x) - theta

        return ang_distance


    def velocity_callback(self, c_velocity):

        """
        Callback is active when new message arrives from subscribed node.
        Current car velocity is updated.
        """

        self.current_velocity = c_velocity.linear.x

    def desired_velocity_callback(self, msg: Float64):
        """
        Callback for the desired velocity calculated by the velocity_logic node.
        """
        if not self.goal_achieved:
            self.cmd_vel.linear.x = msg.data
        else:
            self.cmd_vel.linear.x = 0.0


    def set_goal_achieved(self, value: bool):
        """
        Update the shared GOAL_ACHIEVED flag and publish it (latched) so other
        nodes (simulator) observe the same value. Replaces the ROS1 global
        parameter 'GOAL_ACHIEVED'.
        """
        self.goal_achieved = value
        self.pub_goal_achieved.publish(Bool(data=value))


    def pose_callback(self, Pose):

        """
        Callback is active when new message arrives from subscribed node.
        Desired steering and velocity values are computed.
        """

        GOAL_ACHIEVED = self.goal_achieved
        self.position = Pose


        #If all checkpoints are passed formula is finished.
        if self.i == self.shape[0]-1:
            self.set_goal_achieved(True)
            GOAL_ACHIEVED = True
            if not self._lap_time_logged:
                self.get_logger().info('Your lap time is: ' + str(round(time.time()-self.start, 3)) + 'seconds')
                self._lap_time_logged = True


        #If formula is not finished and is close to checkpoint up to tolerance, set goal for next checkpoint.
        if (not GOAL_ACHIEVED):
            if dist(self.central_trajectories[self.i], [self.position.x, self.position.y]) < self.tolerance:
                self.i = self.i + 1

        #Check if checkpoint has changed to print information on terminal
        if self.i_p != self.i:
            self.get_logger().info('Checkpoint '+ str(self.i) + ' passed')
            self.i_p = self.i


        #Drive one lap autonomously then stop
        if (not GOAL_ACHIEVED):

            ang_dist = self.get_ang_distance(self.central_trajectories[self.i][0], self.central_trajectories[self.i][1],
            self.position.x, self.position.y, self.position.theta)


            #Conditions that prevents formula to choose longer path to checkpoint (ex. makes a loop right when it can just turn slight left)
            if ang_dist < -pi:
                ang_dist = ang_dist + 2*pi
            elif ang_dist > pi:
                ang_dist = ang_dist - 2*pi

            excess = settings.POINTS_IN_FUTURE - (self.shape[0]- self.i) #When car is close to finish ensure that starting checkpoints are taken in observation
            horison = self.central_trajectories[self.i : self.i + settings.POINTS_IN_FUTURE] if self.i < (self.shape[0]-settings.POINTS_IN_FUTURE) else self.central_trajectories[self.i:] + self.central_trajectories[:excess]

            #Set desired steering and velocity (command)
            self.cmd_vel.angular.z = ang_dist

            # Create and publish the vehicle state message
            state_msg = VehicleState()
            state_msg.current_velocity = self.current_velocity
            state_msg.current_theta = self.position.theta
            state_msg.current_position = Point(x=self.position.x, y=self.position.y, z=0.0)

            horizon_msg = Polygon()
            for point in horison:
                horizon_msg.points.append(Point32(x=float(point[0]), y=float(point[1]), z=0.0))
            state_msg.horizon = horizon_msg

            self.pub_vehicle_state.publish(state_msg)

        else:
            self.cmd_vel.angular.z = 0.0
            self.cmd_vel.linear.x = 0.0

        self.pub.publish(self.cmd_vel)



    def __init__(self):

        """
        Initialize publishers and subscribers as well as all parameters specific for this script.
        """

        super().__init__('controller')

        self.position = Pose2D()    #Object that stores subscribed position
        self.cmd_vel = Twist()      #Object that stores commands for publishing
        self.central_trajectories = wr.central_trajectory
        self.shape = np.shape(self.central_trajectories) # Tuple - (number of central points, 2)
        self.i = 0                  #Variable that corresponds to current chackpoint number
        self.i_p = 0                #Variable that memorises previous checkpoint
        self.tolerance = 0.7        #Radial tolerance that tells if checkpoint is reached [m]
        self.current_velocity = 0.0 #Saves current velocity from incoming simulator message
        self.cmd_vel.linear.x = 0.0 # Initialize linear velocity

        # Shared GOAL_ACHIEVED flag (replaces ROS1 global param)
        self.goal_achieved = False
        self._lap_time_logged = False

        # Latched QoS so late-joining subscribers (simulator) get the last value
        latched_qos = QoSProfile(
            depth=1,
            history=QoSHistoryPolicy.KEEP_LAST,
            reliability=QoSReliabilityPolicy.RELIABLE,
            durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
        )

        #Publishes command and subscribes to current formula position
        self.pub = self.create_publisher(Twist, 'controller/command', 1)
        self.pub_vehicle_state = self.create_publisher(VehicleState, 'controller/vehicle_state', 1)
        self.pub_goal_achieved = self.create_publisher(Bool, 'goal_achieved', latched_qos)

        # Publish initial GOAL_ACHIEVED=False (mirrors launch-file param init)
        self.pub_goal_achieved.publish(Bool(data=self.goal_achieved))

        self.create_subscription(Pose2D, 'controller/pose', self.pose_callback, 1)
        self.create_subscription(Twist, 'controller/velocity', self.velocity_callback, 1)
        self.create_subscription(Float64, 'velocity_logic/desired_velocity', self.desired_velocity_callback, 1)

        self.start = time.time() #Start counting time of lap


    def run(self):

        """
        Runs node and all comunication at desired Hz rate.
        """

        rclpy.spin(self)



def main(args=None):

    settings.init()

    rclpy.init(args=args)

    ctr = control()
    ctr.get_logger().info("Driving ready.")

    try:
        ctr.run()
    except KeyboardInterrupt:
        pass
    finally:
        ctr.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
