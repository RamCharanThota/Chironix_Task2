#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


string fname = "/home/rcbot/Chironix_Interview_Material/test2/catkin_ws/src/my_nodes/csv_files/goals.csv";

//ifstream ip (fname);
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

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

int main(int args, char **argv)
{

    ros ::init(args, argv, "auto_nav_cpp");

    MoveBaseClient ac("move_base", true);

    while (!ac.waitForServer(ros::Duration(5.0)))
    {
        ROS_INFO("waiting fot the move base action server to come up");
    }
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    vector<vector<string>> goals= read_goal_from_csv();

    for (vector<string> goal_cor:goals)
    {
        goal.target_pose.pose.position.x = stof(goal_cor[0]);
        goal.target_pose.pose.position.y =  stof(goal_cor[1]);
        goal.target_pose.pose.orientation.w = 1;

        ROS_INFO("Sending the goal");
        ac.sendGoal(goal);
        ac.waitForResult();
        ros::Duration(5.0).sleep();
    }

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("Hooray, reached drop off zone ");
    }
    else
    {
        ROS_INFO("The base failed to reaached the goal");
    }

    return 0;
}
