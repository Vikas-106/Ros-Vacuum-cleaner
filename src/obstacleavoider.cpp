#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<sensor_msgs/LaserScan.h>

ros::Publisher pub;
geometry_msgs::Twist cmd;

void callback(const sensor_msgs::LaserScan::ConstPtr& msg)
{

  std::vector<float> data = msg->ranges;
  
  for (auto i = data.begin(); i != data.end(); i++)
  {
     std::cout<<*i<<std::endl;
    //  if(*i <=1 ){
    //   cmd.linear.x = 0;
    //   cmd.angular.z = 0.3;
    //   pub.publish(cmd);
    //  }
    //  else{
    //   cmd.linear.x = 0.4;
    //   cmd.angular.z = 0;
    //   pub.publish(cmd);
    //  }
  }

}

int main(int argc,char** argv)
{
    ros::init(argc, argv, "obstacleavoid");
    ros::NodeHandle n;
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Subscriber sub = n.subscribe("/scan",10,callback);
    ros::spin();
}