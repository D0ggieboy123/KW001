#include "vex.h"

using namespace vex;

// Drive motors
extern motor L;
extern motor R;

// Pin/Gripper arms
extern motor LGripper;
extern motor RGripper;
extern motor_group GripperArms;

// Beam lift
extern motor LBeamlift;
extern motor RBeamlift;
extern motor_group Beamlift;

// Solenoid for Beam Clamp and Pin grippers
extern pneumatic Solenoid1;

// Solenoid for floor cactus aligner
extern pneumatic Solenoid2;

// Gyro Sensors
extern gyro Gyro9;
extern gyro Gyro10;

//Brain Inertial/Sensor
extern inertial BrainInertial;

// Touch LED to start autonomous
extern touchled FingerSensor;
