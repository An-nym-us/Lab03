#pragma once

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "gameState.h"





class Lander
{
public:
    Lander() :
        ptLM(550, 550)
    {};

    
    bool isThrust() { return applyThrust; }
    void setThrust(bool thrust);
    void applyThrustEffect();
    double getAngle() { return angle; }
    void setAngle(double angle) { this->angle = angle; }



    Point& const getptLMInstance() { return ptLM; }
    double getFuelStatus() { return fuel; }
    int getMoonLanderWidth()  { return MOONLANDERWIDTH; }
    double getWeight() { return WEIGHT; }
    double getThrust() { return THRUST;  }




private:
    const int MOONLANDERWIDTH = 9.44; // width of the lander in meters
    const double WEIGHT = 15103.00;
    const double THRUST = 45000.00;

    Point ptLM;           // location of the LM on the screen
    double fuel = 777;
    double angle = 0;
    bool applyThrust = false;
    void decrementFuel();
};