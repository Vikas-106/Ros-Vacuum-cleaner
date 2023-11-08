#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf/transform_datatypes.h>
#include <math.h>

double pi = M_PI;
double currentx, currenty, qx, qy, qz, qw, yaw;
double dist, min , add; 
double degree = 90 * pi/180;
ros::Publisher pub;
geometry_msgs::Twist cmd;
bool flag = true;
double speed = 0.3;

void callback(const nav_msgs::Odometry::ConstPtr &msg) {
    currentx = msg->pose.pose.position.x;
    currenty = msg->pose.pose.position.y;
    dist = sqrt(pow(currentx,2)+pow(currenty,2));

    qx = msg->pose.pose.orientation.x;
    qy = msg->pose.pose.orientation.y;
    qz = msg->pose.pose.orientation.z;
    qw = msg->pose.pose.orientation.w;

    tf2::Quaternion quat(qx, qy, qz, qw);
    tf2::Matrix3x3 mat(quat);
    double roll, pitch;
    mat.getRPY(roll, pitch, yaw);
}

double normalizeAngle(double angle) {
    return atan2(sin(angle), cos(angle));  // makes the radian fall into the range -180 to 180
}

void turn() {

    if (abs(degree - yaw) > 0.05) {
        cmd.angular.z = 0.3;
        pub.publish(cmd);
    } else {
        cmd.angular.z = 0.0;
        pub.publish(cmd);
        min += add;
        degree = normalizeAngle(degree+= 90*M_PI/180);
    }
}

void move() {
    if (dist < min) {  
        cmd.linear.x = speed;
        pub.publish(cmd);
    } else {
        cmd.linear.x = 0;
        pub.publish(cmd);
        turn();
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "spiral");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("odom", 10, callback);
    pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    ros::Rate loop_rate(10);

    while (ros::ok()) {
        ros::spinOnce();
        if(flag)
        {
            std::cout<<"Enter your initial distance : ";
            std::cin>>min;
            std::cout<<"Enter your dist to be increased : ";
            std::cin>>add;
            std::cout<<std::endl;
            flag = false;
        }
        move();
        std::cout << "distance moved is : " << dist << std::endl;
        std::cout<< " current radian : "<<yaw<<std::endl;
        std::cout<<"  radian to be turned  :" <<degree<<std::endl;
        loop_rate.sleep();
    }

    return 0;
}
