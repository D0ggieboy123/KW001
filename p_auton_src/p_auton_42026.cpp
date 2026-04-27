/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       dogma                                                     */
/*    Created:      1/30/2026, 5:50:45 PM                                     */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "RobotConfig.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

//Resets all the cylinders and sets velocity of all motors
void Settings(){
    L.setStopping(brake);
    R.setStopping(brake);   

    GripperArms.setVelocity(100, percentUnits::pct);
    Beamlift.setVelocity(100, percentUnits::pct);
    GripperArms.setMaxTorque(100, percentUnits::pct);
    Beamlift.setMaxTorque(100, percentUnits::pct);

    Solenoid1.retract(cylinder1);
    Solenoid1.extend(cylinder2);
    Solenoid2.retract(cylinder1);
    Solenoid1.pumpOff();

    //Waits 2 seconds before calibrating brain inertial to insure a good calibration 
    wait(2, timeUnits::sec);

    BrainInertial.calibrate();
    BrainInertial.setHeading(0, rotationUnits::deg);
    BrainInertial.setRotation(0, rotationUnits::deg);
    FingerSensor.setBrightness(100);
    FingerSensor.setColor(blue_green);
    Solenoid1.pumpOn();

    //Waits 18 seconds to fully fill air tanks so cylinders can run at full potential(Indicated by touch led turning red)
    wait(18, timeUnits::sec);
    FingerSensor.setColor(red);
    Solenoid1.pumpOff();
    return;
}

//Correcting turn function
void turn_correct(double rotation, double velocity, double momentum){
    if ((BrainInertial.rotation(rotationUnits::deg) + momentum) > rotation){
        //Right turn
        while((BrainInertial.rotation(rotationUnits::deg) + momentum) > rotation){
            L.setVelocity(velocity, percentUnits::pct);
            R.setVelocity(velocity, percentUnits::pct);
            L.spin(forward);
            R.spin(reverse);

            task::sleep(20);
        }
    }
    else{
        //Left turn
        while((BrainInertial.rotation(rotationUnits::deg) - momentum) < rotation){
            L.setVelocity(velocity, percentUnits::pct);
            R.setVelocity(velocity, percentUnits::pct);
            L.spin(reverse);
            R.spin(forward);

            task::sleep(20);
        }
    }
    L.stop();
    R.stop();
}

void P_straight(double heading, double distance, double velocity, double kp){
    L.setPosition(0, rotationUnits::deg);
    R.setPosition(0, rotationUnits::deg);

    while((fabs(static_cast<float>((L.position(rotationUnits::deg) + R.position(rotationUnits::deg)) / 2)) < distance)){
        //Proportional
        float error = (heading - BrainInertial.rotation(rotationUnits::deg));
        //Calculates the correction
        float output = (error * kp);

        //Sets the velocity to the argument velocity and the corrections
        L.setVelocity(velocity + output, percentUnits::pct);
        R.setVelocity(velocity - output, percentUnits::pct);
        L.spin(forward);
        R.spin(forward);
        
        task::sleep(20);
    }
    L.stop();
    R.stop();
}

void P_straight_timeout(double heading, double distance, double velocity, double kp, double timer){
    L.setPosition(0, rotationUnits::deg);
    R.setPosition(0, rotationUnits::deg);
    Brain.Timer.reset();

    while((fabs(static_cast<float>((L.position(rotationUnits::deg) + R.position(rotationUnits::deg)) / 2)) < distance) && (Brain.Timer.value()) <= timer){
        //Proportional
        float error = (heading - BrainInertial.rotation(rotationUnits::deg));
        //Calculates the correction
        float output = (error * kp);

        L.setVelocity(velocity + output, percentUnits::pct);
        R.setVelocity(velocity - output, percentUnits::pct);
        L.spin(forward);
        R.spin(forward);
        task::sleep(20);
    }

    L.stop();
    R.stop();
}

