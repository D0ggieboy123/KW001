#include "main.h"
#include "pros/motor_group.hpp"
#include <numbers>

using namespace pros;


//Settings 
MotorGroup Left_Drive ({1, 2, 3});
MotorGroup Right_Drive ({4, 5, 6});

Imu imu_sensor(7);

Rotation TrackingWheel_Vertical(9);
Rotation TrackingWheel_Horizontal(10);



//Global variables
double TrackingWheel_Radius = 1.0;

double Prev_Angle_Vertical = TrackingWheel_Vertical.get_angle();
double Prev_Angle_Horizontal = TrackingWheel_Horizontal.get_angle();
double Prev_Inertial_Rotation = imu_sensor.get_rotation();

double x;
double y;
double theta;

double X_Prev_Error = 0.0;
double Y_Prev_Error = 0.0;
double Theta_Prev_Error = 0.0;




void Settings(){
	Left_Drive.set_drive_brake(brake_type: MOTOR_BRAKE_COAST);
	Right_Drive.set_drive_brake(brake_type : MOTOR_BRAKE_COAST);
}

//Calculates current position on field 
void get_point(){
	double Angle_Moved_Vertical = (Prev_Angle_Vertical - TrackingWheel_Vertical.get_angle());
	double Angle_Moved_Horizontal = (Prev_Angle_Horizontal - TrackingWheel_Horizontal.get_angle());

	double Delta_V = ((Angle_Moved_Vertical / 360.0) * ((2 * TrackingWheel_Radius) * numbers::pi));
	double Delta_H = ((Angle_Moved_Horizontal / 360.0) * ((2 * TrackingWheel_Radius) * numbers::pi));
	double Theta_1  = (Prev_Inertial_Rotation + Inertial_Sensor.get_rotation());
	double Delta_Theta = (Theta_1 - Prev_Inertial_Rotation);

	if (Delta_Theta == 0.0){
		double Delta_dl_v = Delta_V;
		double Delta_dl_h = Delta_H;
	}
	else{
		Delta_dl_v = 2.0 * sin(Delta_Theta / 2.0) * ((Delta_V / Delta_Theta));
		Delta_dl_h = 2.0 * sin(Delta_Theta / 2.0) * ((Delta_H / Delta_Theta));
	}

	double Theta_m = (Prev_Inertial_Rotation - (Delta_Theta / 2.0));
	double Delta_d_v = Delta_dl_h * sin(Theta_m) + Delta_dl_v * cos(Theta_m); 
	double Delta_d_h = Delta_dl_h * cos(Theta_m) - Delta_dl_v * sin(Theta_m);

	Prev_Angle_Vertical = TrackingWheel_Vertical.get_angle();
	Prev_Angle_Horizontal = TrackingWheel_Horizontal.get_angle();
	Prev_Inertial_Rotation = imu_sensor.get_rotation();

	x = Delta_d_h;
	y = Delta_d_v;
	theta = Theta_m;
}

void move_to_point(double X_target, double Y_target, double Theta_Target, double Velocity, double Distance_error, double kp, double kd){
	get_point();

	double X_Error = X_target - x;
	double Y_Error = Y_target - y;

	double Distance = sqrt((x_error * x_error) + (y_error * y_error));

	while(Distance > Distance_error){
		X_Error = X_target - x;
		Y_Error = Y_target - y;

		Distance = sqrt((x_error * x_error) + (y_error * y_error));

		Theta_Target = atan2(Y_Error, X_Error);
		double Theta_Error - Prev_Inertial_Rotation;

		double X_Derivative = X_Prev_Error - X_Error;
		double Y_Derivative = Y_Prev_Error - Y_Error;
		double Theta_Derivative = Theta_Prev_Error - Theta_Error;

		double X_Output = (kp * X_Error) + (kd * X_Derivative);
		double Y_Output = (kp * Y_Error) + (kd * Y_Derivative);
		double Theta_Output = (kp * Theta_Error) + (kd * Theta_Derivative);

		
	}
}

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {}
	