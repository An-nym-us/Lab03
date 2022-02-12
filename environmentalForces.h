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
    const double GRAVITY = -1.625;                  // Moon gravity
    const double TIMEDILATION = .1;                 // Time dilation of based on game tick/framerate


    /* Environmental Member Variables */
    double dx;                                      // World location in X-axis
    double dy;                                      // World location in Y-axis
    double ddx;                                     // World accelleration in X-axis
    double ddy;                                     // World accelleration in Y-axis     

};