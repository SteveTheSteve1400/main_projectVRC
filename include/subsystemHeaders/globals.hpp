
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
extern pros::Motor driveLeftBack;
extern pros::Motor driveRightBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightFront;
extern pros::Motor extension;
extern pros::Motor flywheel;
extern pros::Motor intake;
extern pros::Motor launcher;
extern pros::Motor_Group motor_Left; //({driveLeftBack , driveLeftFront});
extern pros::Motor_Group motor_Right; //({driveRightBack , driveRightFront});
extern pros::Rotation RotLeft;
extern pros::Rotation RotRight;
extern pros::Rotation RotBack;
extern pros::IMU inertialSensor;
extern double theta;
extern double xintinialposition;
extern double yintinialposition;
extern int flywheelPower;
//CONTROLLERS
extern pros::Controller controller;
extern double fError;
extern double fDerivate;
extern double fTotalError;
extern double fPrevError;
extern double fKp;
extern double fKi;
extern double fKd;

//extern pros::Controller secondcontroller;

//MISCELLANEOUS (where you declare things that u want to abbreviate)
#define PositionSet 3000;
