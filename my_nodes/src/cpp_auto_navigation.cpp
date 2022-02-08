#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <sstream>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


std::string fname="/home/rcbot/Chironix_Interview_Material/test2/catkin_ws/src/my_nodes/csv_files/goals.csv";

vector<vector<string>> read_goal_from_csv()
{
  std::vector<vector<string>> content;
  std::vector<string> row;
  std::string line, word;

  fstream file(fname, ios::in);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      row.clear();

      std::stringstream str(line);

      while (getline(str, word, ','))
       row.push_back(word);

      content.push_back(row);
    }
  }
  else
    cout << "Could not open the file\n";

    return content;
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "cpp_auto_navigation");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);

  //ros::Duration(5).sleep();
  std::vector<std::vector<string>>goals=read_goal_from_csv();

  for(std::vector<string> goal:goals){
     geometry_msgs::PoseStamped msg;
    msg.header.frame_id = "map";
    msg.header.stamp = ros::Time::now();
   
   // msg.pose.position.x = goal[0];
    //msg.pose.position.y = goal[1];
    //msg.pose.orientation.w = 1;

    std::cout<<" x:"<<goal[0]<<" y:"<<goal[1]<<" "<<std::endl;

    //pub.publish(msg);

  }
 

 

  return 0;
}


