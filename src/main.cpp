#include "main.h"
#include "ARMS/chassis.h"
#include "display/lv_objx/lv_btnm.h"
#include "okapi/impl/device/rotarysensor/rotationSensor.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "ARMS/config.h"
#include <chrono>
#include <machine/_default_types.h>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing--   .hello--fsuhgdkjilhjgsdfkakvhgfdslvfhdg
	Steve made this change jfdskjkdsjsakjd
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
	pros::lcd::set_text(1, "NP(C) is on the Top...");
	pros::lcd::set_text(2,"Get Clapped!uuuuuu");
	pros::lcd::set_text(3,"Made by Steve Rho of 39T");
	pros::lcd::set_text(4,"Can you give us pneumatics");
	pros::lcd::set_text(5,"so we become P(C)?");
	pros::lcd::set_text(6,"ur momYUH");
	pros::lcd::register_btn1_cb(on_center_button);
	arms::init();
	
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	while(true){
		pros::lcd::set_text(2, "Ez claps you bozos!");
		pros::lcd::set_text(2, "ez");
	}
	
}

double kP = 0.20;//change later
double kI = 0.00;//change later
double kD = 0.00;//change later

double turn_kP =0.00;//change later
double turn_kI =0.00;//change later
double turn_kD =0.00;//change later

int error;
int prevError;
int derivate;
int totalError;
int targetPosition = 100;

int turn_error;
int turn_prevError;
int turn_derivate;
int turn_totalError;
int turn_targetPosition = 0;

bool enablePID = false;
bool resetDriveSensor = true;

int drivePID(){
	if(resetDriveSensor){
		motor_Left.tare_position();
		motor_Right.tare_position();
	}
	int leftFPosition = driveLeftFront.get_position();
	int leftBPosition = driveLeftBack.get_position();
	int RightFPosition = driveRightFront.get_position();
	int RightBPosition = driveRightBack.get_position();
	int leftAvg = (leftBPosition + leftBPosition)/2;
	int rightAvg = (RightBPosition+ RightFPosition)/2;
	int avgPos = (leftAvg+rightAvg)/2;

	error = avgPos - targetPosition;
	derivate = error - prevError;
	totalError += error;

	double lateralMotion = kP*error + kI*totalError + kD*derivate;

	int turnDifference = leftAvg - rightAvg;
	turn_error = turnDifference - turn_targetPosition;
	turn_derivate = turn_error - turn_prevError;
	turn_totalError += turn_error;
	double turnMotor = turn_kP*turn_error + turn_kI*turn_totalError + turn_kD*turn_derivate;
	motor_Left.move_voltage(lateralMotion + turnMotor);
	motor_Right.move_voltage(lateralMotion- turnMotor); 
	prevError = error;	
	turn_prevError = turn_error;
	return 0;
	
}



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

void driveF(int power){
	motor_Left.move_relative(power,80 );
	motor_Right.move_relative(power,80);

}
void spinStand(int power){
	motor_Left.move_relative(power,80 );
	motor_Right.move_relative(-power,80);
}
void spinR(int power){
	motor_Right = power;
}
void spinL(int power){
	motor_Left= power;
}
void intakePower(int power){
	intake.move_relative(power, 100);
}
void flywheelShoot(int power){
	flywheel.move_voltage(power);
	pros::delay(3000);
	launcher.move_relative(800,100);
    pros::delay(400);
    launcher.move_relative(-800,100);
	pros::delay(600);
	launcher.move_relative(800,100);
    pros::delay(400);
    launcher.move_relative(-800,100);
}
void autonomouMains() {
	driveF(10);
	pros::delay(200);
	driveF(0);
	pros::delay(1000);
	setIntake(0);

}
void autonomousSide(){
	//flywheelShoot(7000);
	//driveF(1600);
	//spinStand(300);
}
void autonomousArms(){
	//23.4 inches per tile
	arms::chassis::move(-1);
	intakePower(900);
	arms::chassis::move(1.0);
	arms::chassis::turn(90, 100);
	arms::chassis::move(-11.0);
	intakePower(900);
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
	std::cout<<"hello";
	flywheelPower=10000;
	int time=0;
	while(true){
		timeTaken = pros::millis();
		//code to control the drive
		setDriveMotors();
		//code to control the intake
		setIntakeMotors();
		//code to controller flywheel
		//code to controller launcher
		setLauncherMotors();
		launch();
		

		
		if(time%50){
			controller.print(0,0, "Speed = %d",flywheelPower);
		}
		time +=10;
		pros::delay(10); //motors update their values every 10 ms;

	}
}

