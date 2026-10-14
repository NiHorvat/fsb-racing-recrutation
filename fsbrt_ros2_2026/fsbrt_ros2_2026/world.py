#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import os
from pathlib import Path

"""
Author: Matej Lovreković & Luka Bradarić-Lisić

FSBRT Autonomous - Recruitment task

Script that loads the track from .csv file to python list
"""


def _resolve_src_dir():
    """
    Locate the directory that holds the track .csv files.

    In ROS2 this module is installed into the package's site-packages, so the
    old "../src" relative path no longer works. We first try the installed
    share directory (where CMakeLists.txt installs the csv files), then fall
    back to the source-tree layout for running uninstalled.
    """
    # 1) Installed location: <prefix>/share/fsbrt_ros2_2026/src
    try:
        from ament_index_python.packages import get_package_share_directory
        share_src = os.path.join(
            get_package_share_directory("fsbrt_ros2_2026"), "src")
        if os.path.isdir(share_src):
            return share_src
    except Exception:
        pass

    # 2) Source-tree fallback: <pkg>/src
    curr_dir_path = Path(os.path.dirname(os.path.realpath(__file__)))
    candidates = [
        str(curr_dir_path.parent.absolute()) + "/src",
        str(curr_dir_path.parent.parent.absolute()) + "/src",
    ]
    for c in candidates:
        if os.path.isdir(c):
            return c

    # 3) Last resort: original relative layout
    return str(curr_dir_path.parent.absolute()) + "/src"


src_dir_path = _resolve_src_dir()


def read_csv_points(file_name: str):

    """
    Function that reads .csv file and makes a list of tuples that represents points of a track.
    """

    temp_list = []
    with open(os.path.join(src_dir_path, file_name), "r") as csv_points:
        for line in csv_points.readlines():
            temp_list.append(tuple(map(float, line.rstrip().split(","))))
    return temp_list


outer_points = read_csv_points("outer_track.csv")
inner_points = read_csv_points("inner_track.csv")
central_trajectory = read_csv_points("central_trajectory.csv")
