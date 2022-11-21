#include "main.h"
#include "pros/misc.h"

//HELPER FUNCTION
void setLauncher(int power){
    launcher.move_relative(power,100);
}

//DRIVER CONTROL FUNCTION
void setLauncherMotors(){
    //int launcherpower = 70*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y));
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
        setLauncher(700);
        pros::delay(300);
        setLauncher(-700);
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        setLauncher(-100);
        pros::delay(100);
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        setLauncher(100);
        pros::delay(100);
    }
    
}