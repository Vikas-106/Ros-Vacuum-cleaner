#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <cmath>

float x = 0.0;
float y = 0.0;
float z = 0.0;
void callback(const nav_msgs::Odometry::ConstPtr &msgs)
{
   x = msgs->pose.pose.position.x;
   y = msgs->pose.pose.position.y;
   z = msgs->pose.pose.position.z;
}

int main(int argc , char**argv)
{
    ros::init(argc, argv, "pathpublisher");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<visualization_msgs::Marker>("visualization_marker",10);
    ros::Subscriber sub = n.subscribe("odom",10,callback);
    ros::Rate rate(30);
  
        visualization_msgs::Marker line_strip,line_list;
        line_strip.header.frame_id = line_list.header.frame_id = "odom";
        line_list.header.stamp = line_strip.header.stamp = ros::Time::now();
        line_strip.ns = line_list.ns = "pathpublisher";
        line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
        line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;


        line_strip.id = 1;
        line_strip.id = 2;

        line_strip.type = visualization_msgs::Marker::LINE_STRIP;
        line_list.type = visualization_msgs::Marker::LINE_LIST;

        line_strip.scale.x = 0.1;
        line_list.scale.x = 0.1;

        line_list.color.r = 1.0;
        line_list.color.a = 1.0;

        line_strip.color.b = 1.0;
        line_strip.color.a = 1.0;
    while(ros::ok())
    {
      ros::spinOnce();
              geometry_msgs::Point p;
               p.x = x;
               p.y = y;
               p.z = z;
  
             line_strip.points.push_back(p);
             line_list.points.push_back(p);
        // The line list needs two points for each line
               p.x = x;
               p.y = y;
               p.z = z;
              line_list.points.push_back(p);

         pub.publish(line_strip);
         pub.publish(line_list);
  
         rate.sleep();  
    }

}