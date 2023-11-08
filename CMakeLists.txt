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
add_executable(S_pattern src/S_pattern.cpp)
target_link_libraries(S_pattern ${catkin_LIBRARIES})
add_executable(spiral src/spiral.cpp)
target_link_libraries(spiral ${catkin_LIBRARIES})