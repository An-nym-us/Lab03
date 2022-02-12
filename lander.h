/***********************************************************************
 * Header File:
 *    Lander
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *    Create a trackable instance of the moon lander. This class 
 *    will contain the default moon lander values and constants. 
 *    This will also apply any forces to the lander that are created 
 *    specifically by the moon lander, such as thrust and rotation.
 ************************************************************************/


#pragma once
#include "environmentalForces.h"

class Lander
{
public:
    Lander() :
        ptLM(550, 550)              // starting point on screen for the lander craft (positioned is near the upper right corner)
    {};

    


    bool isThrustActive() { return applyThrust; }               // Get if the player requested active apply thrust to lander
    void setThrustActive(bool thrust);                          // Set that player is requesting thrust be applied to the moon lander
    void applyThrustEffect(Lander& landerInstance, EnvironmentalForces& environmentalForcesInstance);           // apply thurst movement to the lander in space

    Point& const getptLMInstance() { return ptLM; }             // Return the current locion in 2D space of the moon lander
    double getFuelStatus() { return fuel; }                     // Return the current fuel level of the moon lander
    int getMoonLanderWidth()  { return MOONLANDERWIDTH; }       // Return the constant width of the moon lander

    double getAngle() { return angle; }                         // Return the current angle of the moon lander
    void setAngle(double angle) { this->angle = angle; }        // Set the current angle of the moon lander

private:

    /* Lander constants to be accessed from this class*/
    const int MOONLANDERWIDTH = 9.44;   // width of the lander in meters
    const double WEIGHT = 15103.00;     // Mass of the lander in Kilograms
    const double THRUST = 45000.00;     // Effective thrust in Newtons



    /* Lander memeber variables */
    Point ptLM;                         // location of the LM on the screen
    double fuel = 22000;                  // Default starting fuel level (Propellant mass found via google search)
    double angle = 0;                   // Default starting lander angle
    bool applyThrust = false;           // Default startign state of appied thrust bool


    /* Lander memeber functions */
    void decrementFuel();               // Decrement the fuel level by one unit
};