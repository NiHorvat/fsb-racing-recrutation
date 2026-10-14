#!/usr/bin/env python3
#-*- coding: utf-8 -*-

"""
FSBRT Autonomous - Recruitment task

ROS2 launch file (C++ velocity_logic variant).
Starts the simulator, controller, and the C++ velocity_logic node.

Note on GOAL_ACHIEVED:
  In ROS1 this was a global rosparam initialised here. ROS2 has no global
  parameter server, so the shared flag is now a latched 'goal_achieved'
  (std_msgs/Bool) topic. The controller node publishes the initial value
  (False) on startup and updates it, while simulator subscribes to it.
"""

from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

config = os.path.join(
get_package_share_directory("fsbrt_ros2_2026"), "config", "config.yml")


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

        # C++ node (built executable, no .py extension)
        Node(
            package='fsbrt_ros2_2026',
            executable='velocity_logic',
            name='velocity_logic',
            output='screen',
            parameters=[config]
        ),
    ])
