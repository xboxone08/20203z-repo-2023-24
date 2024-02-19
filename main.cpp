#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L1                   motor         12              
// R1                   motor         10              
// R2                   motor         9               
// Poop                 inertial      13              
// L2                   motor         19              
// Controller1          controller                    
// R3                   motor         15              
// L3                   motor         20              
// Intake               motor         8               
// Wings                digital_out   A               
// Balance              digital_out   B               
// Climb                digital_out   F               
// Shooter              motor         17              
// ShooterSensor        rotation      16              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

typedef enum
{
    LIFT_STATE_AT_ZERO = 0,
    LIFT_STATE_AT_GRAB,
    LIFT_STATE_AT_READY,
    LIFT_STATE_AT_LAUNCH,
    LIFT_STATE_MOVING_UP,
    LIFT_STATE_MOVING_DOWN,
    LIFT_STATE_MOVING_TO_ZERO
} lift_state_t;

// #define LIFT_POSITION_ZERO        0.0  // Lift is resting on the switch
// #define LIFT_POSITION_GRAB      100.0  // Lift is grabbing a ball
// #define LIFT_POSITION_READY     240.0  // Lift is ready to grab a ball
// #define LIFT_POSITION_LAUNCH    600.0  // Lift is ready for match loading


/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(L1, L2, L3),

//Right Motors:
motor_group(R1, R2, R3),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT13,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.75,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1.0,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360.0,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
7,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;
int shoot = 0;
bool shooterRecovering = true;
bool released_ = true;

void pre_auton(void) {
  chassis.set_heading(0);
  Intake.setVelocity(100, percent);
  
  Shooter.setVelocity(100, percent);
  Shooter.setStopping(hold);
  //ShooterSensor.setPosition(0, degrees);
  Wings.set(false);
  Climb.set(false);
  //Lock.set(false);
  
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(auto_started == false) {            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(50, 50, "Defensive Side 1");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Defensive Side 2");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Offensive Side 1");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "skills");
        break;
    }
    if(Brain.Screen.pressing()) {
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 4) {
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection) {
    case 0:
      defensive_side_1(); //This is the default auton, if you don't select from the brain.
      break;        //Change these to be your own auton functions in order to use the auton selector.
    case 1:         //Tap the screen to cycle through autons.
      defensive_side_2();
      break;
    case 2:         //Tap the screen to cycle through autons.
      offensive_side_1();
      break;
    case 3:         //Tap the screen to cycle through autons.
      skills();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void usercontrol(void) {
  Climb.set(false);
  Balance.set(false);

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();

    
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.

    if (Controller1.ButtonR1.pressing())
    {
      Intake.spin(forward);
    }
    else if (Controller1.ButtonR2.pressing())
    {
      Intake.spin(reverse);
    }
    else
    {
      Intake.stop();                                                                           
    }

    if (Controller1.ButtonL1.pressing())
    {
      Wings.set(true);
      // WingD.set(true);
    }
    else
    {
      Wings.set(false);
      // WingD.set(false);
    }

    if (Controller1.ButtonUp.pressing()) 
    {
      Climb.set(false);
    } 
    else if (Controller1.ButtonDown.pressing()) 
    {
      Climb.set(true);
    } 
    if (Controller1.ButtonX.pressing()) 
    {
      Balance.set(true);
    } 
    else if (Controller1.ButtonB.pressing()) 
    {
      Balance.set(false);
    } 
         
    if (shooterRecovering) {
      if (ShooterSensor.angle() < 60.0) {
        Shooter.spin(reverse);
      } else {
        Shooter.stop();
        shooterRecovering = false;
      }
    } else {
      if (shoot == -1) {
        Shooter.spin(reverse);
      } else {
        shooterRecovering = true;
      }
    }

     if (Controller1.ButtonL2.pressing()) {
        if (released_) {
          if (!shoot) {
            shoot = -1;
          } else {
            shoot = 0;
          }
          released_ = false;
        }
      } else {
        released_ = true;
      }



    }
  }


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
