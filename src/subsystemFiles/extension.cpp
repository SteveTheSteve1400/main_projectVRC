#include "main.h"
#include "pros/misc.h"

void launch(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
        extension = 50*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT));
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        extension = -50*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT));
    }
    else{
        extension = 0;
    }
}