cmake_minimum_required(VERSION 3.0.2)
project(point_in_polygon_lib)

find_package(catkin REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES point_in_polygon_lib
)

###########
## Build ##
###########

include_directories(
  include
)

add_library(point_in_polygon_lib src/point_in_polygon.cpp)
target_compile_options(point_in_polygon_lib PUBLIC -std=c++17 -O3 -Wall)

#############
## Install ##
#############

install(TARGETS point_in_polygon_lib
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
