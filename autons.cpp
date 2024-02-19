#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 3000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

#define DEGREE_TO_RADIANS(x) ((x) * 180.0 / 3.14159)

// Quals
void defensive_side_1(){
  int scale = 80;
  // int turnScaler = 10;
  L1.setVelocity(scale, percent);
  L2.setVelocity(scale, percent);
  L3.setVelocity(scale, percent);
  //L3.setVelocity(scale, percent);
  R1.setVelocity(scale, percent);
  R2.setVelocity(scale, percent);
  R3.setVelocity(scale, percent);
  //R3.setVelocity(scale, percent);
  // Poop.calibrate();

  
  chassis.set_heading(0);
  // LEFT SWING
  chassis.set_swing_constants(9.0, 0.12, 0.0, 0.0, 0.0);
  // RIGHT SWING
  chassis.set_swing_constants(9.0, 0.145, 0.0, 0.0, 0.0);
  chassis.set_swing_exit_conditions(0.5, 500, 500);

  chassis.set_turn_constants(9.0, 0.09, 0.0, 0.15, 0.0);
  chassis.set_turn_exit_conditions(0.5, 500, 500);
  chassis.set_drive_constants(10.0, 1.5, 0, 10, 0);

  chassis.right_swing_to_angle(315);
  Wings.set(true);
  chassis.turn_to_angle(225);
  Wings.set(false);
  chassis.right_swing_to_angle(270);
  chassis.drive_distance(-6);

  chassis.turn_to_angle(170);
  chassis.turn_to_angle(45);

  Intake.spin(reverse);
  chassis.drive_distance(18);
}


void defensive_side_2(){
  int scale = 80;
  // int turnScaler = 10;
  L1.setVelocity(scale, percent);
  L2.setVelocity(scale, percent);
  L3.setVelocity(scale, percent);
  //L3.setVelocity(scale, percent);
  R1.setVelocity(scale, percent);
  R2.setVelocity(scale, percent);
  R3.setVelocity(scale, percent);
  //R3.setVelocity(scale, percent);
  // Poop.calibrate();
  
  chassis.set_heading(0);
  // LEFT SWING
  chassis.set_swing_constants(9.0, 0.12, 0.0, 0.0, 0.0);
  // RIGHT SWING
  chassis.set_swing_constants(9.0, 0.145, 0.0, 0.0, 0.0);
  chassis.set_swing_exit_conditions(0.5, 500, 500);

  chassis.set_turn_constants(9.0, 0.09, 0.0, 0.15, 0.0);
  chassis.set_turn_exit_conditions(0.5, 500, 2000);
  chassis.set_drive_constants(10.0, 1.5, 0, 10, 0);

  Wings.set(true);
  wait(500,msec);
  Wings.set(false);

  chassis.drive_distance(30);
  Wings.set(true);
  chassis.left_swing_to_angle(50);
  wait(100,msec);
  chassis.drive_distance(-5);
  chassis.set_swing_constants(9.0, 0.12, 0.0, 0.0, 0.0);
  chassis.left_swing_to_angle(350);
  chassis.drive_distance(-10);

  Wings.set(false);
  chassis.drive_distance(-32);

}

