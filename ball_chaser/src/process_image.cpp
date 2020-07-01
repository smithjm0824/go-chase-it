#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

//Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction

void drive_robot(float lin_x, float ang_z){
    ROS_INFO_STREAM("Chasing the ball.");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv)) {
        ROS_ERROR("Failed to call service command_robot.");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img){ 
    int white_pixel = 255;
    int left = 0;
    int middle = 0;
    int right = 0;

    for (int i = 0; i < img.height * img.step; i += 3){
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel & img.data[i+2] == white_pixel) {
            int section = i % img.step;

            if (section >= 0 && section < img.step / 3){
                left ++;
            } else if (section >= img.step / 3 && section < img.step * 2/3) {
                middle++;
            } else {
                right ++;
            }
        }
    }

    if (left > middle && left > right) {
        drive_robot(0.25, 0.5);
    } else if (middle > left && middle > right) {
        drive_robot(0.25, 0);
    } else if (right > left && right > middle) {
        drive_robot(0.25, -0.5);
    } else {
        drive_robot(0, 0.5);
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    ros::spin();

    return 0;
}