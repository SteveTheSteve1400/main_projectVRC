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
pros::Motor extension(2,pros::E_MOTOR_GEARSET_36, false);
pros::Motor flywheel(5,pros::E_MOTOR_GEARSET_INVALID, false);
pros::Motor intake(4,pros::E_MOTOR_GEARSET_18, false);
pros::Motor launcher(13,pros::E_MOTOR_GEARSET_36, false);
pros::Motor driveLeftBack(17,pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveRightBack(20,pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveLeftFront(11,pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveRightFront(19,pros::E_MOTOR_GEARSET_18, true);
pros ::Motor_Group motor_Left({driveLeftBack , driveLeftFront});
pros ::Motor_Group motor_Right({driveRightBack , driveRightFront});
pros ::Rotation RotLeft(6);
pros ::Rotation RotRight(21);
pros ::Rotation RotBack(3);
pros ::IMU inertialSensor(15);
int flywheelPower = 0;
double theta = pi/2;
double xintinialposition;
double yintinialposition;
double fError;
double fDerivate;
double fTotalError;
double fPrevError = 0;
double fKp = 0.0001;
double fKi = 0.0000001;
double fKd = 0.0000001;



//Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//pros:: Controller secondcontroller(pros::E_CONTROLLER_PARTNER);'

