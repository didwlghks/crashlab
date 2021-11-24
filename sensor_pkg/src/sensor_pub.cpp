#include<ros/ros.h>
#include<std_msgs/Int16.h>
#include<my_msgs/SensorData.h>
#include<cstdlib>

int main(int argc, char** argv){
    ros::init(argc, argv, "sensor_pub");
    ros::NodeHandle nh;

    ros::Publisher pub_number = nh.advertise<my_msgs::SensorData>("/Topic/SensorData",10);

    ros::Rate loop_rate(1);
    my_msgs::SensorData sensor_data;

    std::srand(123);

    while(ros::ok()){
        sensor_data.ultra_sonic_1 = false;
        sensor_data.ultra_sonic_2 = false;
        sensor_data.ultra_sonic_3 = false;
        sensor_data.ultra_sonic_4 = false;
        sensor_data.ultra_sonic_5 = false;
        sensor_data.ultra_sonic_6 = false;
        sensor_data.is_card_checked = false;

        ROS_INFO("publish sensor_data\n");
        pub_number.publish(sensor_data);
        //ROS_INFO("pub speed: %d degree: %d \n",move.speed, move.degree);

        ros::spinOnce();
        loop_rate.sleep();
    }
}
