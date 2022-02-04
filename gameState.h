#pragma once
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include <vector>
#include <random>

#include <iostream>

class LanderState 
{
public:
    LanderState(const Point& ptUpperRight) : 
        angle(0.0),
        ptLM(ptUpperRight.getX() - 50, ptUpperRight.getY() - 50),
        ground(ptUpperRight)
    {};

    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    Ground ground;




    double angle;         // angle the LM is pointing
    static double fuel;


    void decrementFuel();



};



class UserInterface
{
public:
    bool applyThrust = false;

    void onScreenText(LanderState* landerInstance, Ground groundInstance); // Centerlize what text to place on screen
    void updateControllerInputs(const Interface* pUI, LanderState* LanderInstance);
    


};




class Crash
{
public:
    bool isInGround(LanderState * landerInstance);
    double altitude(Ground groundInstance, LanderState* landerInstance);

private:

protected:
};



class Stars
{
public:
    void showStars();

private:
    unsigned char phase;
    Point location;
    ogstream starsOut;

protected:

};



class Physics
{
public:
	void gravity(LanderState* LanderInstance);
    void applyIntertia(LanderState* LanderInstance);
    void applyThrust(LanderState* LanderInstance, UserInterface* userInterfaceInstance);
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