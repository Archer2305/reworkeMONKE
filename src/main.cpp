#include "main.h"


// #include "auton.hpp"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void leftPressed(){
route=1;

}
void middlePressed(){
route=2;
}
void rightPressed(){
route=3;
}
void initialize() {
	pros::lcd::initialize();  
	pros::lcd::set_text(1, "To the left...");
	// 	pros::lcd::set_text(2, "To the right... ");
	// 	pros::lcd::set_text(3, "Find your ride ");
	// 		pros::lcd::set_text(4, "Now put that whip in drive  ");
	
	pros::lcd::register_btn0_cb(leftPressed);
	pros::lcd::register_btn1_cb(middlePressed);
	pros::lcd::register_btn2_cb(rightPressed);
    pros::ADIDigitalOut  leftPiston('B');
	okapi::IMU  inertial = IMU(7);
	
}

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
void autonomous() {
	updateAuton();
}

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
		while (true){
	okapi::Rate rate;
// start();
// stop();
updateExpansion();
updateDrive();
updateFlywheel();
updateIntake();
rate.delay(100_Hz);
	}
}
  
