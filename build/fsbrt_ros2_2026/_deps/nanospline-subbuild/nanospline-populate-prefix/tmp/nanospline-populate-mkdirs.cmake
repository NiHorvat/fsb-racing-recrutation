# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-src"
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-build"
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix"
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix/tmp"
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix/src/nanospline-populate-stamp"
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix/src"
  "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix/src/nanospline-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix/src/nanospline-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/nh-laptop/FSB-racing/task/build/fsbrt_ros2_2026/_deps/nanospline-subbuild/nanospline-populate-prefix/src/nanospline-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
