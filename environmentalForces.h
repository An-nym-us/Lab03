#pragma once

#include "gameState.h"
#include "lander.h"



class EnvironmentalForces
{
public:

    void applyGravity();
    void applyIntertia(Lander& landerInstance);
    double getTotalVelocity();
    double getDDX() { return ddx; }
    double getDDY() { return ddy; }
    void setDDX(double ddx) { this->ddx = ddx; }
    void setDDY(double ddy) { this->ddy = ddy; }



private:
    const double GRAVITY = -1.625;


    double dx;
    double dy;
    static double ddx;
    static double ddy;


};