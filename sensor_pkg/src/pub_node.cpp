#include<ros/ros.h>
#include<std_msgs/Int16.h>
#include<my_msgs/RequestOfMove.h>
#include<my_msgs/SensorData.h>

enum heading{
    forward,
    left,
    right,
    stop
};
int headingTo = forward;

void NumberCallback(const my_msgs::SensorData &msg){

    if(msg.ultra_sonic_2)
        headingTo = right;

    if(msg.ultra_sonic_1 && msg.ultra_sonic_3){
        headingTo = stop;
    }else{
        if(msg.ultra_sonic_1)
            headingTo = right;
        else
            headingTo = left;
    }
}

int main(int argc, char** argv){
    ros::init(argc, argv, "pub_node");
    ros::NodeHandle nh;

    ros::Publisher pub_number = nh.advertise<my_msgs::RequestOfMove>("/Topic/Move",10);
    ros::Subscriber sub_number = nh.subscribe("/Topic/SensorData", 10, NumberCallback);

    ros::Rate loop_rate(1);
    my_msgs::RequestOfMove move;


    move.ML = 50;
    move.MR = 50;

    while(ros::ok()){
        
        switch(headingTo){
            case forward:
                move.ML = 50;
                move.MR = 50;
                break;
            case left:
                move.ML = -30;
                move.MR = 30;
                break;
            case right:
                move.ML = 30;
                move.MR = -30;
                break;
        }

        pub_number.publish(move);
        ROS_INFO("pub MR: %d ML: %d \n",move.MR, move.ML);

        ros::spinOnce();
        loop_rate.sleep();
    }
}
