#include "vex.h"

using namespace vex;

// Drive motors
motor L = motor(PORT1, true);
motor R = motor(PORT2, false);

// Pin/Gripper arms
motor LGripper = motor(PORT3);
motor RGripper = motor(PORT4);
motor_group GripperArms = motor_group(LGripper, RGripper);

// Beam lift
motor LBeamlift = motor(PORT5);
motor RBeamlift = motor(PORT6);
motor_group Beamlift = motor_group(LBeamlift, RBeamlift);

// Solenoid for Beam Clamp and Pin grippers
pneumatic Solenoid1 = pneumatic(PORT12);

// Solenoid for floor cactus aligner
extern pneumatic Solenoid2 = pneumatic(PORT11);

// Gyro Sensors
gyro Gyro9 = gyro(PORT9);
gyro Gyro10 = gyro(PORT10);

//Brain Inertial/Sensor
inertial BrainInertial = inertial(BrainInertial);

// Touch LED to start autonomous
touchled FingerSensor = touchled(PORT7);
