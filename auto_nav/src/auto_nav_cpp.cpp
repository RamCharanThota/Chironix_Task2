#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int args, char **argv)
{

    ros ::init(args, argv, "auto_nav_cpp");

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0)))
    {
        ROS_INFO("waiting fot the move base action server to come up");
    }
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id="map";
    goal.target_pose.header.stamp=ros::Time::now();

    float goals[2][3]={{2,3,1},{5,6,1}};

    for (int i=0;i<2;i++){
        goal.target_pose.pose.position.x=goals[i][0];
        goal.target_pose.pose.position.y=goals[i][1];
        goal.target_pose.pose.orientation.w=1;
        
        ROS_INFO("Sending the goal");
        ac.sendGoal(goal);
        ac.waitForResult();
        ros::Duration(5.0).sleep();
    }

    if(ac.getState()==actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Hooray, reached drop off zone ");
    }
    else{
        ROS_INFO("The base failed to reaached the goal");
     }
       
    
    return 0;
        

}

