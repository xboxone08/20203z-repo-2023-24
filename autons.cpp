#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

#define DEGREE_TO_RADIANS(x) ((x) * 180.0 / 3.14159)

void defensive_side_1(){
  int scale = 80;
  // int turnScaler = 10;
  L1.setVelocity(scale, percent);
  L2.setVelocity(scale, percent);
  L3.setVelocity(scale, percent);
  R1.setVelocity(scale, percent);
  R2.setVelocity(scale, percent);
  R3.setVelocity(scale, percent);
  // Poop.calibrate();

  chassis.set_heading(0);
  
  Wing1.set(false);
  chassis.drive_distance(6);
  Wing1.set(true);
  
  // chassis.set_turn_constants(8.0, 0.08, 1.0, 0.05, 0.0);
  // chassis.set_turn_exit_conditions(0.5, 500, 3000);
  // chassis.turn_to_angle(180);
  
  chassis.set_swing_constants(8.0, 0.2, 1.0, 0.03, 0.0);
  chassis.set_swing_exit_conditions(1.0, 500, 1000);
  chassis.left_swing_to_angle(45);
  chassis.turn_to_angle(27);
  
  Wing1.set(false);
  chassis.drive_distance(25);

  chassis.drive_distance(-25);
  chassis.left_swing_to_angle(320);
  chassis.drive_distance(-43);
  Lift.spin(forward);
  Intake.spin(forward);
  wait(500,msec);
  Lift.stop();
  Intake.stop();
}

void offensive_side_1(){
  Intake.setVelocity(100, percent);

  chassis.set_turn_constants(8.0, 0.08, 1.0, 0.05, 0.0);
  chassis.set_turn_exit_conditions(0.5, 500, 3000);

  chassis.set_swing_constants(8.0, 0.2, 1.0, 0.03, 0.0);
  chassis.set_swing_exit_conditions(1.0, 500, 1000);

  // Intake middle tri-ball
  chassis.right_swing_to_angle(10);
  chassis.drive_distance(60);
  Lift.spin(forward);
  Intake.spin(forward);
  chassis.drive_distance(10);
  wait(500,msec);
  Lift.stop();
  Intake.stop();

  // Score middle and front tri-balls
  chassis.set_turn_constants(5.0, 0.08, 1.0, 0.05, 0.0);
  chassis.set_turn_exit_conditions(0.5, 500, 3000);
  chassis.turn_to_angle(135);
  Wing1.set(true);
  Lift.spin(reverse);
  Intake.spin(reverse);
  chassis.drive_distance(28);
  Intake.stop();
  Lift.stop();
  chassis.drive_distance(-12);
  chassis.drive_distance(15);
}
