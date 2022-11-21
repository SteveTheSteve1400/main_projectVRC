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

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        flywheelPower+= 1000;
        pros::delay(200);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
        flywheelPower-=1000;
        pros::delay(200);
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        setFlywheel(-1*flywheelPower);
    }
    else{
        setFlywheel(0);
    }
}