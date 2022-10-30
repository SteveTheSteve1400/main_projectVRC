
#include "main.h"
#include "okapi/api/units/RQuantity.hpp"
#include "pros/misc.h"
#include <cmath>
#include <ratio>

//proportial terms (change later)
double kp = 0;
double ki = 0;
//pros::Motor flywheel(1,pros::E_MOTOR_GEARSET_18,true);
double kd = 0;

//proportional
double rpm_error;

//integral
double prevasym; //prevents the motor from reaching asymtoting behaviour

//derivative
double commandedFlywheelSpeed = 1090;

double currentFlywheelSpeed;//motor encoder value (always changing from 0-3600 rpm)
double drpm;//derivative value

//change commanded voltage for the flywheel
double tellmotorspeed;
double k = 1; //concavity of function (currently at 1 for it to fucking work)
double maxrpm; //crossmap rpm required

double minrpm; //point blank rpm required
//HELPER FUNCTION
void setFlywheel(int power){
    flywheel = power;
}

//DRIVER CONTROL FUNCTION
void setFlywheelMotors(){

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        flywheelPower+= 10;
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        flywheelPower-= 10;
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        flywheelPower = (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    }
    else{
        flywheelPower = 0;
    }

    //PID for flywheel
    double absvaluedist = sqrt(pow(xintinialposition,2)+pow(yintinialposition,2));
    double voltagerpm = (127*(maxrpm-minrpm)*(pow(((absvaluedist-2.76557)/9.71122),k)+minrpm))/3600;

    //change this
    double commandedFlywheelSpeed = flywheelPower*3600/127;

    double motorsignalrpm = currentFlywheelSpeed;

    currentFlywheelSpeed = flywheel.get_actual_velocity();

    rpm_error = kp*(commandedFlywheelSpeed - currentFlywheelSpeed); //proportional
    prevasym = ki*(prevasym + ((commandedFlywheelSpeed - motorsignalrpm)+(commandedFlywheelSpeed - currentFlywheelSpeed))/2*20); //integral, 20 is miliseconds
    drpm = kd*(currentFlywheelSpeed - motorsignalrpm); //derivative
    tellmotorspeed = currentFlywheelSpeed + rpm_error + prevasym + drpm;
    //top triggers flywheel;
    //function


    //actual commanded flywheel speed
    /*
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        flywheelPower = (127*tellmotorspeed/3600)*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    } //change voltagerpm to motorsignalrpm after Saturday
    else{
        flywheelPower = 0;
    }*/

    setFlywheel(tellmotorspeed); 
}








    /*int flywheelPower = 50;

    setFlywheel(flywheelPower);*/