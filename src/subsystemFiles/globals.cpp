#include "main.h"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rotation.hpp"
#include "pros/motors.hpp"

//pros::Motor [name] ([port], pros::E_MOTOR_GEARSET_[choice], [reverse true?], pros::E_MOTOR_ENCODER_[encoder units]);
//E_MOTOR_GEARSET_06: 600 rpm
//E_MOTOR_GEARSET_18: 200 rpm
//E_MOTOR_GEARSET_36: 100 rpm

//Motors
pros::Motor extension(2,pros::E_MOTOR_GEARSET_36, false);// Port is 2, 100 rpm, not reversed
pros::Motor flywheel(5,pros::E_MOTOR_GEARSET_INVALID, false);// Port is 5, 3600 rpm using a custom cartridge, not reversed
pros::Motor intake(4,pros::E_MOTOR_GEARSET_18, false);// Port is 4, 200 rpm, not reversed
pros::Motor launcher(13,pros::E_MOTOR_GEARSET_36, false);// Port is 13, 100 rpm, not reversed
pros::Motor driveLeftBack(17,pros::E_MOTOR_GEARSET_18, false);// Port is 17, 200 rpm, not reversed
pros::Motor driveRightBack(20,pros::E_MOTOR_GEARSET_18, true);// Port is 20, 200 rpm, reversed
pros::Motor driveLeftFront(11,pros::E_MOTOR_GEARSET_18, false);// Port is 11, 200 rpm, not reversed
pros::Motor driveRightFront(19,pros::E_MOTOR_GEARSET_18, true);//  Port is 19, 200 rpm, reversed
pros ::Motor_Group motor_Left({driveLeftBack , driveLeftFront});// Port is 17 and 11, 200 rpm, not reversed
pros ::Motor_Group motor_Right({driveRightBack , driveRightFront});// Port is 20 and 19, 200 rpm, reversed
pros ::Rotation RotLeft(6);// Port is 6
pros ::Rotation RotRight(21);// Port is 21
pros ::Rotation RotBack(3);// Port is 3
pros ::IMU inertialSensor(15);// Port is 15
int flywheelPower = 0;
double theta = pi/2;
double xintinialposition;
double yintinialposition;
double fError;
double fDerivate;
double fTotalError = 0;
double fPrevError = 0;
double fKp = 0.0001;
double fKi = 0.0000001;
double fKd = 0.0000001;
uint32_t timeTaken;



//Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//pros:: Controller secondcontroller(pros::E_CONTROLLER_PARTNER);

