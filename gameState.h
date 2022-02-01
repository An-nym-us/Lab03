#pragma once
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"

#include <iostream>

class LanderState 
{
public:
    LanderState(const Point& ptUpperRight) : 
        angle(0.0),
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
        ground(ptUpperRight)
    {};

    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen

    Ground ground;




    //DEBUG
    double landerDX = 0; // lander stating state
    double landerDY = 0; // lander stating state
    double angle;         // angle the LM is pointing
    bool applyThrust = false;
    double fuel = 7777;
    double speed = 77;
    double altitude = 777;



    void onScreenText(LanderState* landerInstance); // Centerlize what text to place on screen
    void updateControllerInputs(const Interface* pUI, LanderState* LanderInstance);

};






class Crash
{
public:
    bool isInGround(LanderState * landerInstance);

private:

protected:
};



class Stars
{
public:
    void showStars();

private:

protected:

};




class Physics
{
public:


	void gravity(LanderState* LanderInstance);
    void applyIntertia(LanderState* LanderInstance);
    void applyThrust(LanderState* LanderInstance);
    double totalVelocity();




private:

    // Declare static variables.
    static double x;
    static double y;
    static double dx;
    static double dy;


    // Decalre Normal variables.
    double angle = 0;
    const double WEIGHT = 15103.00;
    const double GRAVITY = -1.625;
    const double THRUST = 45000.00;
    double time = 0;



protected:


};