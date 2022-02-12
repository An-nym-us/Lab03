/***********************************************************************
 * Header File:
 *    Lander
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *    Create an instance of the lander. This call will hold its current 
 *      location on the screen, and apply any forces that are instigated by the 
 *      lander craft, such as its rotation and thrust, will be contained 
 *      within this class
 ************************************************************************/


#pragma once
#include "environmentalForces.h"






class Lander
{
public:
    Lander() :
        ptLM(550, 550) // starting point on screen for the lander craft (positioned near the upper right corner)
    {};

    


    bool isThrust() { return applyThrust; }             
    void setThrust(bool thrust);
    void applyThrustEffect(Lander& landerInstance, EnvironmentalForces& environmentalForcesInstance);




    Point& const getptLMInstance() { return ptLM; }
    double getFuelStatus() { return fuel; }
    int getMoonLanderWidth()  { return MOONLANDERWIDTH; }

    double getAngle() { return angle; }
    void setAngle(double angle) { this->angle = angle; }




private:

    /* Lander constants to be accessed from this class*/
    const int MOONLANDERWIDTH = 9.44;   // width of the lander in meters
    const double WEIGHT = 15103.00;     // Mass of the lander in Kilograms
    const double THRUST = 45000.00;     // Effective thrust in Newtons



    /* Lander memeber variables */
    Point ptLM;                         // location of the LM on the screen
    double fuel = 777;                  // Default starting fuel level
    double angle = 0;                   // Default starting lander angle
    bool applyThrust = false;           // Default 


    /* Lander memeber functions */
    void decrementFuel();
};