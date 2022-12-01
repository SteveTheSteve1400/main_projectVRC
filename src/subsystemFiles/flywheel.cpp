#include "main.h"
#include "okapi/api/units/RQuantity.hpp"
#include "pros/misc.h"
#include <cmath>
#include <ratio>

//HELPER FUNCTION
void setFlywheel(int power){
    flywheel.move_voltage(power);
}

//DRIVER CONTROL FUNCTION
void setFlywheelMotors(){
	
    //top triggers flywheel;
    //
    //
    //
    //
    //function
    /*double k; //concavity of function
    double maxrpm; //crossmap rpm required
    double minrpm; //point blank rpm required
    double absvaluedist = sqrt(pow(xintinialposition,2)+pow(yintinialposition,2));
    double voltagerpm = (127*(maxrpm-minrpm)*(pow(((absvaluedist-2.76557)/9.71122),k)+minrpm))/3600;
    int flywheelPower;
    */
    /**
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
    */
	double fSubstract;
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
	flywheelPower+= 1000;
	pros::delay(200);
	}
	else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
	flywheelPower-=1000;
	pros::delay(200);
	}
	fError =  flywheelPower - flywheel.get_voltage();
	fDerivate = fError - fPrevError;
	fTotalError += fError;
	fSubtract = fKp*fError + fKi*fTotalError + fKd*fDerivate;
	flywheelPower = flywheelPower - fSubtract;
	
	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
	setFlywheel(flywheelPower);
	}
	else{
	setFlywheel(0);
	}
	fPrevError = fError;

}