//Autonomous strategy with Proportional conttroller
void P_auton_strat(){
    float kp = 2.2;
    float turn_speed = 60;
  while (true){
        if (FingerSensor.pressing()){
        FingerSensor.setColor(blue);
        Solenoid1.retract(cylinder1);
        //First long drive forward to red pin
        P_straight(0, 1075, 80, kp);
        wait(0.1, timeUnits::sec);
        //Turns to first red pin
        turn_correct(90, turn_speed, 32);
        wait(0.1, timeUnits::sec);
        Solenoid1.extend(cylinder1);
        Solenoid1.pumpOn();
        //Drives to first red pin from turn
        P_straight(90, 290, 80, kp);
        //Gets red pin
        Solenoid1.retract(cylinder1);
        wait(0.1, timeUnits::sec);
        GripperArms.spinFor(forward, 200, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        //Gets first orange pin alingments
        P_straight(90, 280, 80, kp);
        //Turns to get second orange pin
        turn_correct(115, turn_speed, 30);
        wait(0.1, timeUnits::sec);
        P_straight(115, 337, 70, kp);
        //Slams down orange pins
        wait(0.1, timeUnits::sec);
        GripperArms.spinFor(reverse, 200, rotationUnits::deg, true);
        wait(0.2, timeUnits::sec);
        Solenoid1.extend(cylinder1);
        wait(0.1, timeUnits::sec);
        Solenoid1.retract(cylinder1);
        //Double stack shift in grippers
        P_straight(115, 75, 80, kp);
        wait(0.1, timeUnits::sec);
        P_straight(115, 235, -80, kp);
        wait(0.1, timeUnits::sec);
        //Turns toward beam
        turn_correct(180, turn_speed, 30);
        wait(0.1, timeUnits::sec);
        //Drives into beam
        L.spin(reverse);
        R.spin(reverse);
        wait(1, timeUnits::sec);
        //Clamps down beam
        Solenoid1.extend(cylinder2);
        wait(0.1, timeUnits::sec);
        //Drives slightly away from wall
        P_straight(180, 135, 80, kp);
        Solenoid1.pumpOff();
        wait(0.1, timeUnits::sec);
        //Inserts double stacks into beam
        GripperArms.spinFor(forward, 710, rotationUnits::deg);
        Solenoid1.extend(cylinder1);
        GripperArms.spinFor(reverse, 710, rotationUnits::deg);
        //Raises beam lift
        Beamlift.spinFor(forward, 490, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        turn_correct(220, turn_speed, 30);
        wait(0.1, timeUnits::sec);
        P_straight(220, 300, 80, kp);
        //Turns to standoff pin
        Solenoid1.pumpOn();
        //Grabs stanoff pin
        Solenoid1.retract(cylinder1);
        wait(0.3, timeUnits::sec);
        //Raises arm so the white pins don't hit
        GripperArms.spinFor(forward, 280, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        //Backs up from standoff pin position
        P_straight(220, 350, -50, kp);
        wait(0.1, timeUnits::sec);
        //Turn toward pedestal to place pin
        turn_correct(193, turn_speed, 15);
        wait(0.1, timeUnits::sec);
        //Drives into pedestal to place pin
        P_straight_timeout(192, 380, 52, kp, 1.5);
        Solenoid1.extend(cylinder1);
        //Drives away from placed standoff pin
        P_straight(197, 210, -80, kp);
        wait(0.1, timeUnits::sec);
        GripperArms.spinFor(reverse, 280, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        turn_correct(0, turn_speed, 32);
        wait(0.1, timeUnits::sec);
        //Drive backwards and align beam to drop on standoff
        L.spin(reverse);
        R.spin(reverse);
        wait(2.3, timeUnits::sec);
        L.stop();
        R.stop();
        Beamlift.spinFor(reverse, 50, rotationUnits::deg);
        Solenoid1.retract(cylinder2);
        wait(0.6, timeUnits::sec);
        Solenoid1.pumpOff();
        Beamlift.spinFor(forward, 50, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        //Drive away from placed beam
        P_straight(0, 400, 60, kp);
        Beamlift.spinFor(reverse, 490, rotationUnits::deg);
        //Turns into first orange pin for wall zero
        turn_correct(90, turn_speed, 33);
        wait(0.1, timeUnits::sec);
        //Drives to first orange pin for wall zero
        P_straight(90, 400, 55, kp);
        wait(0.1, timeUnits::sec);
        //Turn to second orange pin
        turn_correct(111, turn_speed, 10);
        wait(0.1, timeUnits::sec);
        //Drives Certain distance to get pins
        P_straight_timeout(110, 480, 55, kp, 2);
        wait(0.1, timeUnits::sec);
        //Turns to zero on wall
        turn_correct(90, turn_speed, 20);
        //Zeros the robot on the wall
        P_straight_timeout(90, 200, 70, kp, 0.8);
        Solenoid1.retract(cylinder1);
        //Slight correction of zero on wall
        turn_correct(90, turn_speed, 15);
        //Backup from wall
        P_straight(90, 40, -70, kp);
        wait(0.1, timeUnits::sec);
        //Turns into stacking
        turn_correct(202, turn_speed, 30);
        GripperArms.spinFor(reverse, 200, rotationUnits::deg);
        //Drive into two pins and stack
        P_straight(202, 550, 70, kp);
        GripperArms.setVelocity(85, percentUnits::pct);
        GripperArms.spinFor(reverse, 200, rotationUnits::deg, true);
        Solenoid1.pumpOn();
        GripperArms.setVelocity(100, percentUnits::pct);
        wait(0.2, timeUnits::sec);
        Solenoid1.extend(cylinder1);
        wait(0.2, timeUnits::sec);
        Solenoid1.retract(cylinder1);
        //Align the two double stacks into grippers
        P_straight(202, 75, 70, kp);
        wait(0.1, timeUnits::sec);
        //Backup into beam to align it with the wall
        P_straight(202, 130, -70, kp);
        //Turn into aligned beam to clamp
        turn_correct(280, turn_speed, 22);
        wait(0.1, timeUnits::sec);
        Solenoid1.pumpOff();
        //Drive into aligned beam to clamp
        L.spin(reverse);
        R.spin(reverse);
        wait(1.3, timeUnits::sec);
        //Clamp beam
        Solenoid1.extend(cylinder2);
        //Drive away to get off of loading zone from original beam position
        P_straight(270, 235, 70, kp);
        //Put 2 double stacks into beam
        GripperArms.spinFor(forward, 710, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        Solenoid1.extend(cylinder1);
        wait(0.1, timeUnits::sec);
        GripperArms.spinFor(reverse, 710, rotationUnits::deg);
        Beamlift.spinFor(forward, 35, rotationUnits::deg);
        //Turn into first orange pin for final double stack
        turn_correct(180, turn_speed, 44);
        wait(0.1, timeUnits::sec);
        //Drive into first orange pin for final double stack
        P_straight(180, 265, 70, kp);
        wait(0.1, timeUnits::sec);
        //Grab first orange pin for final double stack
        Solenoid1.retract(cylinder1);
        wait(0.1, timeUnits::sec);
        //Lift gripper arms for final double stack
        GripperArms.spinFor(forward, 200, rotationUnits::deg);
        wait(0.1, timeUnits::sec);
        //Drive into second blue pin final double stack
        P_straight(180, 135, 70, kp);
        wait(0.1, timeUnits::sec);
        //Stack final double stack 
        GripperArms.spinFor(reverse, 200, rotationUnits::deg, true);
        Solenoid1.pumpOn();
        wait(0.2, timeUnits::sec);
        Solenoid1.extend(cylinder1);
        wait(0.2, timeUnits::sec);
        //Drive a little bit away from final doble stack
        P_straight(180, 70, -70, kp);
        wait(0.1, timeUnits::sec);
        //Turn into stack final cactus
        turn_correct(345, turn_speed, 39);
        Beamlift.spinFor(forward, 300, rotationUnits::deg, true);
        wait(0.8, timeUnits::sec);
        Solenoid2.extend(cylinder1);
        wait(0.3, timeUnits::sec);
        //Drive into stack for final cactus
        P_straight_timeout(345, 325, -38, 1.5, 1.5);
        wait(0.1, timeUnits::sec);
        //Stack final cactus
        Beamlift.spinFor(reverse, 55, rotationUnits::deg);
        Solenoid1.retract(cylinder2);
        wait(0.6, timeUnits::sec);
        Solenoid1.pumpOff();
        Beamlift.spinFor(forward, 55, rotationUnits::deg);
        //Drive into touch 2 final pins
        P_straight(340, 935, 100, kp);
        //Grab 2 final pins
        Solenoid1.retract(cylinder1);
        Brain.programStop();
        }
        wait(20, msec);
    }
    return;
}


int main() {
//Only calling 2 functions because the other functions are called in the strategy functions
   Settings();
   P_auton_strat();
}
