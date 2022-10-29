/*
 * Robot arm
 * 
 * Pick the cube to drop it in a box
 *
 */
 
// Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <webots/motor.h>
#include <webots/robot.h>

// Set variable for the time step
static int time_step;

// Wait for <sec> seconds
static void wait_time(double sec) {
  double initial_time = wb_robot_get_time();
  do
    if (wb_robot_step(time_step) == -1) {
      wb_robot_cleanup();
      exit(EXIT_SUCCESS);
    }
  while (initial_time + sec > wb_robot_get_time());
}

// Controller code
int main(int argc, char **argv) {
  wb_robot_init();
  
  // Get time step
  time_step = (int)wb_robot_get_basic_time_step();

  // Instantiate motors
  WbDeviceTag motors[7];
  WbDeviceTag gripper[3];
  motors[1] = wb_robot_get_device("joint_1");
  motors[2] = wb_robot_get_device("joint_2");
  motors[3] = wb_robot_get_device("joint_3");
  gripper[1] = wb_robot_get_device("joint_base_to_jaw_1");
  gripper[2] = wb_robot_get_device("joint_base_to_jaw_2");

  // Set initial position for each joint
  wb_motor_set_position(motors[1], 0.0);
  wb_motor_set_position(motors[2], 0.0);
  wb_motor_set_position(motors[3], 0.0);
  wb_motor_set_position(gripper[1], 0.0);
  wb_motor_set_position(gripper[2], 0.0);

  // Loop while simulation is running
  while (wb_robot_step(time_step) != -1) {
    
    // Set the motor velocity - unit is radian/second
    wb_motor_set_velocity(motors[1], 0.5);
    wb_motor_set_velocity(motors[2], 0.5);
    wb_motor_set_velocity(motors[3], 0.5);
    wb_motor_set_velocity(gripper[1], 1.0);
    wb_motor_set_velocity(gripper[2], 1.0);
  
    // Wait 12s for mobile robot to arrive
    wait_time(12.0);
    
    //Lower the arm
    wb_motor_set_position(motors[2], 0.5);
    wb_motor_set_position(motors[3], 0.6);
    wb_motor_set_position(gripper[1], 0.01);
    wb_motor_set_position(gripper[2], 0.01);
    wait_time(2.0);
    
    //Pick the cube
    wb_motor_set_position(gripper[1], 0.0);
    wb_motor_set_position(gripper[2], 0.0);
    wait_time(1.0);
    
    //Raise the arm
    wb_motor_set_position(motors[2], 0.0);
    wb_motor_set_position(motors[3], 0.0);
    wait_time(0.5);
    
    // Turn to the side
    wb_motor_set_position(motors[1], -1.6);
    wait_time(3.0);
    
    // Lower arm to the side
    wb_motor_set_position(motors[2], 0.35);
    wb_motor_set_position(motors[3], 0.35);
    wait_time(2.0);
    
    //Drop the cube
    wb_motor_set_position(gripper[1], 0.01);
    wb_motor_set_position(gripper[2], 0.01);
    wait_time(2.0);
    
    //Reset position
    wb_motor_set_position(motors[2], 0.0);
    wb_motor_set_position(motors[3], 0.0);
    wait_time(2.0);
    wb_motor_set_position(motors[1], 0.0);
    wb_motor_set_position(gripper[1], 0.0);
    wb_motor_set_position(gripper[2], 0.0);
    wait_time(3.5);
    break;
    
  }
  
  // End simulation
  wb_robot_cleanup();
  return 0;
}
