#include"ros/ros.h"
#include"geometry_msgs/Twist.h"
#include"geometry_msgs/Pose2D.h"
#include "nav_msgs/Odometry.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include<math.h>
double pi=M_PI;
double qx,qy,qw,qz,currentx,currenty,yaw,dist,theta,waypointx, waypointy,x,y,goalx, goaly;
bool a=true;
bool b=true;
geometry_msgs::Twist velCommand;
void goals(int i, int j){
   goalx =i;
   goaly =j;
}
void callback(const nav_msgs::Odometry::ConstPtr &msg){
 currentx=msg->pose.pose.position.x;
 currenty=msg->pose.pose.position.y;

 qx=msg->pose.pose.orientation.x;
 qy=msg->pose.pose.orientation.y;
 qz=msg->pose.pose.orientation.z;
 qw=msg->pose.pose.orientation.w;
 tf2::Quaternion quat(qx, qy, qz, qw);
  tf2::Matrix3x3 mat(quat);
  double roll, pitch;
  mat.getRPY(roll, pitch, yaw);
}
double getHeadingError() {
  double x1 = goalx - currentx;
  double y1 = goaly - currenty;
  theta = atan2(y1, x1);
  dist= sqrt(pow(x1, 2) + pow(y1, 2));
  double headingError =  theta -yaw;   
  
  if (headingError > pi) {
    headingError = headingError - (2 * pi);
  } 
  if (headingError < -pi) {
    headingError = headingError + (2 * pi);
  } 
   
  return headingError;
}
void setVelocity() {
  double error=getHeadingError();
   if(a==true && abs(dist)>0.1){
      if (abs(error) > 0.1) {
      velCommand.linear.x = 0.0;
      velCommand.angular.z = 0.5*error;
    }
    else {
      velCommand.linear.x = 0.3;
      velCommand.angular.z = 0.0;    
    }
   }
  else {
    std::cout << "Goal has been reached!" << std::endl << std::endl;
    velCommand.linear.x = 0.0;
    velCommand.angular.z = 0.0; 
    b=true;
}
}
int main(int argc, char** argv){
  ros::init(argc, argv,"forwardnode");
  ros::NodeHandle n;
  ros::Subscriber sub=n.subscribe("odom",10,callback);
  ros::Publisher pub= n.advertise<geometry_msgs::Twist>("cmd_vel",10);
  double currentGoalY=0;
  double currentGoalX=0;
  int gridSize=3;  // grid size to cover
  ros::Rate loop_rate(10);
  
while(ros::ok()){
  
   ros::spinOnce();
    if (b) {
            goals(currentGoalX, currentGoalY);
            b = false; // Set the flag to indicate the goal is set
        }
            setVelocity();
            pub.publish(velCommand);
            std::cout<<"your x,y-location = "<<currentx<<" ,"<<currenty<<std::endl;
            std::cout<<"your theta = "<<yaw<<std::endl;
            std::cout<<"your desired theta = "<< theta<<std::endl;
            std::cout<<"your goal = "<<goalx<<" "<<goaly<<std::endl;

   if (abs(dist) <= 0.1) {
            currentGoalY++; //can change the distance between each goal 
            if (currentGoalY > gridSize) {
                currentGoalY = 0;
                currentGoalX++;  // can change the distance between each goal 
                if (currentGoalX > gridSize) {
                    currentGoalX = 0;
                }

            }
            b = true; // Set the flag to indicate the goal is reached
        }
        
   loop_rate.sleep();
}
}