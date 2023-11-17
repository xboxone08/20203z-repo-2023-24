#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L2                   motor         1               
// L1                   motor         11              
// R3                   motor         20              
// L3                   motor         19              
// R1                   motor         18              
// R2                   motor         17              
// Controller1          controller                    
// LiftSwitch           limit         A               
// Potentiometer        potV2         C               
// Intake               motor         16              
// Lift                 motor         13              
// CATAPULT             motor         10              
// SWITCH               limit         B               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

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
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(L1, L2, L3),

//Right Motors:
motor_group(R1, R2, R3),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT1,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.75,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.60,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

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
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(50, 50, "Drive Test");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Drive Test");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Turn Test");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Swing Test");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "Full Test");
        break;
      case 5:
        Brain.Screen.printAt(50, 50, "Odom Test");
        break;
      case 6:
        Brain.Screen.printAt(50, 50, "Tank Odom Test");
        break;
      case 7:
        Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
      drive_test(); //This is the default auton, if you don't select from the brain.
      break;        //Change these to be your own auton functions in order to use the auton selector.
    case 1:         //Tap the screen to cycle through autons.
      drive_test();
      break;
    case 2:
      turn_test();
      break;
    case 3:
      swing_test();
      break;
    case 4:
      full_test();
      break;
    case 5:
      odom_test();
      break;
    case 6:
      tank_odom_test();
      break;
    case 7:
      holonomic_odom_test();
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

typedef enum {
  INTAKE_STATE_PRIMED = 0,
  INTAKE_STATE_ARM_LOWERING,
  INTAKE_STATE_INTAKE,
  INTAKE_STATE_HOLD,
  INTAKE_STATE_ARM_RAISING,
  INTAKE_STATE_INDEXING,
  INTAKE_STATE_LOADED,
  INTAKE_STATE_ARMING,
  INTAKE_STATE_READY,
  INTAKE_STATE_FIRE
} intake_state_t;

#define CATA_STATE_REST 0
#define CATA_STATE_TRIGGERED 1
#define CATA_STATE_RECOVER 2

