#include "main.h"

//HELPER FUNCTION
void setDrive(int left, int right) {
    motor_Left = left;
    motor_Right = right;
}

//DRIVER CONTROL FUNCTONS 
void setDriveMotors(){
    //setDrive(0,0); --> all the drive motors are set to 0;
    //joystick --> analog and button --> digital
    //VOLTAGE OF MOTOR: + or - 127
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    
    if(abs(leftJoystick) < 10){ //TO prevent from margin fo error of the stop position
        leftJoystick = 0;
    }
    if(abs(rightJoystick) < 10){
        rightJoystick = 0;
    }
    
    setDrive(leftJoystick, rightJoystick);
}
