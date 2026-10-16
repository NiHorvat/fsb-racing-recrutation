#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSDurabilityPolicy, QoSReliabilityPolicy, QoSHistoryPolicy
from geometry_msgs.msg import Pose2D
from geometry_msgs.msg import Twist
from std_msgs.msg import Bool
import math

from fsbrt_ros2_2026 import drawer as dr
from fsbrt_ros2_2026 import settings


"""
Author: Matej Lovreković

FSBRT Autonomous - Recruitment task

Initialise simulator node that sends position of formula to controller after receiving steering and gas command from controller.
Simple vehicle dynamics is applied to simulate response. Speed and yaw velocity are integrated to get position and orientation.
"""

f = 1 # 1/inertia


class simulate(Node):


    """
    Defines behaviour of simulator.
    """


    def draw_request(self,x,y,theta):

        """
        Function that every X_SECONDS_APPEREANCE sends pose of a car to drawing queue.
        """

        if self.k == settings.X_SECONDS_APPEREANCE*settings.SAMPLING:
            dr.plt_draw_arrows(x, y, theta)
            self.k = 1
        else:
            self.k += 1


    def draw_graphs(self):

        """
        Function that draws current buffer of angular and linear velocity.
        """

        dr.end_result_speed(self.velocities_commands, self.velocities, settings.SAMPLING)
        dr.end_result_steering(self.ang_velocities_commands, self.ang_velocities, settings.SAMPLING)


    def goal_achieved_callback(self, msg: Bool):
        """
        Tracks the shared GOAL_ACHIEVED flag published by the controller
        (replaces the ROS1 global parameter 'GOAL_ACHIEVED').
        """
        self.goal_achieved = msg.data


    def command_callback(self, command):

        """
        Callback is being called(executed) every time a new message arrives.
        All dynamics is calculated in this callback.
        """

        #Read parameters
        velocity_prev, ang_vel_prev = self.previous_state[0], self.previous_state[1]
        velocity_wanted, ang_vel_wanted = command.linear.x, command.angular.z



        #Velocity_dynamics
        if velocity_prev < velocity_wanted: #Accelerating
                velocity = ((1/settings.SAMPLING) * settings.A_a * velocity_wanted) / (velocity_prev+1) + velocity_prev
                if velocity > velocity_wanted: #Constraint
                    velocity = velocity_wanted


        elif velocity_prev > velocity_wanted: #Braking
            velocity = -((1/settings.SAMPLING) * settings.A_b * (settings.MAX_VELOCITY - velocity_wanted)) / (velocity_prev+1) + velocity_prev
            if velocity < velocity_wanted: #Constraint
                velocity = velocity_wanted

        else:
            velocity = velocity_wanted  #Retain commanded speed



        #Steering dynamics
        if ang_vel_wanted < 0:
            if abs(velocity) < 1:
                ang_vel = ang_vel_prev - settings.STEERING_POWER*(1/settings.SAMPLING)*(6*f)*velocity
            else:
                ang_vel = ang_vel_prev - settings.STEERING_POWER*(1/settings.SAMPLING)*(6*f)/(velocity)

            if ang_vel < ang_vel_wanted:
                ang_vel = ang_vel_wanted
        else:
            if abs(velocity) < 1:
                ang_vel = ang_vel_prev + settings.STEERING_POWER*(1/settings.SAMPLING)*(6*f)*velocity
            else:
                ang_vel = ang_vel_prev + settings.STEERING_POWER*(1/settings.SAMPLING)*(6*f)/(velocity)

            if ang_vel > ang_vel_wanted:
                ang_vel = ang_vel_wanted


        #Velocities integration to get positions
        x,y, theta = self.position.x, self.position.y, self.position.theta
        new_theta = theta + ang_vel*(1/settings.SAMPLING)
        new_x, new_y = x + velocity*math.cos(new_theta)*(1/settings.SAMPLING), y + velocity*math.sin(new_theta)*(1/settings.SAMPLING)

        #Clipping theta to <-pi,pi]
        if new_theta > math.pi:
            new_theta = new_theta - 2*math.pi
        elif new_theta <= -math.pi:
            new_theta = new_theta + 2*math.pi


        #Update
        self.previous_state = [velocity, ang_vel]
        new_position = Pose2D(x=new_x, y=new_y, theta=new_theta)
        self.position = new_position
        self.c_velocity.linear.x = velocity

        #Save for drawings
        if (self.k == settings.X_SECONDS_APPEREANCE*settings.SAMPLING) and (not self.goal_achieved):
            self.velocities_commands.append(velocity_wanted)
            self.ang_velocities_commands.append(ang_vel_wanted)
            self.velocities.append(velocity)
            self.ang_velocities.append(ang_vel)


        #Draw current position
        self.draw_request(self.position.x, self.position.y, self.position.theta)




    def __init__(self):

        """
        Initialise publisher, subscriber, starting position of a car and parameters specific for this script.
        """

        super().__init__('simulator')

        self.previous_state = [0,0] #[prev_velocity, prev_angular_vel]
        self.position = Pose2D()    #Object that stores postition for publishing
        self.position.x = 244.323428998323  #Starting position of a car
        self.position.y = 92.0534487527686  #Starting position of a car
        self.position.theta = math.pi       #Starting orientation of a car
        self.command = Twist()              #Object that saves incoming message
        self.c_velocity = Twist()           #Object that saves current speed for publishing
        self.k = 1                  #Counter for plotting

        # Shared GOAL_ACHIEVED flag (replaces ROS1 global param)
        self.goal_achieved = False

        #Lists that contain all values through time for plotting
        self.velocities = [0]
        self.ang_velocities = [0]
        self.velocities_commands = [0]
        self.ang_velocities_commands = [0]

        self.pub1 = self.create_publisher(Pose2D, 'simulator/pose', 1)
        self.pub2 = self.create_publisher(Twist, 'simulator/velocity', 1)
        self.create_subscription(Twist, 'simulator/command', self.command_callback, 1)

        # Latched subscription to the shared GOAL_ACHIEVED flag
        latched_qos = QoSProfile(
            depth=1,
            history=QoSHistoryPolicy.KEEP_LAST,
            reliability=QoSReliabilityPolicy.RELIABLE,
            durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
        )
        self.create_subscription(Bool, 'goal_achieved', self.goal_achieved_callback, latched_qos)

        # Timer replaces the ROS1 rospy.Rate(SAMPLING) publish loop:
        # publish current velocity and pose at SAMPLING Hz.
        self.timer = self.create_timer(1.0/settings.SAMPLING, self._publish_state)


    def _publish_state(self):
        """
        Periodic publisher (was the body of the ROS1 run() while-loop).
        """
        self.pub2.publish(self.c_velocity)
        self.pub1.publish(self.position)



def main(args=None):

    settings.init()
    dr.init_drawer() #Initialize live plotting

    rclpy.init(args=args)

    sim = simulate()
    sim.get_logger().info("Simulator ready.")

    try:
        rclpy.spin(sim)
    except KeyboardInterrupt:
        pass
    finally:
        # When process is terminated graphs are drawn (replaces rospy.on_shutdown)
        try:
            sim.draw_graphs()
        except Exception as e:
            sim.get_logger().warn('Could not draw graphs on shutdown: ' + str(e))
        sim.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
