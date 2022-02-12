/***********************************************************************
 * Header File:
 *    EnvironmentalForces
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *    Apply all forces that are based on real-world logic. Effects such
 *    as gravity, drag, or any other reality effect that may be present,
 ************************************************************************/

#pragma once


class EnvironmentalForces
{
public:

    void applyGravity();                            // Apply gravity based on the gravity constant to the native acceleration variable.
    void applyIntertia(Point& point);               // Apply Intertia effect. The input will be a point in space, taken, altered, and returned to its appropriate new value.
    double getTotalVelocity();                      // Get total velocity of created class model
    double getDDX() { return ddx; }                 // Return the current acceleration in X-axis
    double getDDY() { return ddy; }                 // Return the current acceleration in Y-axis
    void setDDX(double ddx) { this->ddx = ddx; }    // Set acceleration in X-axis
    void setDDY(double ddy) { this->ddy = ddy; }    // Set acceleration in Y-axis



private:

    /* Environmental Constants */
    const double GRAVITY = -1.625;
    const double TIMEDILATION = .1;


    /* Environmental Member Variables */
    double dx;
    double dy;
    double ddx;
    double ddy;

};