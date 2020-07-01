# go-chase-it
Contains 2 ROS packages - one to process camera input, and another to actuate the robot.

## Purpose
This repository utilizes the Robot Operating System to create a simulated world in which a robot chases a white ball.

## Contents
### ball_chaser  

  
The ball_chaser package conatins two ROS nodes (drive_bot & process_image) that communicate with the robot and provide commands.
* drive_bot: implements a service that takes linear_x and angular_z values to send to the robot's motors
* process_image: implements a service that analyzes a camera onboard the robot to determine what action the robot should take
