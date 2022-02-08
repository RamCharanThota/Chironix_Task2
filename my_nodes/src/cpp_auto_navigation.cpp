#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "cpp_auto_navigation");

 
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise< geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);

 
   ros::Duration(5).sleep(); 
    geometry_msgs::PoseStamped msg;
    msg.header.frame_id ="map";
    msg.header.stamp=ros::Time::now();

    msg.pose.position.x=4;
    msg.pose.position.y=2;
    msg.pose.orientation.w=1;

   pub.publish(msg);
    


  return 0;
}
