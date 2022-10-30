#include "main.h"
#include "okapi/api/units/RQuantity.hpp"
#include "pros/misc.h"
#include <cmath>
#include <ratio>

//HELPER FUNCTION
void setFlywheel(int power){
    flywheel = power;
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
        flywheelPower+= 10;
        pros::delay(100);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
        flywheelPower-=10;
        pros::delay(100);
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        setFlywheel(127/100*abs(flywheelPower));
    }
    else{
        setFlywheel(0);
    }
}
