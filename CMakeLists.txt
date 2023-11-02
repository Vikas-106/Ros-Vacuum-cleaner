cmake_minimum_required(VERSION 3.0.2)
project(vacuum_cleaner)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(

)

include_directories(

  ${catkin_INCLUDE_DIRS}
)

add_executable(obstacleavoider src/obstacleavoider.cpp)
target_link_libraries(obstacleavoider ${catkin_LIBRARIES})
add_executable(wallfollower src/wallfollower.cpp)
target_link_libraries(wallfollower ${catkin_LIBRARIES})
