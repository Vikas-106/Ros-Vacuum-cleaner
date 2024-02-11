#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<sensor_msgs/LaserScan.h>
#include<vector>

geometry_msgs::Twist cmd;
ros::Publisher pub ;

void callback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
   char state ;
   int total_points = msg->ranges.size();
   std::vector<float> data = msg->ranges;


int front_start = total_points / 2 - 30;  
int front_end = total_points /2 + 30;   

int right_start = 0;       
int right_end = total_points / 4 ;  

int left_start = total_points * 3 / 4  ; 
int left_end = total_points - 1;  

std::vector<double> front_data(msg->ranges.begin() + front_start, msg->ranges.begin() + front_end);
std::vector<double> right_data(msg->ranges.begin() + right_start, msg->ranges.begin() + right_end);
std::vector<double> left_data(msg->ranges.begin() + left_start, msg->ranges.begin() + left_end);

 double front = *std::min_element(front_data.begin(),front_data.end());
 double left = *std::min_element(left_data.begin(),left_data.end());
 double right = *std::min_element(right_data.begin(),right_data.end());
 double d = 1;
    
    if (front > d && left > d && right > d)
        {
          cmd.linear.x = 0.3;
          cmd.angular.z = 0.0;
          pub.publish(cmd);
        }
    else if( front < d and left > d && right > d)
        {
          cmd.linear.x = 0.0;
          cmd.angular.z = 0.2;
          pub.publish(cmd);
        }
    else if (front > d && left > d && right < d)
        {
          cmd.linear.x = 0.3;
          cmd.angular.z = 0.0;
          pub.publish(cmd);
        }
    
    else if (front > d && left < d && right > d)
         {
            cmd.linear.x = 0.3;
            cmd.angular.z = 0.0;
            pub.publish(cmd);
         }
    else if (front < d && left > d && right < d)
         {
            cmd.linear.x = 0.0;
            cmd.angular.z = 0.3;
            pub.publish(cmd);
         }
    else if (front < d && left < d && right > d)
          {
            cmd.linear.x = 0.0;
            cmd.angular.z = 0.3;
            pub.publish(cmd);
          }
    else if (front < d && left < d && right < d)
         {
            cmd.linear.x = 0.0;
            cmd.angular.z = 0.3;
            pub.publish(cmd);
         }
    else if (front > d && left < d && right < d)
        {
            cmd.linear.x = 0.3;
            cmd.angular.z = 0.0;
            pub.publish(cmd);
        }

}

int main(int argc, char** argv)
{
    ros::init(argc, argv ,"wallfollower");
    ros::NodeHandle n;
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Subscriber sub = n.subscribe("/scan",10,callback);
    ros::spin();
}