void offensive_side_1(){
   int scale = 80;
  // int turnScaler = 10;
  L1.setVelocity(scale, percent);
  L2.setVelocity(scale, percent);
  L3.setVelocity(scale, percent);
  //L3.setVelocity(scale, percent);
  R1.setVelocity(scale, percent);
  R2.setVelocity(scale, percent);
  R3.setVelocity(scale, percent);
  //R3.setVelocity(scale, percent);
  // Poop.calibrate();
  
  chassis.set_heading(0);
  chassis.set_heading(0);
  // LEFT SWING
  chassis.set_swing_constants(9.0, 0.12, 0.0, 0.0, 0.0);
  // RIGHT SWING
  chassis.set_swing_constants(9.0, 0.145, 0.0, 0.0, 0.0);
  chassis.set_swing_exit_conditions(0.5, 500, 500);

  chassis.set_turn_constants(9.0, 0.09, 0.0, 0.15, 0.0);
  chassis.set_turn_exit_conditions(0.5, 500, 500);
  chassis.set_drive_constants(9.0, 1.5, 0, 10, 0);

  Intake.spin(forward);

  chassis.drive_distance(-22);
  chassis.left_swing_to_angle(90);
  Intake.spin(forward);
  chassis.drive_distance(16);
  chassis.drive_distance(-7);
  chassis.turn_to_angle(180);
  chassis.drive_distance(7);
  //Wings.set(true);
  chassis.left_swing_to_angle(270);
  Wings.set(true);
  Intake.spin(reverse);
  chassis.set_drive_constants(12.0, 1.5, 0, 10, 0);
  chassis.drive_distance(25);
  chassis.set_drive_constants(10.0, 1.5, 0, 10, 0);
  chassis.drive_distance(-10);
  Wings.set(false);
  chassis.turn_to_angle(165);
  Intake.spin(forward);
  chassis.drive_distance(6);
  chassis.turn_to_angle(90);
  chassis.drive_distance(10);
  wait(2,msec);
  chassis.drive_distance(-6);
  chassis.turn_to_angle(290);
  Intake.spin(reverse);
  chassis.drive_distance(8);
  Wings.set(true);
  chassis.drive_distance(6);
  chassis.drive_distance(-6);

  



}

void skills(){
  int scale = 80;
  // int turnScaler = 10;
  L1.setVelocity(scale, percent);
  L2.setVelocity(scale, percent);
  L3.setVelocity(scale, percent);
  //L3.setVelocity(scale, percent);
  R1.setVelocity(scale, percent);
  R2.setVelocity(scale, percent);
  R3.setVelocity(scale, percent);
  //R3.setVelocity(scale, percent);
  // Poop.calibrate();
  
  //chassis.set_heading(0);
  chassis.set_heading(0);
  // LEFT SWING
  chassis.set_swing_constants(9.0, 0.12, 0.0, 0.0, 0.0);
  // RIGHT SWING
  chassis.set_swing_constants(9.0, 0.145, 0.0, 0.0, 0.0);
  chassis.set_swing_exit_conditions(0.5, 500, 500);

  chassis.set_turn_constants(9.0, 0.09, 0.0, 0.15, 0.0);
  chassis.set_turn_exit_conditions(0.5, 500, 500);

  chassis.set_drive_constants(12.0, 2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1500);

  // Shooter.spin(forward);
  chassis.right_swing_to_angle(315);
  chassis.turn_to_angle(20);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-6);
  chassis.set_drive_exit_conditions(1.5, 300, 1500);
  Shooter.spin(reverse);
   wait(35.1,sec);
  Shooter.stop();
  chassis.turn_to_angle(0);
  chassis.drive_distance(-3);
  chassis.drive_distance(3);
  chassis.turn_to_angle(330.0);
  Intake.spin(reverse);
  chassis.drive_distance(22);
  chassis.turn_to_angle(45);
  chassis.set_drive_constants(12.0, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 4000);
  chassis.drive_distance(80);
  chassis.set_drive_exit_conditions(1.5, 300, 1500);
  chassis.set_drive_constants(12.0, 1.5, 0, 10, 0);
  chassis.drive_distance(-5);
  Wings.set(true);
  chassis.turn_to_angle(35 );
  chassis.drive_distance(30);
  Wings.set(false);
  chassis.drive_distance(-20);
  Wings.set(false);
  chassis.drive_distance(4);
  chassis.turn_to_angle(305);
  chassis.drive_distance(19);
  Wings.set(true);
  chassis.turn_to_angle(64);
  Wings.set(true);
  chassis.drive_distance(30);
  chassis.drive_distance(-30);
  chassis.drive_distance(30);
    chassis.drive_distance(-30);
     chassis.drive_distance(-30);
  chassis.drive_distance(30);
    chassis.drive_distance(-30);
}
