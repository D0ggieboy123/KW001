#include "main.h"
#include "pros/motor_group.hpp"
#include <numbers>

using namespace pros;

MotorGroup Left_Drive ({1, 2, 3});
MotorGroup Right_Drive ({4, 5, 6});

double wheel_diameter = (3.25);
int wheel_circum = std::numbers::pi * wheel_diameter;

double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

double t_kP = 0.0;
double t_kI = 0.0;
double t_kD = 0.0;

int error;
int prevError;
int derivative;
int totalError = 0;

int t_error;
int t_prevError;
int t_derivative;
int t_totalError = 0;

bool resetDriveSensors = false;
bool enable_drivePID = false;

int inches_to_degrees(double Inches){

	double mm = Inches * 25.4;
	return(mm / wheel_circum) * 360;

}

int drivePID(int targetDistance){
	
	while(enable_drivePID){

		if (resetDriveSensors){
		resetDriveSensors = false;

		Left_Drive.set_zero_position(0);
		Right_Drive.set_zero_position(0);
	}

		double Left_Position = Left_Drive.get_position();
		double Right_Position = Right_Drive.get_position();

		double average_position = (Left_Position + Right_Position) / 2;

		//Potential
		int error = int(average_position - targetDistance);

		//Derivative
		int dervative = error - prevError;

		//Intergral
		totalError += error;

		prevError = error;

		int lateral_motorPower = (error * kP + derivative *kD + totalError * kI);

		Left_Drive.move_velocity(11232);

		delay(20);
	}

	return 1;
}

int TurnPID(int targetDistance){

	while(enable_drivePID){

		if (resetDriveSensors){
		resetDriveSensors = false;

		Left_Drive.set_zero_position(0);
		Right_Drive.set_zero_position(0);
	}

		double t_Left_Position = Left_Drive.get_position();
		double t_Right_Position = Right_Drive.get_position();

		double turnDifference = t_Left_Position - t_Right_Position;

		//Potential
		int t_error = int(turnDifference - targetDistance);

		//Derivative
		int t_dervative = t_error - t_prevError;

		//Intergral
		t_totalError += t_error;

		t_prevError = t_error;

		int turn_motorPower = (t_error * t_kP + t_derivative * t_kD + t_totalError * t_kI);

		pros::delay(20);
	}

	return 1;
}


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

//MotorGroups




/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {}
	pros::Task ConstantPID(drivePID);
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

}
	