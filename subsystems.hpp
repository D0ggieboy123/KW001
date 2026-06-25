#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#ifndef SUB
#define SUB

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::MotorGroup intake_motors({12, 19});


/** 
 * Only for regular season
 * inline pros::Distance d_1(3);
 * inline pros::Distance d_2(4);
*/
//inline pros::Distance Dist(3);

inline pros::Motor l_lift(13);
inline pros::Motor r_lift(18);

inline void set_lift(int input) {
  l_lift.move(input);
  r_lift.move(input);
}

//Maybe? Probably not for tpsf
inline ez::PID four_lift{0.45, 0, 0, 0, "Lift"};

/**  
 * Use for lift if team is using (probably not tpsf)
 * inline pros::Rotation r_1(10);
 * inline pros::Rotation r_2(11);
*/

inline pros::MotorGroup two_lift({2, 9});


inline ez::Piston liftclaw('A');
#endif


// inline pros::adi::DigitalIn limit_switch;