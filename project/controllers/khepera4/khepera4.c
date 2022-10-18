/*
 * Mobile Robot
 *
 * Brings the cube to the Robot Arm
 *
 */

#include <webots/motor.h>
#include <webots/robot.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SPEED 47.6

int main(int argc, char **argv) {
  wb_robot_init();

  int time_step = (int)wb_robot_get_basic_time_step();
  
  // get the motors and set target position to infinity (speed control)
  WbDeviceTag left_motor, right_motor;
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  // main loop
  while (wb_robot_step(time_step) != -1) {
  
    int robot_time = (int)wb_robot_get_time();
    
    //Bring the cube to the robot arm
    if (robot_time == 1){
      wb_motor_set_velocity(left_motor, 3.0);
      wb_motor_set_velocity(right_motor, 3.0);
    }
    
    //Stop and wait the robot arm to pick the cube
    if (robot_time == 12){
      wb_motor_set_velocity(left_motor, 0.0);
      wb_motor_set_velocity(right_motor, 0.0);
    }
    
    //Return to initial position
    if (robot_time == 17){
      wb_motor_set_velocity(left_motor, -3.0);
      wb_motor_set_velocity(right_motor, -3.0);
    }
    
    //Stop to end simulation
    if (robot_time == 28){
      wb_motor_set_velocity(left_motor, 0.0);
      wb_motor_set_velocity(right_motor, 0.0);
      break;
      
    }
    
  };
  
  wb_robot_cleanup();

  return EXIT_SUCCESS;
}