void usercontrol(void) {
  // User control code here, inside the loop
  intake_state_t intakeState = INTAKE_STATE_PRIMED;
  int potentiometerBase = Potentiometer.value(percent);

  Intake.setVelocity(100.0, percent);
  Lift.setStopping(brake);
  Lift.setMaxTorque(100, percent);
  Intake.setStopping(brake);
  CATAPULT.setStopping(hold);
  CATAPULT.setVelocity(100, percent);
  CATAPULT.setMaxTorque(100, percent);

  potentiometerBase = 40;
  bool Cata_Button_Pressed;
  bool pressed_before = false;
  int Cata_State = CATA_STATE_RECOVER;

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

    printf("%d\n", intakeState);
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.


    if (pressed_before) {
      if (!Controller1.ButtonL1.pressing())
        pressed_before = false;
    } else {
      if (Controller1.ButtonL1.pressing() && intakeState != INTAKE_STATE_READY) {
        intakeState = INTAKE_STATE_ARMING;
        pressed_before = true;
      }
    }

    // State machine for moving the tri-ball
    // into and within the bot
    switch (intakeState)
    {
    case INTAKE_STATE_PRIMED:
      // Intake and lift motors off
      // Starting state
      Intake.stop();
      Lift.stop();
      if (Potentiometer.value(percent) >= potentiometerBase + 25)
      {
        intakeState = INTAKE_STATE_HOLD;
      }
      else if (Controller1.ButtonR1.pressing())
      {
        intakeState = INTAKE_STATE_ARM_LOWERING;
      }
      break;
    case INTAKE_STATE_ARM_LOWERING:
      // Intake and lift motors forward
      // Lower intake mechanism
      Intake.spin(forward);
      Lift.spin(forward);
      // If lowering/intake button released before passing halfway point,
      // bring arm back up, otherwise continue downward motion.
      if (Potentiometer.value(percent) >= potentiometerBase + 25)
      {
        intakeState = INTAKE_STATE_INTAKE;
      }
      else if (!Controller1.ButtonR1.pressing() && Potentiometer.value(percent) < potentiometerBase + 13)
      {
        intakeState = INTAKE_STATE_ARM_RAISING;
      }
      break;
    case INTAKE_STATE_INTAKE:
      // Intake motor forward; lift motor off
      // Actually do the intaking
      Intake.spin(forward);
      Lift.stop();
      if (!Controller1.ButtonR1.pressing())
      {
        intakeState = INTAKE_STATE_HOLD;
      }
      break;
    case INTAKE_STATE_HOLD:
      // Intake and lift motors off
      // Tri-ball in intake mechanism
      Intake.stop();
      Lift.stop();
      if (LiftSwitch.pressing())
      {
        intakeState = INTAKE_STATE_PRIMED;
      }
      else if (Controller1.ButtonR1.pressing())
      {
        intakeState = INTAKE_STATE_ARM_RAISING;
      }
      else if (Controller1.ButtonR2.pressing())
      {
        intakeState = INTAKE_STATE_INDEXING;
      }
      else if (Controller1.ButtonL1.pressing())
      {
        intakeState = INTAKE_STATE_FIRE;
      }
      break;
    case INTAKE_STATE_ARM_RAISING:
      // Intake and lift motors reverse
      Intake.spin(reverse);
      Lift.spin(reverse);
      if (LiftSwitch.pressing())
      {
        potentiometerBase = Potentiometer.value(percent);
        intakeState = INTAKE_STATE_PRIMED;
      }
      break;
    case INTAKE_STATE_INDEXING:
      // Intake motor forward, lift motor off
      // Move tri-ball to shooting mechanism
      Intake.stop();
      Lift.stop();
      if (LiftSwitch.pressing())
      {
        // Do piston sequence
        intakeState = INTAKE_STATE_LOADED;
      }
      break;
    case INTAKE_STATE_LOADED: 
      // Intake and lift motors off
      // Ball in shooting mechanism
      Intake.stop();
      Lift.stop();
      if  (Controller1.ButtonL1.pressing())
      {
        intakeState = INTAKE_STATE_ARMING;
      }          
      break;
    case INTAKE_STATE_ARMING:
      // Intake and lift motors forward
      // Prepare to fire
      if (!(Potentiometer.value(percent) >= potentiometerBase + 25)) {
        Intake.spin(forward);
        Lift.spin(forward);
      } else {
        intakeState = INTAKE_STATE_READY;
      }
      break;
    case INTAKE_STATE_READY:
      // Intake and lift motors off
      // Ready to fire
      Intake.stop();
      Lift.stop();
      Controller1.rumble("-");
      if  (Controller1.ButtonL1.pressing())
      {
        intakeState = INTAKE_STATE_FIRE;
      }
      break;
    case INTAKE_STATE_FIRE:
      // Intake and lift motors off
      // Actually firing
      Intake.stop();
      Lift.stop();
      // Do catapult sequence
      Cata_Button_Pressed = true;
      intakeState = INTAKE_STATE_PRIMED;
      break;
    default:
      break;
    }

    // State machine for catapult
    switch (Cata_State) {
      case CATA_STATE_REST:
        if (Cata_Button_Pressed)
        {
          CATAPULT.spin(forward);
          Cata_State = CATA_STATE_TRIGGERED;
        } 
        break;
      // Fire button was pressed
      // (in prev. state machine)
      case CATA_STATE_TRIGGERED:
        if (Cata_Button_Pressed)
        {
          CATAPULT.spin(forward);
        } 
        if (!SWITCH)
        {
          Cata_State = CATA_STATE_RECOVER;
        }
        break;
      // Get ready to fire again
      // (bring catapult back down
      // after firing)
      case CATA_STATE_RECOVER:
        if (Cata_Button_Pressed)
        {
          CATAPULT.spin(forward);
        } 
        if (SWITCH)
        {
          CATAPULT.stop();
          Cata_Button_Pressed = false;
          Cata_State = CATA_STATE_REST;
        }
        break; 
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
