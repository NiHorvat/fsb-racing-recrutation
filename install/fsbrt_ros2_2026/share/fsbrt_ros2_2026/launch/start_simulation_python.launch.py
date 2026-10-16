#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""
FSBRT Autonomous - Recruitment task

ROS2 launch file (Python velocity_logic variant).
Starts the simulator, controller, and the Python velocity_logic node.

Note on GOAL_ACHIEVED:
  In ROS1 this was a global rosparam initialised here. ROS2 has no global
  parameter server, so the shared flag is now a latched 'goal_achieved'
  (std_msgs/Bool) topic. The controller node publishes the initial value
  (False) on startup and updates it, while simulator subscribes to it.
"""

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([

        Node(
            package='fsbrt_ros2_2026',
            executable='simulator.py',
            name='simulator',
            output='screen',
            remappings=[
                ('simulator/velocity', 'controller/velocity'),
                ('simulator/pose', 'controller/pose'),
            ],
        ),

        Node(
            package='fsbrt_ros2_2026',
            executable='controller.py',
            name='controller',
            output='screen',
            remappings=[
                ('controller/command', 'simulator/command'),
            ],
        ),

        # Python node
        Node(
            package='fsbrt_ros2_2026',
            executable='velocity_logic.py',
            name='velocity_logic',
            output='screen',
        ),
    ])
