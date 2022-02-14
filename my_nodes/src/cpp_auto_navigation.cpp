#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string fname = "/home/rcbot/Chironix_Interview_Material/test2/catkin_ws/src/my_nodes/csv_files/goals.csv";

//ifstream ip (fname);

vector<vector<string>> read_goal_from_csv()
{
  std::vector<vector<string>> coordinates;
  std::vector<string> row;
  std::string line, coordinate;

  ifstream file(fname, ios::in);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      row.clear();

      std::stringstream str(line);

      while (getline(str, coordinate, ','))
      {
        row.push_back(coordinate);
      }

      coordinates.push_back(row);
    }
  }
  else
    cout << "----------- Could not open the file--------------------\n";

  return coordinates;
}

void RobotCurrentPositionCallBack(const nav_msgs::Odometry::ConstPtr &msg){

   //std::cout<<" x: "<< msg->pose.pose.position.x <<" y :"<<msg.pose.pose.position.y<<std::endl;
   ROS_INFO("robot position is x : %f  , y : %f", msg->pose.pose.position.x,msg->pose.pose.position.x);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "cpp_auto_navigation");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("move_base/goal", 1000);
  ros::Subscriber sub = n.subscribe("move_base/status", 1000, RobotCurrentPositionCallBack);

  //ros::Duration(5).sleep();
 // vector<vector<string>> goals = read_goal_from_csv();

  //for(vector<string> goal:goals){

 ros::Rate loop_rate(100);
  while (ros::ok())
  {
    geometry_msgs::PoseStamped msg;
    msg.header.frame_id = "map";
    msg.header.stamp = ros::Time::now();
    

    msg.pose.position.x = 2;
    msg.pose.position.y = 3;
    msg.pose.orientation.w = 1;

    vector<string> goal{"2","3"};

    ROS_INFO("coordinates from the csv file is x : %s, y : %s", goal[0].c_str(), goal[1].c_str());
    ros::Duration(5).sleep();

    pub.publish(msg);
    ///ros::spinOnce();
    ros::Duration(5).sleep();
    //loop_rate.sleep();
    //<!--include file="$(find husky_viz)/launch/view_robot.launch" --/>
  }

  //}

  return 0;
}
