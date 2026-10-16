from setuptools import find_packages
from setuptools import setup

setup(
    name='fsbrt_ros2_2026',
    version='0.0.0',
    packages=find_packages(
        include=('fsbrt_ros2_2026', 'fsbrt_ros2_2026.*')),
)
