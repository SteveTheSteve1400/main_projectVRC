#include "main.h"
#include "okapi/api/util/mathUtil.hpp"
#include "pros/rotation.hpp"
#include <cmath>
double changeMid = 0;
double prevM;
double changeBack = 0;
double prevB;
double dM = changeMid - prevM;
double dB = changeBack - prevB;
double diam_of_odomwheel = (2.75*pi)/12;
double rotation;
double x; //adding small orientated x
double y; //adding small orientated y
double posx = 0;
double posy = 0;

void odometryS(){
    while(1){
        rotation = inertialSensor.get_rotation();
        prevM = changeMid;
        prevB = changeBack;
        changeMid = RotMid.get_angle();
        changeBack = RotBack.get_angle();
        if (changeMid - prevM < 0) ybeforeorientation = (360 + (changeMid - prevM))*diam_of_odomwheel/36000; // converting to inches
        if(changeMid - prevM > 18000) ybeforeorientation = (360 - (changeMid - prevM))*diam_of_odomwheel/36000; // converting to inches
        if (changeBack - prevB < 0) xbeforeorientation = (360 + (changeMid - prevM))*diam_of_odomwheel/36000; // converting to inches
        if (changeBack - prevB > 18000) xbeforeorientation = (360 - (changeMid - prevM))*diam_of_odomwheel/36000; // converting to inches
        x = ybeforeorientation*cos(rotation) + xbeforeorientation*cos(rotation-90);
        y = ybeforeorientation*sin(rotation) + xbeforeorientation*sin(rotation-90);
        posx += x;
        posy += y;
    }
}
   

/*double prevL;
double prevR;
double prevB;

void odometryS(){
    while(1){
        double a[100][100];
        theta = pi/2;
        double changeLeft = RotLeft.get_angle();
        double changeRight = RotRight.get_angle();
        double changeBack = RotBack.get_angle();
        double dL = changeLeft - prevL;
        double dR = changeRight - prevR;
        double dB = changeBack - prevB;
        prevL = changeLeft;
        prevR = changeRight;
        prevB = changeBack;
        double dX = (dL + dR) / 2;
        double dY = dB;
        double dTheta = (dR - dL) / 2;
        double db1eac = 10;//change later, distance between center and right encoder
        double db1eab = 10;//change later, distance between center and left encoder
        double db1ead = 10;//change later, distance between center and back encoder
        double thetasub1 = (dL - dR) / (2*db1eac);
        double cd = -thetasub1;
        double cc = theta;
        theta = cc - thetasub1;
        double changeiny;
        double changeinx;
        double optimizefory;
        double optimizeforx;
        double optimizeforx1;
        double optimizefory2;
        double finaladdx;
        double finaladdy;
        double rs;
        xintinialposition = 0;//change to right below goal
        yintinialposition = 0;//change to right below goal
        changeiny = 2*sin(cd/2)*((dL/cd)+db1eac);
        optimizefory = sin(theta)*changeiny;
        optimizeforx = cos(theta)*changeiny;
        rs = dB/cd - dB;
        optimizeforx1 = rs*sin(cd);
        optimizefory2 = rs*cos(cd);
        finaladdx = optimizeforx + optimizeforx1;
        finaladdy = optimizefory + optimizefory2;
        xintinialposition = xintinialposition + finaladdx;
        yintinialposition = yintinialposition + finaladdy;
        
    }
}*/
