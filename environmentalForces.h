/***********************************************************************
 * Header File:
 *    EnvironmentalForces
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *    
 ************************************************************************/

#pragma once


class EnvironmentalForces
{
public:

    void applyGravity();
    void applyIntertia(Point& point);
    double getTotalVelocity();
    double getDDX() { return ddx; }
    double getDDY() { return ddy; }
    void setDDX(double ddx) { this->ddx = ddx; }
    void setDDY(double ddy) { this->ddy = ddy; }



private:

    /* Environmental Constants */
    const double GRAVITY = -1.625;


    /* Environmental Member Variables */
    double dx;
    double dy;
    //static double ddx;
    //static double ddy;


    double ddx;
    double ddy;

};