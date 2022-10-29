/*
 * Mobile Robot
 *
 * Bring the cube to the Robot Arm
 *
 */

// Import libraries
#include <webots/motor.h>
#include <webots/robot.h>
#include <stdio.h>
#include <stdlib.h>

// Controller code
int main(int argc, char **argv) {
  wb_robot_init();
  
  // Set time step
  int time_step = (int)wb_robot_get_basic_time_step();
  
  // Instantiate motors
  WbDeviceTag left_motor, right_motor;
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  
  // Set initial positions and velocities
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  // Loop while simulation is running
  while (wb_robot_step(time_step) != -1) {
    
    // Get time step
    int robot_time = (int)wb_robot_get_time();
    
    //Bring the cube to the robot arm - from second 1
    if (robot_time == 1){
      wb_motor_set_velocity(left_motor, 3.0);
      wb_motor_set_velocity(right_motor, 3.0);
    }
    
    //Stop and wait the robot arm to pick the cube - from second 12
    if (robot_time == 12){
      wb_motor_set_velocity(left_motor, 0.0);
      wb_motor_set_velocity(right_motor, 0.0);
    }
    
    //Return to initial position - from second 17
    if (robot_time == 17){
      wb_motor_set_velocity(left_motor, -3.0);
      wb_motor_set_velocity(right_motor, -3.0);
    }
    
    //Stop to end simulation - at second 28
    if (robot_time == 28){
      wb_motor_set_velocity(left_motor, 0.0);
      wb_motor_set_velocity(right_motor, 0.0);
      break;
    }
    
  };
  
  // End simulation
  wb_robot_cleanup();
  return EXIT_SUCCESS;
}
